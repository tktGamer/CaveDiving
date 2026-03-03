/**
 * @file   Player.cpp
 *
 * @brief  プレイヤーに関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　　2026/01/12
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Player.h"
#include "Game/Interface/IState.h"
#include"Game/Shader/ShaderManager.h"
#include"Game/Common/Collision/Sphere.h"
#include"Game/Common/Collision/CollisionManager.h"
#include"../Gem/GemManager.h"
#include"Game/Common/DamageSystem.h"
#include"Game/Factory/GameObjectFactory.h"
#include"Game/Particle/ParticleManager.h"
#include"Game/UI/Buff/BuffUIControl.h"
#include"Game/Object/Gem/Unique/HPAutoRecoveryGem.h"
#include"Game/Object/Gem/StatusUp/FullHPStatusUpGem.h"
#include"Game/Object/Gem/Unique/GenerateShieldGem.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] data プレイヤーデータ
 * @param[in] parent 親のポインタ
 * @param[in] initialPositon 初期座標
 * @param[in] initialAngle 　初期角度
 */
Player::Player(BuffUIControl* pBuffUIControl, const GameData::PlayerData& data,const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	: 
	Character(data.maxHP,PLAYER_BASE_ATTACK,PLAYER_BASE_DIFFENCE,Tag::ObjectType::Player,parent,initialPosition,initialAngle),
	m_messageID{},
	m_sphere{ GetPosition(), PLAYER_SPHERE_SIZE },
	m_motionAngle{},
	m_pBuffUIControl{pBuffUIControl}
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	//テクスチャ設定
	SetTexture(resourceManager->RequestTexture(ResourcePath::TEXTURE::PLAYER));
	//モデル設定
	SetModel(resourceManager->RequestModel(ResourcePath::MODEL::PLAYER));

	//メッセンジャークラスに登録
	Messenger::GetInstance()->Register(GetObjectNumber(), this);
	//所持宝石クラスを生成
	m_holderGem = std::make_unique<HolderGem>(data.gemID);

	//HP調整
 	if (data.maxHP < GetMaxHP()) 
	{
		SetCurrentHP(GetCurrentHP() + GetMaxHP() - data.maxHP);
	}
	else
	{
		SetCurrentHP(data.currentHP);
	}
}

/**
 * @brief デストラクタ
 */
Player::~Player()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Player::Initialize()
{
	//右手の生成
	std::unique_ptr<Hand> handR = GameObjectFactory::CreateHand(this, this,RIGHT_HAND_INIT_POS);
	handR->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, RIGHT_HAND_Z_ANGLE));
	//左手の生成
	std::unique_ptr<Hand> handL = GameObjectFactory::CreateHand(this, this,LEFT_HAND_INIT_POS);
	//右手にピッケルを持たせる
	handR->HaveWeapon(GameObjectFactory::CreatePikle(this, handR.get()));

	// 状態の初期化
	m_idlingState		= std::make_unique<PlayerIdling>(this);
	m_movingState		= std::make_unique<PlayerMoving>(this);
	m_groundAttackState = std::make_unique<PlayerGroundAttack>(this,handR.get(),handL.get());
	m_airAttackState    = std::make_unique<PlayerAirAttack>(this,handR.get(),handL.get());
	m_jumpingState		= std::make_unique<PlayerJumping>(this);
	m_avoidState		= std::make_unique<PlayerAvoidance>(this);
	m_damagedState		= std::make_unique<PlayerDamaged>(this);

	//パーツ配列にムーブ
	m_bodyParts.emplace_back(std::move(handR));
	m_bodyParts.emplace_back(std::move(handL));

	//初期状態を設定
	SetState(m_idlingState.get());

	//初期設定
	SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	SetScale(DirectX::SimpleMath::Vector3::One);
	//当たり判定セット
	SetShape(&m_sphere);
	//ライト生成
	m_light = std::make_unique<Light>(this,DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Quaternion::Identity);
	//ライトオン
	m_light->LightOn();
	//メッセンジャークラスに登録
	Messenger::GetInstance()->RegisterLight(m_light.get());
	//アイテムゲット音
	m_getItemSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::ITEM_GET));


}



/**
 * @brief 更新処理
 *
 * @param[in] currentPosition 親の座標
 * @param[in] currentAngle    親の角度
 *
 * @return なし
 */
