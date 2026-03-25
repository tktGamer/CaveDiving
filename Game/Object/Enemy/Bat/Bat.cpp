/**
 * @file   Bat.cpp
 *
 * @brief  コウモリの敵に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Bat.h"
#include "Game/Common/Collision/CollisionManager.h"
#include"../CaveDiving/Game/Factory/GameObjectFactory.h"
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
Bat::Bat(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	: 
	Character(BAT_BASE_HP,BAT_BASE_ATTACK,BAT_BASE_DIFFENCE
				,Tag::ObjectType::Enemy, parent, initialPosition, initialAngle),
	m_sphere{ GetPosition(), BAT_SPHERE_SIZE },
	m_messageID{},
	m_frameCount{},
	m_motionAngle{},
	m_idlingState{},   
	m_movingState{},  
	m_attackState{},
	m_chasingState{},
	m_attackPreaparing{}, 
	m_damagedState{},
	m_rightWing{},
	m_leftWing{}
{
	//テクスチャ設定
	SetTexture(ResourceManager::GetInstance()->RequestTexture(ResourcePath::TEXTURE::BAT));
	//モデル設定
	SetModel(ResourceManager::GetInstance()->RequestModel(ResourcePath::MODEL::BAT));
	//当たり判定設定
	SetShape(&m_sphere);

	//羽オブジェクトの生成
	m_leftWing = GameObjectFactory::CreateBatWing(this, this,LEFTWING_INIT_POS);
	//モデルの初期が左羽の向きなので反対向きにする
	m_rightWing = GameObjectFactory::CreateBatWing(this, this,RIGHTWING_INIT_POS
	,DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY,RIGHT_WING_INIT_ANGLE));
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
	//角度設定
	SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	//大きさ設定
	SetScale(DirectX::SimpleMath::Vector3::One);

	//現在位置・角度設定
	SetCurrentPosition(GetPosition());
	SetCurrentAngle(GetQuaternion());
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
	//ダメージ演出更新
	DamageFlashUpdate();

	//位置の更新
	SetCurrentPosition(currentPosition + GetPosition());
	//角度の更新
	SetCurrentAngle(m_motionAngle * GetQuaternion() * currentAngle);
	
	//当たり判定更新
	m_sphere.SetCenter(GetCurrentPosition());

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
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();
	ShaderManager* shader = ShaderManager::GetInstance();
	///ワールド行列を計算
	DirectX::SimpleMath::Matrix world = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale());
	//アウトラインの描画
	if (Messenger::GetInstance()->IsOutLineActive()) 
	{
		OutlineRenderer::Draw(*GetModel(), world, BAT_OUTLINE_THICKNESS);
	}

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ModelShader::ModelCB cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.flash.x = GetDamageFlash();
	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::ShaderType::Model), 0, NULL, &cbuff, 0, 0);

	//モデル描画
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

			//シェーダーセット
			shader->StartShader(ShaderManager::Model);
			//インプットレイアウトセット
			context->IASetInputLayout(shader->GetInputLayout(ShaderManager::Model));

		});
	//シェーダー終了
	shader->EndShader();

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
		//待機
	case Message::IDLING:
		GameObject::ChangeState(m_idlingState.get());
		break;
		//移動
	case Message::MOVING:
		GameObject::ChangeState(m_movingState.get());
		break;
		//攻撃
	case Message::ATTACK:
		GameObject::ChangeState(m_attackState.get());
		break;
		//ダメージ
	case Message::DAMAGED:
		GameObject::ChangeState(m_damagedState.get());
		break;
		//追跡
	case Message::CHASING:
		GameObject::ChangeState(m_chasingState.get());
		break;
		//攻撃準備
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
		}
		break;
		case Tag::Enemy:
		{
			//敵同士の衝突処理　押し出し
			SetPosition(CollisionManager::GetInstance()->PushOut(other->GetShape(), &m_sphere));
		}
		break;
		case Tag::ObjectType::Ground:
		{
			//ステージとの衝突応答　押し出し
			SetPosition(CollisionManager::GetInstance()->PushOut(other->GetShape(), &m_sphere));
			//Yの速度をリセット
			DirectX::SimpleMath::Vector3 velocity = GetVelocity();
			velocity.y = 0.0f;
			SetVelocity(velocity);

			//攻撃状態なら
			if (GetState() == m_attackState.get()) 
			{
				OnMessegeAccepted(Message::MessageID::IDLING);
			}

		}	
		break;
		case Tag::ObjectType::Wall: 
		{
			//壁に内包されているか
			if (m_sphere.Contains(other->GetShape()))
			{
				break;
			}

			//ステージ壁との衝突応答　押し出し
			SetPosition(CollisionManager::GetInstance()->PushBack(&m_sphere, dynamic_cast<Sphere*>(other->GetShape())));
			
			m_sphere.SetCenter(GetPosition());


		}
		break;
		//武器と
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
			SetPosition(CollisionManager::GetInstance()->PushOut(other->GetShape(), &m_sphere));

		}
	default:
		break;
	}

	//死んでいたらエフェクトを出す
	if (!IsAlive())
	{
		//消滅パーティクル生成をリクエスト
		ParticleManager::GetInstance()->RequestVanishParticle(GetCurrentPosition());

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

/**
 * @brief モーション用角度の取得
 *
 * @param[in] なし
 *
 * @return モーション用角度
 */
const DirectX::SimpleMath::Quaternion& Bat::GetMotionAngle() const
{
	return m_motionAngle;
}

/**
 * @brief モーション用角度の設定
 *
 * @param[in] angle  モーション用角度
 *
 * @return  なし
 */
void Bat::SetMotionAngle(const DirectX::SimpleMath::Quaternion& angle)
{
	m_motionAngle = angle;
}