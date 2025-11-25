/**
 * @file   Golem.cpp
 *
 * @brief  ゴーレムのボス敵に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/11/15
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Golem.h"
#include "Game/Common/Collision/CollisionManager.h"
#include"Game/Fuctory/GameObjectFactory.h"
#include"Game/Common/DamageSystem.h"
#include"Game/Object/Weapon.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
 */
Golem::Golem(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:m_graphics{Graphics::GetInstance()}
	, Character(GOLEM_HP,13,0,Tag::ObjectType::Enemy, parent, initialPosition, initialAngle)
	, m_sphere{ GetPosition(), 4.0f } // 初期位置とサイズを設定
	,m_frameCount{}
	,m_messageID{}
	, m_display{ Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext() }
	,m_attackMessage{Message::AttackMesssage::NONE}
{
	SetTexture(ResourceManager::GetInstance()->RequestTexture("golem.png"));

	SetModel(ResourceManager::GetInstance()->RequestModel(L"golem.sdkmesh"));

	SetShape(&m_sphere);



}



/**
 * @brief デストラクタ
 */
Golem::~Golem()
{
	CollisionManager::GetInstance()->UnRegister(m_rightHand.get());
	CollisionManager::GetInstance()->UnRegister(m_leftHand.get());
}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Golem::Initialize()
{


	SetPosition(DirectX::SimpleMath::Vector3(0.0f, 1.0f, -8.0f));
	SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	SetScale(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));

	m_currentPosition = m_initialPosition  + GetPosition();
	m_currentAngle = m_initialAngle * GetQuaternion() ;

	m_rightHand = std::make_unique<GolemHand>(this,this, DirectX::SimpleMath::Vector3{ 4.5f ,2.0f,0.0f}, DirectX::SimpleMath::Quaternion::Identity);
	m_leftHand = std::make_unique<GolemHand>(this,this, DirectX::SimpleMath::Vector3{ -4.5f ,2.0f,0.0f},
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY,DirectX::XMConvertToRadians(180.0f)));

	CollisionManager::GetInstance()->Register(m_rightHand.get());
	CollisionManager::GetInstance()->Register(m_leftHand.get());

	// 状態の初期化
	m_idlingState  = std::make_unique<GolemIdling>(this);
	m_movingState  = std::make_unique<GolemMoving>(this);
	m_chasingState = std::make_unique<GolemChasing>(this);
	m_attackState  = std::make_unique<GolemAttack>(this, m_rightHand.get(), m_leftHand.get());
	m_attackPreaparing = std::make_unique<GolemAttackPreparing>(this,m_rightHand.get(), m_leftHand.get());
	//m_damagedState = std::make_unique<GolemDamaged>(this);

	SetState(m_idlingState.get());
}



/**
 * @brief 更新処理
 *
 * @param[in] currentPosition 親の座標
 * @param[in] currentAngle　親の角度
 *
 * @return なし
 */
void Golem::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();
	//生きていない場合更新しない
	if (!IsAlive())
	{
		return;
	}


	//現在の状態を更新
	GetState()->Update(elapsedTime);

	DamageFlashUpdate();

	m_currentPosition = m_initialPosition + currentPosition + GetPosition();
	m_currentAngle =m_initialAngle * m_motionAngle* GetQuaternion() * currentAngle;
	
	//当たり判定更新
	m_sphere.SetCenter(m_currentPosition);

	//子クラス更新
	m_rightHand->Update(m_currentPosition, m_currentAngle);
	m_leftHand->Update(m_currentPosition, m_currentAngle);
	//時間経過
	m_frameCount += elapsedTime;
}




/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Golem::Draw()
{
	//生きていない場合描画しない
	if (!IsAlive()) 
	{
		return;
	}


	//現在の状態を描画
	//GetState()->Render();

	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Golem::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale()).Transpose();
	cbuff.matView = graphics->GetViewMatrix().Transpose();
	cbuff.matProj = graphics->GetProjectionMatrix().Transpose();
	cbuff.color.x = GetDamageFlash();

	Shader* shader = Shader::GetInstance();
	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(Shader::Model), 0, NULL, &cbuff, 0, 0);

	Shader::OutlineConstBuffer outline;
	outline.matWorld = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale()).Transpose();
	outline.matView = graphics->GetViewMatrix().Transpose();
	outline.matProj = graphics->GetProjectionMatrix().Transpose();
	outline.outlineThickness = 0.04f;
	context->UpdateSubresource(shader->GetCBuffer(Shader::Outline), 0, NULL, &outline, 0, 0);



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

	m_rightHand->Draw();
	m_leftHand->Draw();

	m_sphere.AddDisplayCollision(&m_display);
	m_display.DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates()
		, Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Golem::Finalize()
{

}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void Golem::OnMessegeAccepted(Message::MessageID messageID)
{
	switch (messageID)
	{
	case Message::IDLING:
		GameObject::ChangeState(m_idlingState.get());
		break;
	case Message::MOVING:
		GameObject::ChangeState(m_movingState.get());
		break;
	case Message::GROUNDATTACK:
		GameObject::ChangeState(m_attackState.get());
		break;
	case Message::DAMAGED:
		//GameObject::ChangeState(m_damagedState.get());
		break;
	case Message::CHASING:
		GameObject::ChangeState(m_chasingState.get());
		break;
	case Message::ATTACKPREPARING:
		GameObject::ChangeState(m_attackPreaparing.get());
		break;

	default:
		break;
	}

}

/**
 * @brief 衝突応答
 *
 * @param[in] other 衝突したオブジェクト
 *
 * @return なし
 */
void Golem::CollisionResponce(GameObject* other)
{
	switch (other->GetObjectType())
	{
		case Tag::ObjectType::Player:
		{
			// プレイヤーとの衝突処理
			// ここでは何もしないが、必要に応じて実装
			break;
		}
		case Tag::ObjectType::Ground:
		{
			//ステージとの衝突応答　押し出し
			SetPosition(CollisionManager::GetInstance()->PushOut(dynamic_cast<Box*>(other->GetShape()), &m_sphere, GetVelocity()));
			//速度をリセット
			m_velocity.y = 0.0f;


			break;
		}
		case Tag::ObjectType::Weapon:
		{
			Weapon* weapon = other->Cast<Weapon>();
			//攻撃力をもっている所有者を渡す
			OnDamage(weapon->GetOwner());
			SetDamageFlash();
			break;
		}
	default:
		break;
	}
}



/**
 * @brief オブジェクトの経過時間（状態遷移用）
 *
 * @param[in] なし
 *
 * @return 経過時間
 */
const float Golem::GetFrameCount() const
{
	return m_frameCount;
}

/**
 * @brief 経過時間のリセット
 *
 * @param[in] なし
 *
 * @return なし
 */
void Golem::ResetFrameCount()
{
	m_frameCount = 0.0f;
}

DirectX::SimpleMath::Vector3 Golem::GetVelocity()
{
	return m_velocity;
}

void Golem::SetVelocity(DirectX::SimpleMath::Vector3 v)
{
	m_velocity = v;
}

const Message::AttackMesssage Golem::GetAttackMessage() const
{
	return m_attackMessage;
}

void Golem::SetAttackMessage(const Message::AttackMesssage& message)
{
	m_attackMessage = message;
}


DirectX::SimpleMath::Quaternion Golem::GetMotionAngle() const
{
	return m_motionAngle;
}

void Golem::SetMotionAngle(DirectX::SimpleMath::Quaternion angle)
{
	m_motionAngle = angle;
}