void Player::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();
	//状態の更新
	GetState()->Update(elapsedTime);
	//現在位置の更新
	SetCurrentPosition(currentPosition + GetPosition());
	//現在角度の更新
	SetCurrentAngle(m_motionAngle * GetQuaternion() * currentAngle);
	
	//パーツの更新
	for (std::unique_ptr<GameObject>& part : m_bodyParts)
	{
		part->Update(GetCurrentPosition(), GetCurrentQuaternion());
	}

	//ライトの更新
	m_light->Update(GetCurrentPosition(), GetCurrentQuaternion());
	//当たり判定の更新
	m_sphere.SetCenter(GetCurrentPosition());
	//取得アイテムの更新
	UpdateGotItems();
	//ダメージ演出
	DamageFlashUpdate();

	//HP自動回復の宝石をもっているか
	const std::vector<HPAutoRecoveryGem*> gems = GetHolderGem().FindHasGem<HPAutoRecoveryGem>();
	for(HPAutoRecoveryGem* gem : gems)
	{ 
		//回復値を取得
		int healValue = gem->RecoveryHP();
		if (healValue == TKTLib::INT_ZERO) 
		{
			continue;
		}

		//HPを回復
		int currentHp = GetCurrentHP() + healValue;
		//HPの最大値を超えていたら修正
		if (currentHp > GetMaxHP()) 
		{
			currentHp = GetMaxHP();
		}
		//回復したHPをセット
		SetCurrentHP(currentHp);

		//回復パーティクル生成
		ParticleManager::GetInstance()->RequestHPHealParticle(GetCurrentPosition());
	}

	//盾生成の宝石をもっているか
	const std::vector<GenerateShieldGem*> shieldGems = GetHolderGem().FindHasGem<GenerateShieldGem>();
	for (GenerateShieldGem* shieldGem : shieldGems)
	{
		//盾を生成
		int shield = shieldGem->GenerateShield();
		if (shield == 0) 
		{
			continue;
		}
		m_invincibleCount += shield;
		//盾エフェクト生成
		ParticleManager::GetInstance()->RequestShieldParticle(GetObjectNumber());
	}

	SetIsOnGround(false);
	m_attackBuffered = false;
}




/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Player::Draw()
{
	GetState()->Render();

	ShaderManager* shader = ShaderManager::GetInstance();
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale());
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ModelShader::ModelCB cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.flash.x = GetDamageFlash();

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::Model), 0, NULL, &cbuff, 0, 0);

	//アウトライン描画
	if (Messenger::GetInstance()->IsOutLineActive())
	{
		OutlineRenderer::Draw(*GetModel(), world, PLAYER_OUTLINE_THICKNESS);
	}

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
			//シェーダーの設定
			shader->StartShader(ShaderManager::Model);
			//頂点情報を設定
			context->IASetInputLayout(shader->GetInputLayout(ShaderManager::Model));
		});
	//シェーダー解放
	shader->EndShader();

	//パーツの描画
	for (std::unique_ptr<GameObject>& part : m_bodyParts)
	{
		part->Draw();
	}

#ifdef _DEBUG

	auto debugFont = Graphics::GetInstance()->GetDebugFont();
	
	//Y軸
	debugFont->AddString(L"AngleY::", DirectX::SimpleMath::Vector2(0.0f, 50.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetCurrentQuaternion().y)), DirectX::SimpleMath::Vector2(100.0f, 50.0f));
	//現在の体力
	debugFont->AddString(L"NowHP::", DirectX::SimpleMath::Vector2(0.0f, 100.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetCurrentHP())), DirectX::SimpleMath::Vector2(100.0f, 100.0f));
	//攻撃力
	debugFont->AddString(L"Attack::", DirectX::SimpleMath::Vector2(0.0f, 150.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetAttackPower())), DirectX::SimpleMath::Vector2(100.0f, 150.0f));
	//防御力
	debugFont->AddString(L"Diffence::", DirectX::SimpleMath::Vector2(0.0f, 200.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetDiffence())), DirectX::SimpleMath::Vector2(100.0f, 200.0f));
	//最大の体力
	debugFont->AddString(L"MaxHP::", DirectX::SimpleMath::Vector2(0.0f, 250.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetMaxHP())), DirectX::SimpleMath::Vector2(100.0f, 250.0f));
	//現在座標
	debugFont->AddString(L"PosX::", DirectX::SimpleMath::Vector2(0.0f, 300.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetCurrentPosition().x)), DirectX::SimpleMath::Vector2(60.0f, 300.0f));
	debugFont->AddString(L"PosY::", DirectX::SimpleMath::Vector2(0.0f, 330.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetCurrentPosition().y)), DirectX::SimpleMath::Vector2(60.0f, 330.0f));
	debugFont->AddString(L"PosZ::", DirectX::SimpleMath::Vector2(0.0f, 360.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetCurrentPosition().z)), DirectX::SimpleMath::Vector2(60.0f, 360.0f));
	//現在速度
	debugFont->AddString(L"VelX::", DirectX::SimpleMath::Vector2(0.0f, 390.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetVelocity().x)), DirectX::SimpleMath::Vector2(60.0f, 390.0f));
	debugFont->AddString(L"VelY::", DirectX::SimpleMath::Vector2(0.0f, 420.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetVelocity().y)), DirectX::SimpleMath::Vector2(60.0f, 420.0f));
	debugFont->AddString(L"VelZ::", DirectX::SimpleMath::Vector2(0.0f, 450.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetVelocity().z)), DirectX::SimpleMath::Vector2(60.0f, 450.0f));
	//ダメージ無効化回数
	debugFont->AddString(L"InvisibleCount", DirectX::SimpleMath::Vector2(0.0f, 480.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(m_invincibleCount)), DirectX::SimpleMath::Vector2(180.0f, 480.0f));
