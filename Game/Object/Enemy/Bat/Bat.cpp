/**
 * @file   Bat.cpp
 *
 * @brief  コウモリの敵に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/10/17
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Bat.h"
#include "Game/Common/Collision/CollisionManager.h"
#include"../CaveDiving/Game/Factory/GameObjectFactory.h"
#include"Game/Common/DamageSystem.h"
#include"Game/Object/Weapon.h"
#include"Game/Shader/ShaderManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
 */
Bat::Bat(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:m_graphics{Graphics::GetInstance()}
	, Character(40,30,5,Tag::ObjectType::Enemy, parent, initialPosition, initialAngle)
	, m_sphere{ GetPosition(), 2.0f } // 初期位置とサイズを設定
	,m_frameCount{}
	,m_messageID{}
{
	SetTexture(ResourceManager::GetInstance()->RequestTexture("bat.png"));

	SetModel(ResourceManager::GetInstance()->RequestModel(L"bat.sdkmesh"));

	SetShape(&m_sphere);

	//羽オブジェクトの生成
	m_leftWing = GameObjectFactory::CreateBatWing(this, this,LEFTWING_INIT_POS);
	m_rightWing = GameObjectFactory::CreateBatWing(this, this,RIGHTWING_INIT_POS
	,DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(RIGHT_WING_INIT_DEGREE)));



}



/**
 * @brief デストラクタ
 */
Bat::~Bat()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Bat::Initialize()
{
	// 状態の初期化
	m_idlingState  = std::make_unique<BatIdling>(this);
	m_movingState  = std::make_unique<BatMoving>(this);
	m_chasingState = std::make_unique<BatChasing>(this);
	m_attackState  = std::make_unique<BatAttack>(this, m_rightWing.get(), m_leftWing.get());
	m_attackPreaparing = std::make_unique<BatAttackPreparing>(this,m_rightWing.get(), m_leftWing.get());
	m_damagedState = std::make_unique<BatDamaged>(this);

	//初期状態設定
	SetState(m_idlingState.get());


	//SetPosition(DirectX::SimpleMath::Vector3(0.0f, 1.0f, -8.0f));
	SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	SetScale(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));

	m_currentPosition = m_initialPosition  + GetPosition();
	m_currentAngle = m_initialAngle * GetQuaternion() ;

}



/**
 * @brief 更新処理
 *
 * @param[in] currentPosition 親の座標
 * @param[in] currentAngle　親の角度
 *
 * @return なし
 */
void Bat::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
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
	m_leftWing->Update(GetCurrentPosition(), GetCurrentQuaternion());
	m_rightWing->Update(GetCurrentPosition(), GetCurrentQuaternion());

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
void Bat::Draw()
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
	Bat::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale()).Transpose();
	cbuff.matView = graphics->GetViewMatrix().Transpose();
	cbuff.matProj = graphics->GetProjectionMatrix().Transpose();
	cbuff.color.x = GetDamageFlash();
	ShaderManager* shader = ShaderManager::GetInstance();
	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::ShaderType::Model), 0, NULL, &cbuff, 0, 0);


	OutlineShader::OutlineCB outline;
	outline.matWorld = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale()).Transpose();
	outline.matView = graphics->GetViewMatrix().Transpose();
	outline.matProj = graphics->GetProjectionMatrix().Transpose();
	outline.outlineThickness = 0.04f;
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::ShaderType::Outline), 0, NULL, &outline, 0, 0);


	if (Messenger::GetInstance()->IsOutLineActive()) {

	// モデル描画（アウトライン専用）
	GetModel()->Draw(context, *states, world, view, proj, false, [&]() {
		// カリングを FrontFace にして裏面を描画（アウトライン用）
		context->RSSetState(states->CullCounterClockwise());

		// ブレンド・デプスステート（深度は通常通り or 調整）
		context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);
		context->OMSetDepthStencilState(states->DepthDefault(), 0);

		// アウトラインシェーダを設定
		ShaderManager::GetInstance()->StartShader(ShaderManager::ShaderType::Outline);
		context->IASetInputLayout(shader->GetInputLayout(ShaderManager::ShaderType::Outline));

		});

	ShaderManager::GetInstance()->EndShader();
	}


	GetModel()->Draw(context, *states, world, view, proj, false, [&]()
		{
			//	モデル表示をするための自作シェーダに関連する設定を行う


			//	画像用サンプラーの登録
			ID3D11SamplerState* sampler[1] = { states->PointWrap() };
			context->PSSetSamplers(0, 1, sampler);

			if (GetTexture() != nullptr)
			{
				//	読み込んだ画像をピクセルシェーダに伝える
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

			ShaderManager::GetInstance()->StartShader(ShaderManager::Model);

			context->IASetInputLayout(shader->GetInputLayout(ShaderManager::Model));

		});
	ShaderManager::GetInstance()->EndShader();

	//羽の描画
	m_leftWing->Draw();
	m_rightWing->Draw();
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Bat::Finalize()
{

}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void Bat::OnMessegeAccepted(Message::MessageID messageID)
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
		GameObject::ChangeState(m_damagedState.get());
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
void Bat::CollisionResponce(GameObject* other)
{
	switch (other->GetObjectType())
	{
		case Tag::ObjectType::Player:
		{
			// プレイヤーとの衝突処理
			// ここでは何もしないが、必要に応じて実装
		}
		break;
		case Tag::ObjectType::Ground:
		{
			//ステージとの衝突応答　押し出し
			SetPosition(CollisionManager::GetInstance()->PushOut(dynamic_cast<Box*>(other->GetShape()), &m_sphere, GetVelocity()));
			//速度をリセット
			m_velocity.y = 0.0f;

			//攻撃状態なら
			if (GetState() == m_attackState.get()) 
			{
				OnMessegeAccepted(Message::MessageID::IDLING);
			}

		}	
		break;
		case Tag::ObjectType::Wall: 
		{
			if (m_sphere.Contains(other->GetShape()))
			{
				break;
			}


			//ステージ壁との衝突応答　押し出し
			SetPosition(CollisionManager::GetInstance()->PushBack(&m_sphere, dynamic_cast<Sphere*>(other->GetShape())));

			m_sphere.SetCenter(GetPosition());

			//速度をリセット
			//m_velocity.y = 0.0f;
			//ResetJumpCount();

		}
		break;
		case Tag::ObjectType::Weapon:
		{
			Weapon* weapon = other->Cast<Weapon>();
			//攻撃力をもっている所有者を渡す
			OnDamage(weapon->GetOwner());

		}
		break;
		case Tag::ObjectType::Light:
		{
			//ライトオブジェクトとの衝突応答　押し出し
			SetPosition(CollisionManager::GetInstance()->PushOut(dynamic_cast<Box*>(other->GetShape()), &m_sphere, GetVelocity()));

		}
	default:
		break;
	}
}




/**
 * @brief 経過時間の取得
 *
 * @param[in] なし
 *
 * @return なし
 */const float Bat::GetFrameCount() const
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
void Bat::ResetFrameCount()
{
	m_frameCount = 0.0f;
}

DirectX::SimpleMath::Vector3 Bat::GetVelocity()
{
	return m_velocity;
}

void Bat::SetVelocity(DirectX::SimpleMath::Vector3 v)
{
	m_velocity = v;
}


DirectX::SimpleMath::Quaternion Bat::GetMotionAngle()
{
	return m_motionAngle;
}

void Bat::SetMotionAngle(DirectX::SimpleMath::Quaternion angle)
{
	m_motionAngle = angle;
}
