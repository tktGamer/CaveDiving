/**
 * @file   Wing.cpp
 *
 * @brief  プレイヤーの手に関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Wing.h"
#include"../Bat/Bat.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Wing::Wing(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:m_graphics{Graphics::GetInstance()}
	, GameObject(Tag::ObjectType::Player,parent,initialPosition,initialAngle)
	,m_objectNumber{CountUpNumber()}
	,m_motionAngle{}
{
	SetTexture(ResourceManager::GetInstance()->RequestTexture(L"wing.png"));
	SetModel(ResourceManager::GetInstance()->RequestModel(L"wing.sdkmesh"));
	Messenger::GetInstance()->Register(m_objectNumber, this);

}



/**
 * @brief デストラクタ
 */
Wing::~Wing()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Wing::Initialize()
{



}




/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Wing::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{

	m_currentAngle =m_initialAngle * GetQuaternion() * m_motionAngle * currentAngle;
	m_currentPosition =DirectX::SimpleMath::Vector3::Transform(m_initialPosition, m_motionAngle* currentAngle)+ currentPosition + GetPosition();
	
}




/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Wing::Draw()
{
	Shader* shader = Shader::GetInstance();
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = TKTLib::GetWorldMatrix(m_currentPosition,m_currentAngle, GetScale());
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Bat::ConstBuffer cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();


	//GetModel()->Draw(context, *states, world, view, proj);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(Shader::Model), 0, NULL, &cbuff, 0, 0);

	GetModel()->Draw(context, *states, world, view, proj, false, [&]()
		{
			//	モデル表示をするための自作シェーダに関連する設定を行う


			//	画像用サンプラーの登録
			ID3D11SamplerState* sampler[1] = { states->PointWrap() };
			context->PSSetSamplers(0, 1, sampler);

			if (GetTexture() != nullptr)
			{
				//	読み込んだ画像をピクセルシェーダに伝える
				//	自作VSはt0を使っているため、
				//	t0がメインで使われていると勝手に想定。
				context->PSSetShaderResources(0, 1, GetTexture());
			}

			//	半透明描画指定
			ID3D11BlendState* blendstate = states->NonPremultiplied();

			//	透明判定処理
			context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

			//	深度バッファに書き込み参照する
			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			//	カリングはなし
			context->RSSetState(states->CullClockwise());

			Shader::GetInstance()->StartShader(Shader::Model, shader->GetCBuffer(Shader::Model));

			context->IASetInputLayout(shader->GetInputLayout(Shader::Model));

		});
	Shader::GetInstance()->EndShader();

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Wing::Finalize()
{

}

void Wing::OnMessegeAccepted(Message::MessageID messageID)
{
}

int Wing::GetObjectNumber()
{
	return 0;
}

DirectX::SimpleMath::Quaternion Wing::GetMotionAngle()
{
	return m_motionAngle;
}

void Wing::SetMotionAngle(DirectX::SimpleMath::Quaternion angle)
{
	m_motionAngle = angle;
}