#endif // DEBUG

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Player::Finalize()
{

}


/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void Player::OnMessegeAccepted(Message::MessageID messageID)
{
	uint32_t moveFlag = GetMoveFlags();
	switch (messageID)
	{
		case Message::IDLING:
			GameObject::ChangeState(m_idlingState.get());
			break;
		case Message::MOVING:
			//攻撃・回避中ではなければ
			if (!IsAttacking() && !IsAvoidance()) 
			{
				GameObject::ChangeState(m_movingState.get());
			}
			break;
		case Message::ATTACK:
			if (IsAttacking()) 
			{
				//攻撃入力があったことを記録 コンボするため
				m_attackBuffered = true;
				
			}
			else
			{
				//攻撃状態になかったら地上か空中攻撃状態へ遷移
				if (IsOnGround()) 
				{
					GameObject::ChangeState(m_groundAttackState.get());
					break;
				}
				GameObject::ChangeState(m_airAttackState.get());
			}
			break;
		case Message::AVOIDANCE:
			GameObject::ChangeState(m_avoidState.get());
			break;
		case Message::DAMAGED:
			GameObject::ChangeState(m_damagedState.get());
			break;
		case Message::JUMPING:
			if (ReduceJumpCount()) 
			{
				GameObject::ChangeState(m_jumpingState.get());
			}
			break;
		case Message::MOVE_FRONT_ON:
			moveFlag |= Character::MoveFlag::MOVE_FRONT;
			break;
		case Message::MOVE_FRONT_OFF:
			moveFlag &= ~Character::MoveFlag::MOVE_FRONT;
			break;
		case Message::MOVE_LEFT_ON:
			moveFlag |= Character::MoveFlag::MOVE_LEFT;
			break;
		case Message::MOVE_LEFT_OFF:
			moveFlag &= ~Character::MoveFlag::MOVE_LEFT;
			break;
		case Message::MOVE_RIGHT_ON:
			moveFlag |= Character::MoveFlag::MOVE_RIGHT;
			break;
		case Message::MOVE_RIGHT_OFF:
			moveFlag &= ~Character::MoveFlag::MOVE_RIGHT;
			break;
		case Message::MOVE_BACK_ON:
			moveFlag |= Character::MoveFlag::MOVE_BACK;
			break;
		case Message::MOVE_BACK_OFF:
			moveFlag &= ~Character::MoveFlag::MOVE_BACK;
			break;
		default:
			break;
	}

	SetMoveFlags(moveFlag);
}

/**
 * @brief 衝突応答
 *
 * @param[in] other 衝突したオブジェクト
 *
 * @return なし
 */
