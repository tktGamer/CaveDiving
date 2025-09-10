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
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] modelParms モデルパラメータ
 */
Player::Player(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	: Character(100,20,7,Tag::ObjectType::Player,parent,initialPosition,initialAngle)
	, m_messageID{  }
	, m_velocity{ 0.0f, 0.0f, 0.0f }
	, m_initialeDirection{ 0.0f, 0.0f, -1.0f }
	, m_sphere{ GetPosition(), 2.0f }
	,m_remainingJumpCount{1}
	,m_motionAngle{}
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
	std::unique_ptr<Hand> handR = std::make_unique<Hand>(this, DirectX::SimpleMath::Vector3{ 1.5f,0.0f,0.0f }, DirectX::XMConvertToRadians(0.0f));
	std::unique_ptr<Hand> handL = std::make_unique<Hand>(this, DirectX::SimpleMath::Vector3{ -1.5f,0.0f,0.0f }, DirectX::XMConvertToRadians(0.0f));
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
	m_bodyParts.back()->Initialize();
	m_bodyParts.emplace_back(std::move(handL));

	//初期状態を設定
	SetState(m_idlingState.get());

	
	SetTexture(ResourceManager::GetInstance()->RequestTexture("player.png"));

	SetModel(ResourceManager::GetInstance()->RequestModel(L"player.sdkmesh"));
	SetPosition(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f));
	SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	SetScale(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));

	SetShape(&m_sphere);

	m_light = std::make_unique<Light>(this,GetPosition(),DirectX::XMConvertToRadians(0.0f));

	Shader::GetInstance()->RegisterLight(m_light.get());

	//SetMaxHP(100);
	SetCurrentHP();
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
void Player::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	
	//向きを変える
	ChangeDirection();

	//状態の更新
	GetState()->Update(elapsedTime);
	//当たり判定の更新
	m_sphere.SetCenter(currentPosition + GetPosition());


	m_light->Update(elapsedTime,currentPosition + GetPosition(), currentAngle * GetQuaternion());

	//現在位置の更新
	m_currentPosition = currentPosition + GetPosition();
	//現在角度の更新
	m_currentAngle =  m_motionAngle * GetQuaternion() *  currentAngle ;
	
	//パーツの更新
	for (std::unique_ptr<GameObject>& part : m_bodyParts)
	{
		part->Update(elapsedTime,m_currentPosition,m_currentAngle);
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

	Shader* shader = Shader::GetInstance();
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
			if (GetState() == m_damagedState.get())
			{
				break;
			}

			OnDamage(other);
		}
		break;
		case Tag::ObjectType::Stage:
		{
			//ステージとの衝突応答　押し出し
			SetPosition(CollisionManager::GetInstance()->PushOut(dynamic_cast<Box*>(other->GetShape()), &m_sphere));
			//速度をリセット
			m_velocity.y = 0.0f;
			ResetJumpCount();
			//ジャンプ状態・空中攻撃状態なら待機状態へ移行
			if (GetState() == m_jumpingState.get() || GetState() == m_airAttackState.get()) 
			{
				OnMessegeAccepted(Message::IDLING);
			}
			

			break;
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
	return  Character::GetMaxHP()+ GetPlusStatus(Gem::Type::HP);
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
	return GetPlusStatus(Gem::Type::STR) + Character::GetAttackPower();
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
	return GetPlusStatus(Gem::Type::DEF)+ Character::GetDiffence();
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

	if (key->GetLastState().A)
	{
		//左旋回
		rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f*elapsedTime));
	}
	if (key->GetLastState().D)
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
int Player::GetPlusStatus(const Gem::Type type)
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
		if (holdGems[i]->GetAbility().m_type == type) 
		{
			total += holdGems[i]->GetAbility().m_value;
		}
	}

	return total;
}

