/**
 * @file   Golem.cpp
 *
 * @brief  ゴーレムの敵に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/03/02
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Golem.h"
#include "Game/Common/Collision/CollisionManager.h"
#include"Game/Factory/GameObjectFactory.h"
#include"Game/Common/DamageSystem.h"
#include"Game/Object/Weapon.h"
#include"Game/Shader/ShaderManager.h"
#include"Game/Particle/ParticleManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
 */
Golem::Golem(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:Character(GOLEM_BASE_HP,GOLEM_BASE_ATTACK,GOLEM_BASE_DIFFENCE,Tag::ObjectType::Enemy, parent, initialPosition, initialAngle),
	m_box{ GetPosition(), GOLEM_COLLISION_SIZE }, // 初期位置とサイズを設定
	m_frameCount{},
	m_messageID{},
	m_parts{},
	m_display{ Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext() },
	m_attackMessage{Message::AttackMesssage::NONE}
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	//テクスチャ設定
	SetTexture(resourceManager->RequestTexture(ResourcePath::TEXTURE::GOLEM));
	//モデル設定
	SetModel(resourceManager->RequestModel(ResourcePath::MODEL::GOLEM));
	///当たり判定設定
	SetShape(&m_box);
}

/**
 * @brief デストラクタ
 */
Golem::~Golem()
{
	//当たり判定管理クラスの登録を解除
	for (auto& part : m_parts) 
	{
		CollisionManager::GetInstance()->UnRegister(part.get());
	}
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
	CollisionManager* collisionManager = CollisionManager::GetInstance();
	//右腕の生成
	m_parts.emplace_back(GameObjectFactory::CreateGolemArm(this, this, GOLEM_RIGHT_ARM_INIT_POS, DirectX::SimpleMath::Quaternion::Identity));
	//当たり判定管理クラスに登録
	collisionManager->Register(m_parts.back().get());
	//左腕の生成
	m_parts.emplace_back(GameObjectFactory::CreateGolemArm(this, this, GOLEM_LEFT_ARM_INIT_POS,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, LEFT_HAND_INIT_ANGLE)));
	//当たり判定管理クラスに登録
	collisionManager->Register(m_parts.back().get());
	//右足の生成
	m_parts.emplace_back(GameObjectFactory::CreateGolemFot(this, this, GOLEM_RIGHT_FOT_INIT_POS,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, FOT_INIT_ANGLE)));
	//当たり判定管理クラスに登録
	collisionManager->Register(m_parts.back().get());
	//左足の生成
	m_parts.emplace_back(GameObjectFactory::CreateGolemFot(this, this, GOLEM_LEFT_FOT_INIT_POS,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, FOT_INIT_ANGLE)));
	//当たり判定管理クラスに登録
	collisionManager->Register(m_parts.back().get());

	// 状態の初期化
	m_idlingState  = std::make_unique<GolemIdling>(this);
	m_movingState  = std::make_unique<GolemMoving>(this);
	m_chasingState = std::make_unique<GolemChasing>(this);
	m_attackState  = std::make_unique<GolemAttack>(this);
	m_attackPreaparing = std::make_unique<GolemAttackPreparing>(this);
	//m_damagedState = std::make_unique<GolemDamaged>(this);
	//初期状態をセット
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

	if (!DamageFlashUpdate())
	{
		SetInvincible(false);

	}

	//位置の更新
	SetCurrentPosition(currentPosition + GetPosition());
	//角度の更新
	SetCurrentAngle(m_motionAngle * GetQuaternion() * currentAngle);

	//当たり判定更新
	m_box.SetCenter(GetCurrentPosition());

	//子クラス更新
	for (std::unique_ptr<PartObject>& part : m_parts) 
	{
		part->Update(GetCurrentPosition(), GetCurrentQuaternion());
	}

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
	ShaderManager* shader = ShaderManager::GetInstance();

	DirectX::SimpleMath::Matrix world = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale());

	//アウトライン描画
	if (Messenger::GetInstance()->IsOutLineActive())
	{
		OutlineRenderer::Draw(*GetModel(), world, GOLEM_OUTLINE_THICKNESS);
	}

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ModelShader::ModelCB cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.flash.x = GetDamageFlash();

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::Model), 0, NULL, &cbuff, 0, 0);


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
			//シェーダー設定
			shader->StartShader(ShaderManager::Model);
			//頂点情報設定
			context->IASetInputLayout(shader->GetInputLayout(ShaderManager::Model));

		});
	//シェーダー解放
	shader->EndShader();

	//子クラスの描画
	for (std::unique_ptr<PartObject>& part : m_parts)
	{
		part->Draw();
	}

	//m_box.AddDisplayCollision(&m_display);
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
	case Message::ATTACK:
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
			break;
		}
		case Tag::ObjectType::Enemy:
		{

			break;
		}
		case Tag::ObjectType::Ground:
		{
			//ステージとの衝突応答　押し出し
			DirectX::SimpleMath::Vector3 newPosition = CollisionManager::GetInstance()->PushOut(dynamic_cast<Box*>(other->GetShape()),&m_box);
			SetPosition(newPosition);
			//m_box.SetCenter(GetCurrentPosition());

			//Yの速度をリセット
			DirectX::SimpleMath::Vector3 velocity = GetVelocity();
			velocity.y = 0.0f;
			SetVelocity(velocity);


			break;
		}

		case Tag::ObjectType::Weapon:
		{
			Weapon* weapon = other->Cast<Weapon>();
			//攻撃力をもっている所有者を渡す
			OnDamage(weapon->GetOwner());
			break;
		}
	default:
		break;
	}

}


/**
 * @brief ダメージを受けたときの処理
 *
 * @param[in] other  ダメージを与えたオブジェクト
 *
 * @return なし
 */
void Golem::OnDamage(GameObject* other)
{
	Character::OnDamage(other);
	//死んでいたらエフェクトを出す
	if (!IsAlive())
	{
		//消滅パーティクル生成をリクエスト
		ParticleManager::GetInstance()->RequestVanishParticle(GetCurrentPosition());

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


/**
 * @brief 攻撃メッセージの取得
 *
 * @param[in] なし
 *
 * @return 攻撃メッセージ
 */
const Message::AttackMesssage Golem::GetAttackMessage() const
{
	return m_attackMessage;
}

/**
 * @brief 攻撃メッセージの設定
 *
 * @param[in] message  攻撃メッセージ
 *
 * @return なし
 */
void Golem::SetAttackMessage(const Message::AttackMesssage& message)
{
	m_attackMessage = message;
}


/**
 * @brief モーション用角度の取得
 *
 * @param[in] なし
 *
 * @return モーション用角度
 */
const DirectX::SimpleMath::Quaternion& Golem::GetMotionAngle() const
{
	return m_motionAngle;
}

/**
 * @brief モーション用角度の設定
 *
 * @param[in] angle  モーション用角度
 *
 * @return なし
 */
void Golem::SetMotionAngle(const DirectX::SimpleMath::Quaternion& angle)
{
	m_motionAngle = angle;
}