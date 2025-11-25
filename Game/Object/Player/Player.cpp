/**
 * @file   Player.cpp
 *
 * @brief  プレイヤーに関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　　2025/09/08
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Player.h"

#include "Game/Interface/IState.h"
#include"Game/Shader.h"
#include"Game/Common/Collision/Sphere.h"
#include"Game/Common/Collision/CollisionManager.h"
#include"../Gem/GemManager.h"
#include"Game/Common/DamageSystem.h"
#include"Game/Fuctory/GameObjectFactory.h"
#include"Game/Particle/ParticleManager.h"
#include"Game/UI/Buff/BuffUIControl.h"
#include"Game/Object/Gem/Unique/HPAutoRecoveryGem.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] modelParms モデルパラメータ
 */
Player::Player(BuffUIControl* pBuffUIControl, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	: Character(100,20,7,Tag::ObjectType::Player,parent,initialPosition,initialAngle)
	, m_messageID{  }
	, m_velocity{ 0.0f, 0.0f, 0.0f }
	, m_initialeDirection{ 0.0f, 0.0f, -1.0f }
	, m_sphere{ GetPosition(), 2.0f }
	,m_remainingJumpCount{1}
	,m_motionAngle{}
	,m_pBuffUIControl{pBuffUIControl}
{
	Messenger::GetInstance()->Register(GetObjectNumber(), this);
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
	//手の生成
	std::unique_ptr<Hand> handR = GameObjectFactory::CreateHand(this, this, DirectX::SimpleMath::Vector3{ 1.5f,0.0f,0.0f }, DirectX::SimpleMath::Quaternion::Identity);
	std::unique_ptr<Hand> handL = GameObjectFactory::CreateHand(this, this, DirectX::SimpleMath::Vector3{-1.5f,0.0f,0.0f }, DirectX::SimpleMath::Quaternion::Identity);

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
	//m_bodyParts.back()->Initialize();
	m_bodyParts.emplace_back(std::move(handL));

	//初期状態を設定
	SetState(m_idlingState.get());

	
	SetTexture(ResourceManager::GetInstance()->RequestTexture("player.png"));

	SetModel(ResourceManager::GetInstance()->RequestModel(L"player.sdkmesh"));
	SetPosition(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f));
	SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	SetScale(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));

	SetShape(&m_sphere);

	m_light = std::make_unique<Light>(this,GetPosition(),DirectX::SimpleMath::Quaternion::Identity);
	m_light->LightOn();
	Shader::GetInstance()->RegisterLight(m_light.get());

	m_getItemSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(L"getitem.wav"));
}



/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime     フレーム間時間
 * @param[in] currentPosition 親の座標
 * @param[in] currentAngle    親の角度
 *
 * @return なし
 */
