/**
 * @file   BatMoving.cpp
 *
 * @brief  コウモリの移動状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Bat/State/BatMoving.h"
#include "Game/Object/Enemy/Bat/Bat.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player プレイヤーのポインタ
 */
BatMoving::BatMoving(Bat* bat)
	: m_bat(bat)
	, m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
}
/**
 * @brief デストラクタ
 */
BatMoving::~BatMoving()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::Initialize()
{
	PreUpdate();
}

/**
 * @brief 事前処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::PreUpdate()
{
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// キーボードステートを取得する
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();
	DirectX::SimpleMath::Vector3 v = m_bat->GetVelocity();

	DirectX::SimpleMath::Quaternion q;

	if (key->GetLastState().Up) 
	{
		v.z -= 1.0f*elapsedTime;
	}
	if (key->GetLastState().Down)
	{
		v.z += 1.0f*elapsedTime;
	}
	if (key->GetLastState().Left)
	{
		v.x -= 1.0f*elapsedTime;
		q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(1.0f));
	}
	if (key->GetLastState().Right)
	{
		v.x += 1.0f*elapsedTime;
		q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-1.0f));
	}
	if (key->IsKeyPressed(DirectX::Keyboard::Z)) 
	{
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::ATTACK);
	}
	if (key->pressed.Space)
	{
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::JUMPING);
	}

	// 姿勢に回転を加える
	m_bat->SetQuaternion(m_bat->GetQuaternion() * q);

	if(v.Length()<=0.001f)
	{
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::IDLING);
	}
	v *= 0.96f;
	v.y += -0.8f * elapsedTime;

	m_bat->SetVelocity(v);

	m_bat->SetPosition(m_bat->GetPosition() + m_bat->GetVelocity());

}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::PostUpdate()
{
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::Render()
{
	Shader* shader = Shader::GetInstance();

	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Bat::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(m_bat->GetCurrentPosition(), m_bat->GetCurrentQuaternion(), m_bat->GetScale()).Transpose();
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(Shader::Model), 0, NULL, &cbuff, 0, 0);



	m_bat->GetModel()->Draw(context, *states, world, view, proj, false, [&]()
		{
			//	モデル表示をするための自作シェーダに関連する設定を行う


			//	画像用サンプラーの登録
			ID3D11SamplerState* sampler[1] = { states->PointWrap() };
			context->PSSetSamplers(0, 1, sampler);

			if (m_bat->GetTexture() != nullptr)
			{
				//	読み込んだ画像をピクセルシェーダに伝える
				//	自作VSはt0を使っているため、
				//	t0がメインで使われていると勝手に想定。
				context->PSSetShaderResources(0, 1, m_bat->GetTexture());
			}

			//	半透明描画指定
			ID3D11BlendState* blendstate = states->NonPremultiplied();

			//	透明判定処理
			context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

			//	深度バッファに書き込み参照する
			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			//	カリングはなし
			context->RSSetState(states->CullClockwise());

			Shader::GetInstance()->StartShader(Shader::Model,shader->GetCBuffer(Shader::Model));

			context->IASetInputLayout(shader->GetInputLayout(Shader::Model));

		});
	Shader::GetInstance()->EndShader();

#ifdef _DEBUG
#endif // DEBUG

}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::Finalize()
{
}
