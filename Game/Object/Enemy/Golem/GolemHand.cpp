/**
 * @file   GolemHand.cpp
 *
 * @brief  プレイヤーの手に関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2025/09/13
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GolemHand.h"
#include"../Golem/Golem.h"
#include"Game/Fuctory/GameObjectFactory.h"
 // メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
GolemHand::GolemHand(Character* root, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:m_graphics{Graphics::GetInstance()}
	, EnemyPart(root,parent,initialPosition,initialAngle)
	,m_motionAngle{}
	,m_sphere{initialPosition,2.5f}
	,m_display{ Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext() }

{
	SetTexture(ResourceManager::GetInstance()->RequestTexture(L"golemhand.png"));
	SetModel(ResourceManager::GetInstance()->RequestModel(L"golemhand.sdkmesh"));
	Messenger::GetInstance()->Register(GetObjectNumber(), this);

	SetShape(&m_sphere);
}



/**
 * @brief デストラクタ
 */
GolemHand::~GolemHand()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemHand::Initialize()
{
	
	//m_weapon = GameObjectFactory::CreatePikle(m_parent->Cast<Character>(), this, DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f), DirectX::SimpleMath::Quaternion::Identity);

	//DirectX::SimpleMath::Quaternion q = 
	//	//* DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(45.0f))
	//	//* DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(45.0f))
	//	 DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(-90.0f));
	//SetQuaternion(q);



}




/**
 * @brief 更新処理
 *
 * @param[in] currentPosition
 * @param[in] currentAngle
 *
 * @return なし
 */
void GolemHand::Update( const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{

	m_currentAngle =m_initialAngle * GetQuaternion()   * m_motionAngle * currentAngle;
	m_currentPosition =DirectX::SimpleMath::Vector3::Transform(m_initialPosition+ GetPosition(), m_motionAngle * currentAngle)+ currentPosition ;
	

	m_sphere.SetCenter(GetCurrentPosition());

	if(m_weapon)
	m_weapon->Update(m_currentPosition, m_currentAngle);
}




/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemHand::Draw()
{
	Shader* shader = Shader::GetInstance();
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale());
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Golem::ConstBuffer cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();
	cbuff.color.x = GetRootCharacter()->GetDamageFlash();

	//GetModel()->Draw(context, *states, world, view, proj);
	Shader::OutlineConstBuffer outline;
	outline.matWorld = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale()).Transpose();
	outline.matView = graphics->GetViewMatrix().Transpose();
	outline.matProj = graphics->GetProjectionMatrix().Transpose();
	outline.outlineThickness = 0.04f;
	context->UpdateSubresource(shader->GetCBuffer(Shader::Outline), 0, NULL, &outline, 0, 0);



	if (Messenger::GetInstance()->IsOutLineActive()) {

		// モデル描画（アウトライン専用）
		GetModel()->Draw(context, *states, world, view, proj, false, [&]() {
			// カリングを FrontFace にして裏面を描画（アウトライン用）
			context->RSSetState(states->CullCounterClockwise());

			// ブレンド・デプスステート（深度は通常通り or 調整）
			context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);
			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			// アウトラインシェーダを設定
			Shader::GetInstance()->StartShader(Shader::Outline, shader->GetCBuffer(Shader::Outline));
			context->IASetInputLayout(shader->GetInputLayout(Shader::Outline));

			});

		Shader::GetInstance()->EndShader();
	}

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
	if (m_weapon)
	m_weapon->Draw();

	//m_sphere.AddDisplayCollision(&m_display);
	//m_display.DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates()
	//	, Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemHand::Finalize()
{

}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void GolemHand::OnMessegeAccepted(Message::MessageID messageID)
{
}

/**
 * @brief 衝突応答
 *
 * @param[in] other 衝突したオブジェクト
 *
 * @return なし
 */
void GolemHand::CollisionResponce(GameObject* other)
{
}


/**
 * @brief 武器を持たせる
 *
 * @param[in] weapon 武器クラス
 *
 * @return true   成功
 * @return false　失敗
 */
bool GolemHand::HaveWeapon(std::unique_ptr<Weapon> weapon)
{
	//実体があるか確認
	if (weapon) 
	{
		//所有権を移動
		m_weapon = std::move(weapon);

		//成功
		return true;
	}

	//失敗
	return false;
}


/**
 * @brief モーションの角度を取得
 *
 * @param[in] なし
 *
 * @return モーションの角度
 */
DirectX::SimpleMath::Quaternion GolemHand::GetMotionAngle()
{
	return m_motionAngle;
}

/**
 * @brief モーションの角度の設定
 *
 * @param[in] なし
 *
 * @return モーションの角度
 */
void GolemHand::SetMotionAngle(DirectX::SimpleMath::Quaternion angle)
{
	m_motionAngle = angle;
}