void Player::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();

	//向きを変える
	ChangeDirection();

	//状態の更新
	GetState()->Update(elapsedTime);
	//当たり判定の更新
	m_sphere.SetCenter(currentPosition + GetPosition());


	DamageFlashUpdate();

	m_light->Update(currentPosition + GetPosition(), currentAngle * GetQuaternion());

	//取得アイテムの更新
	UpdateGotItems();

	//現在位置の更新
	m_currentPosition = currentPosition + GetPosition();
	//現在角度の更新
	m_currentAngle =  m_motionAngle * GetQuaternion() *  currentAngle ;
	
	//パーツの更新
	for (std::unique_ptr<GameObject>& part : m_bodyParts)
	{
		part->Update(m_currentPosition,m_currentAngle);
	}


	//ParticleManager::GetInstance()->RequestDamageParticle({0,3,0}, {1,1,1,1}, 103);


	//HP自動回復の宝石をもっているか
	std::vector<HPAutoRecoveryGem*> gems = GemManager::GetInstance()->IsHasGem<HPAutoRecoveryGem>();
	for(HPAutoRecoveryGem* gem : gems)
	{
		//回復したHPをセット
		SetCurrentHP( gem->RecoveryHP(GetCurrentHP(), GetMaxHP()));
	}
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

	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Player::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale()).Transpose();
	cbuff.matView = graphics->GetViewMatrix().Transpose();
	cbuff.matProj = graphics->GetProjectionMatrix().Transpose();
	cbuff.color.x = GetDamageFlash();

	Shader* shader = Shader::GetInstance();
	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(Shader::Model), 0, NULL, &cbuff, 0, 0);


	Player::OutlineConstBuffer outline;
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
	//GetModel()->Draw(context, *states, world, view, proj, false, [&]()
	//	{
	//		//	モデル表示をするための自作シェーダに関連する設定を行う


	//		//	画像用サンプラーの登録
	//		ID3D11SamplerState* sampler[1] = { states->PointWrap() };
	//		context->PSSetSamplers(0, 1, sampler);

	//		if (GetTexture() != nullptr)
	//		{
	//			//	読み込んだ画像をピクセルシェーダに伝える
	//			//	自作VSはt0を使っているため、
	//			//	t0がメインで使われていると勝手に想定。
	//			context->PSSetShaderResources(0, 1, GetTexture());
	//		}

	//		//	半透明描画指定
	//		ID3D11BlendState* blendstate = states->NonPremultiplied();

	//		//	透明判定処理
	//		context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//		//	深度バッファに書き込み参照する
	//		context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//		//	カリングはなし
	//		context->RSSetState(states->CullCounterClockwise());

	//		//シェーダーの設定
	//		Shader::GetInstance()->StartShader(Shader::Outline, shader->GetCBuffer(Shader::Outline));

	//		//頂点情報を設定
	//		context->IASetInputLayout(shader->GetInputLayout(Shader::Outline));

	//	});
	//Shader::GetInstance()->EndShader();
	
	
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
			Shader::GetInstance()->StartShader(Shader::Model, shader->GetCBuffer(Shader::Model));

			//頂点情報を設定
			context->IASetInputLayout(shader->GetInputLayout(Shader::Model));

		});
	Shader::GetInstance()->EndShader();


	auto debugFont = Graphics::GetInstance()->GetDebugFont();
	
	//Y軸
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(m_currentAngle.y)), DirectX::SimpleMath::Vector2(50.0f, 50.0f));
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
	debugFont->AddString(L"X::", DirectX::SimpleMath::Vector2(0.0f, 300.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetCurrentPosition().x)), DirectX::SimpleMath::Vector2(25.0f, 300.0f));
	debugFont->AddString(L"Y::", DirectX::SimpleMath::Vector2(0.0f, 330.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetCurrentPosition().y)), DirectX::SimpleMath::Vector2(25.0f, 330.0f));
	debugFont->AddString(L"Z::", DirectX::SimpleMath::Vector2(0.0f, 360.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetCurrentPosition().z)), DirectX::SimpleMath::Vector2(25.0f, 360.0f));

	//パーツの描画
	for (std::unique_ptr<GameObject>& part : m_bodyParts) 
	{
		part->Draw();
	}
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
	switch (messageID)
	{
		case Message::IDLING:
			GameObject::ChangeState(m_idlingState.get());
			break;
		case Message::MOVING:
			GameObject::ChangeState(m_movingState.get());
			break;
		case Message::GROUNDATTACK:
			GameObject::ChangeState(m_groundAttackState.get());
			break;
		case Message::AIRATTACK:
			GameObject::ChangeState(m_airAttackState.get());
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
void Player::CollisionResponce(GameObject* other)
{
	switch (other->GetObjectType())
	{
		case Tag::ObjectType::Enemy:
		{
			if (GetState() == m_damagedState.get() || GetState() == m_avoidState.get())
			{
				break;
			}

			DirectX::SimpleMath::Vector3 contactPos = CollisionManager::GetInstance()->CheckContactPoint(dynamic_cast<Sphere*>(GetShape()), dynamic_cast<Sphere*>(other->GetShape()));
			//ダメージ
			OnDamage(other);


			//ParticleManager::GetInstance()->RequestDamageParticle(contactPos, DirectX::SimpleMath::Vector3{ 2,2,2 }, 10);
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
			SetPosition(CollisionManager::GetInstance()->PushOut(dynamic_cast<Box*>(other->GetShape()), &m_sphere,GetVelocity()));

			//速度をリセット
			m_velocity.y = 0.0f;
			ResetJumpCount();
			//ジャンプ状態・空中攻撃状態なら待機状態へ移行
			if (GetState() == m_jumpingState.get() || GetState() == m_airAttackState.get()) 
			{
				OnMessegeAccepted(Message::IDLING);
			}
			
			DirectX::SimpleMath::Vector3 playerPos = GetCurrentPosition();
			//足元に調整
			playerPos.y = 0.0f;


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
			SetPosition(CollisionManager::GetInstance()->PushBack(&m_sphere,dynamic_cast<Sphere*>( other->GetShape())));

			m_sphere.SetCenter(GetPosition());

			//速度をリセット
			//m_velocity.y = 0.0f;
			//ResetJumpCount();
			//ジャンプ状態・空中攻撃状態なら待機状態へ移行
			if (GetState() == m_jumpingState.get() || GetState() == m_airAttackState.get()) 
			{
				OnMessegeAccepted(Message::IDLING);
			}
			

		}
		break;


		case::Tag::ObjectType::Item: 
		{
			m_getItemSound->Play(false);
			//Item型へキャスト
			Item* item = other->Cast<Item>();

			m_gotItems.emplace_back(ItemInfo{ item->GetUpStatus(),item->GetIncrease(),item->GetTime() });
			m_pBuffUIControl->AddUI(m_gotItems.back().upStatus,m_gotItems.back().time);
			//得たバフのアイコンを表示する
			ParticleManager::GetInstance()->RequestPowerUpParticle( GetCurrentPosition(),item->GetColor());
		}
		break;

		case Tag::ObjectType::Light: 
		{
			//ライトオブジェクトとの衝突応答　押し出し
			SetPosition(CollisionManager::GetInstance()->PushOut(dynamic_cast<Box*>(other->GetShape()), &m_sphere, GetVelocity()));
			
			ResetJumpCount();

		}
	default:
		break;
	}
}



DirectX::SimpleMath::Vector3 Player::GetVelocity()
{
	return m_velocity;
}

void Player::SetVelocity(const DirectX::SimpleMath::Vector3& v)
{
	m_velocity = v;
}

/**
 * @brief 宝石による強化量を考慮した最大HPを取得
 *
 * @param[in] なし
 *
 * @return 最大HP
 */
const int Player::GetMaxHP()
{
	return  GemPlusStatus(Gem::Type::HP)+/*ItemBuff(Item::UpStatus::HP) +*/ Character::GetMaxHP();
}

/**
 * @brief 宝石による強化量を考慮した攻撃力を取得
 *
 * @param[in] なし
 *
 * @return 攻撃力
 */
const int Player::GetAttackPower()
{
	return GemPlusStatus(Gem::Type::STR) + ItemBuff(Item::UpStatus::Attack) + Character::GetAttackPower();
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
	return GemPlusStatus(Gem::Type::DEF)+ ItemBuff(Item::UpStatus::Diffece) + Character::GetDiffence();
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
	m_remainingJumpCount = 1;
}


void Player::UpdateGotItems()
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();
	for (ItemInfo& iteminfo : m_gotItems) 
	{
		//制限時間を減らす
		iteminfo.time -= elapsedTime;

	}

	//効果時間が0になったものを消す
	m_gotItems.remove_if([](ItemInfo iteminfo) {return iteminfo.time < 0.0f; });
}