void Player::CollisionResponce(GameObject* other)
{
	switch (other->GetObjectType())
	{
		case Tag::ObjectType::Enemy:
		{
			//ダメージを受けない
			if (GetState() == m_damagedState.get() || GetState() == m_avoidState.get())
			{
				break;
			}
			//ダメージ
			OnDamage(other);
		}
		break;

		case Tag::ObjectType::ObjectPart:
		{
			if (GetState() == m_damagedState.get())
			{
				break;
			}

			//HPをもつオブジェクトを取得
			GameObject* root = dynamic_cast<EnemyPart*>(other)->GetRootCharacter();
			OnDamage(root);
		}
		break;

		case Tag::ObjectType::Ground:
		{
			//ステージとの衝突応答　押し出し
			DirectX::SimpleMath::Vector3 newPosition = CollisionManager::GetInstance()->PushOut(other->GetShape(), &m_sphere);

			SetPosition(newPosition);
			SetIsOnGround(true);
			//Yの速度をリセット
			DirectX::SimpleMath::Vector3 velocity = GetVelocity();
			velocity.y = 0.0f;
			SetVelocity(velocity);
			//ジャンプ回数をリセット
			ResetJumpCount();
			//ジャンプ状態・空中攻撃状態なら待機状態へ移行
			if (GetState() == m_jumpingState.get() || GetState() == m_airAttackState.get()) 
			{
				OnMessegeAccepted(Message::IDLING);
			}
			
			DirectX::SimpleMath::Vector3 playerPos = GetCurrentPosition();
			//足元に調整
			playerPos.y = 0.0f;

			//土埃パーティクル生成
			ParticleManager::GetInstance()->RequestMoveDustParticle(playerPos);

		}
		break;

		case Tag::ObjectType::Wall:
		{
			
			if (m_sphere.Contains(other->GetShape())) 
			{
				break;
			}


			//ステージとの衝突応答　押し出し
			SetPosition(CollisionManager::GetInstance()->PushBack(&m_sphere ,dynamic_cast<Sphere*>(other->GetShape())));
			//座標更新
			m_sphere.SetCenter(GetPosition());

			//ジャンプ状態・空中攻撃状態なら待機状態へ移行
			if (GetState() == m_jumpingState.get() || GetState() == m_airAttackState.get()) 
			{
				OnMessegeAccepted(Message::IDLING);
			}
			

		}
		break;


		case::Tag::ObjectType::Item: 
		{
			//アイテム取得音再生
			m_getItemSound->Play(false);
			//Item型へキャスト
			Item* item = other->Cast<Item>();
			if (item == nullptr) 
			{
				return;
			}
			//取得アイテムリストに追加
			m_gotItems.emplace_back(item->GetItemInfo());
			//得たバフのアイコンを表示する
			m_pBuffUIControl->AddUI(m_gotItems.back().type,m_gotItems.back().time);
			ParticleManager::GetInstance()->RequestPowerUpParticle(GetCurrentPosition(),item->GetColor());
		}
		break;

		case Tag::ObjectType::Light: 
		{
			//ライトオブジェクトとの衝突応答　押し出し
			SetPosition(CollisionManager::GetInstance()->PushOut(other->GetShape(), &m_sphere));
			
			ResetJumpCount();

		}
		break;
	default:
		break;
	}
}

/**
 * @brief ダメージ処理
 *
 * @param[in] attacker  攻撃してきたオブジェクト
 *
 * @return ダメージ量
 */
int Player::TakeDamage(const Character* attacker)
{	
	//ダメージを無効化できる回数があるなら無効化
	if (m_invincibleCount > 0)
	{
		//回数減少
		m_invincibleCount--;
		//盾エフェクト消去
		ParticleManager::GetInstance()->DeleteShieldParticle(GetObjectNumber());

		return 0;
	}

	return Character::TakeDamage(attacker);
}


/**
 * @brief 宝石による強化量を考慮した最大HPを取得
 *
 * @param[in] なし
 *
 * @return 最大HP
 */
const int Player::GetMaxHP() const
{
	return  GemPlusStatus(Gem::Type::HP)+/*ItemBuff(Item::EffectType::HP) +*/ Character::GetMaxHP();
}

/**
 * @brief 宝石による強化量を考慮した攻撃力を取得
 *
 * @param[in] なし
 *
 * @return 攻撃力
 */
const int Player::GetAttackPower() const
{
	return GemPlusStatus(Gem::Type::STR) + ItemBuff(Item::EffectType::Attack) + Character::GetAttackPower();
}

/**
 * @brief 宝石による強化量を考慮した防御力を取得
 *
 * @param[in] なし
 *
 * @return 防御力
 */
const int Player::GetDiffence()
{
	return GemPlusStatus(Gem::Type::DEF) + ItemBuff(Item::EffectType::Diffece) + Character::GetDiffence();
}


/**
 * @brief ジャンプできる残り回数を取得
 *
 * @param[in] なし
 *
 * @return ジャンプできる残り回数
 */
const int Player::GetRemainingJumpCount() const
{
	return m_remainingJumpCount;
}


/**
 * @brief モーションの角度を取得
 *
 * @param[in] なし
 *
 * @return モーションの角度
 */
DirectX::SimpleMath::Quaternion Player::GetMotionAngle() const
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
void Player::SetMotionAngle(const DirectX::SimpleMath::Quaternion& angle)
{
	m_motionAngle = angle;
}

/**
 * @brief 所持宝石を取得
 *
 * @param[in] なし
 *
 * @return 所持宝石リスト
 */
const HolderGem& Player::GetHolderGem()
{
	return *m_holderGem.get();
}

/**
 * @brief 回避中か取得
 *
 * @param[in] なし
 *
 * @return true  回避中
 * @return false 回避していない
 */
bool Player::IsAvoidance()
{
	return (GetState() == m_avoidState.get());
}


/**
 * @brief 攻撃中か取得
 *
 * @param[in] なし
 *
 * @return true  攻撃中
 * @return false 攻撃していない
 */
bool Player::IsAttacking() 
{
	return (GetState() == m_airAttackState.get() || GetState() == m_groundAttackState.get());
}


/**
 * @brief 攻撃入力があったか
 *
 * @param[in] なし
 *
 * @return true  攻撃入力アリ
 * @return false 攻撃入力なし
 */
bool Player::IsAttackBuffered() const
{
	return m_attackBuffered;
}

/**
 * @brief ジャンプできる残り回数を減らす
 *
 * @param[in] なし
 *
 * @return true  ジャンプ出来る
 * @return false ジャンプ出来ない
 */
bool Player::ReduceJumpCount()
{
	//残り回数がないなら偽を返す
	if (m_remainingJumpCount == 0)
	{
		return false;
	}

	m_remainingJumpCount--;

	return true;
}


/**
 * @brief ジャンプ出来る残り回数をリセット
 *
 * @param[in] なし
 *
 * @return なし
 */
void Player::ResetJumpCount()
{
	m_remainingJumpCount = REMAINING_JUMP;
}


/**
 * @brief 取得したアイテムの更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void Player::UpdateGotItems()
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();

	for (Item::ItemInfo& iteminfo : m_gotItems)
	{
		//制限時間を減らす
		iteminfo.time -= elapsedTime;
		//アウトラインのアイテムなら
		if (iteminfo.type == Item::EffectType::Outline && iteminfo.time <= 0) 
		{
			Messenger::GetInstance()->SetOutLineActive(false);
		}
	}

	//効果時間が0になったものを消す
	m_gotItems.remove_if([](Item::ItemInfo& iteminfo) {return iteminfo.time < 0.0f; });
}


/**
 * @brief 宝石による強化量を取得
 *
 * @param[in] type 取得するステータス
 *
 * @return 強化量
 */
int Player::GemPlusStatus(const Gem::Type& type) const
{
	//プレイヤーの持つ宝石を管理クラスから取得
	auto& holdGems = m_holderGem->GetGems();
	//強化値の合計
	int total = 0;

	//所持できる数だけ処理する（３回）
	for (int i = 0; i < holdGems.size(); i++)
	{
		//空なら飛ばす
		if (!holdGems[i])
		{
			continue;
		}

		//所持している宝石が指定されたステータスを強化するものか
		if (holdGems[i]->GetAbility().powerUp == type)
		{
			//HPが満タンのときに効果を適用する宝石か
			if (const FullHPStatusUpGem* gem = dynamic_cast<const FullHPStatusUpGem*>(holdGems[i].get())) 
			{
				//効果を適用していいか判断
				if (gem->IsApplicable(GetCurrentHP(), GetMaxHP())) 
				{
					//効果を適用
					total += gem->GetAbility().value;
				}
				//加算したの次
				continue;
			}
			//普通のステータス強化の宝石なので普通に加算
			total += holdGems[i]->GetAbility().value;

		}
	}

	return total;
}


/**
 * @brief アイテムによる強化量を取得
 *
 * @param[in] upStatus 取得するステータス
 *
 * @return 強化量
 */
int Player::ItemBuff(const Item::EffectType& upStatus) const
{
	int total = 0;

	for (Item::ItemInfo itemInfo : m_gotItems) 
	{
		//指定されたステータスを強化するものか
		if (itemInfo.type != upStatus)
		{
			continue;
		}

		total += itemInfo.increase;
	}
	return total;
}