/**
 * @brief 方向を変える
 *
 * @param[in] なし
 *
 * @return なし
 */
void Player::ChangeDirection()
{
	DirectX::Keyboard::KeyboardStateTracker* key = Graphics::GetInstance()->GetKeyboardTracker();
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();

	DirectX::SimpleMath::Quaternion rotate = DirectX::SimpleMath::Quaternion::Identity;

	if (key->GetLastState().LeftShift)
	{
		//左旋回
		rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f*elapsedTime));
	}
	if (key->GetLastState().C)
	{
		//右旋回
		rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-180.0f*elapsedTime));
	}

	// 姿勢に回転を加える
	SetQuaternion(GetQuaternion() * rotate);

}

/**
 * @brief 宝石による強化量を取得
 *
 * @param[in] type 取得するステータス
 *
 * @return 強化量
 */
int Player::GemPlusStatus(const Gem::Type type)
{
	//プレイヤーの持つ宝石を管理クラスから取得
	const Gem*const* holdGems = GemManager::GetInstance()->GetPlayerHoldGem();
	//強化値の合計
	int total = 0;

	//所持できる数だけ処理する（３回）
	for (int i = 0; i < 3; i++) 
	{
		//空なら飛ばす
		if (!holdGems[i])
		{
			continue;
		}

		//所持している宝石が指定されたステータスを強化するものか
		if (holdGems[i]->GetAbility().powerUp == type) 
		{
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
int Player::ItemBuff(const Item::UpStatus& upStatus)
{
	int total = 0;

	for (ItemInfo itemInfo : m_gotItems) 
	{
		//指定されたステータスを強化するものか
		if (itemInfo.upStatus != upStatus)
		{
			continue;
		}

		total += itemInfo.increase;
	}
	return total;
}

