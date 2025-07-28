/**
 * @file   Player.cpp
 *
 * @brief  ＸＸＸＸに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Player.h"

#include "Game/Interface/IState.h"
#include"Game/Shader.h"
#include"Game/Common/Collision/Sphere.h"


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] modelParms モデルパラメータ
 */
Player::Player(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	: GameObject(Tag::ObjectType::Player,parent,initialPosition,initialAngle)
	, m_objectNumber{ CountUpNumber() }
	, m_messageID{  }
	, m_hp{100}
	, m_velocity{ 0.0f, 0.0f, 0.0f }
	, m_pGem{}
	, m_initialeDirection{ 0.0f, 0.0f, -1.0f }
	, m_sphere{ GetPosition(), 2.0f }
{
	Messenger::GetInstance()->Register(m_objectNumber, this);
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
	std::unique_ptr<Hand> handR = std::make_unique<Hand>(this, DirectX::SimpleMath::Vector3{ 1.5f,0.0f,0.0f }, DirectX::XMConvertToRadians(0.0f));
	std::unique_ptr<Hand> handL = std::make_unique<Hand>(this, DirectX::SimpleMath::Vector3{ -1.5f,0.0f,0.0f }, DirectX::XMConvertToRadians(0.0f));
	// 状態の初期化
	m_idlingState = std::make_unique<PlayerIdling>(this);
	m_movingState = std::make_unique<PlayerMoving>(this);
	m_attackState = std::make_unique<PlayerAttack>(this,handR.get());

	m_bodyParts.emplace_back(std::move(handR));
	m_bodyParts.back()->Initialize();
	m_bodyParts.push_back(std::make_unique<Hand>(this, DirectX::SimpleMath::Vector3{ -1.5f,0.0f,0.0f }, DirectX::XMConvertToRadians(0.0f)));
	SetState(m_idlingState.get());

	SetTexture(ResourceManager::GetInstance()->RequestTexture("player.png"));

	SetModel(ResourceManager::GetInstance()->RequestModel(L"player.sdkmesh"));
	SetPosition(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f));
	SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	SetScale(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));

	SetShape(&m_sphere);

	m_light = std::make_unique<Light>(this,GetPosition(),DirectX::XMConvertToRadians(0.0f));

	Shader::GetInstance()->RegisterLight(m_light.get());



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
	DirectX::Keyboard::KeyboardStateTracker* traker = Graphics::GetInstance()->GetKeyboardTracker();

	GetState()->Update(elapsedTime);
	m_sphere.SetCenter(currentPosition + GetPosition());
	m_light->Update(elapsedTime,currentPosition + GetPosition(), currentAngle * GetQuaternion());

	m_currentPosition = currentPosition + GetPosition();
	m_currentAngle = currentAngle * GetQuaternion();
	

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

	auto debugFont = Graphics::GetInstance()->GetDebugFont();

	debugFont->AddString(TKTLib::StringToWchar(std::to_string(m_currentAngle.y)), DirectX::SimpleMath::Vector2(50.0f, 250.0f));

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
	case Message::ATTACK:
		GameObject::ChangeState(m_attackState.get());
		break;
	case Message::AVOIDANCE:
		break;
	case Message::DAMAGED:
		break;
	default:
		break;
	}
}


void Player::SetGem(Gem* gem, int index)
{
	m_pGem[index] = gem;
}

int Player::GetObjectNumber()
{
	return m_objectNumber;
}

DirectX::SimpleMath::Vector3 Player::GetVelocity()
{
	return m_velocity;
}

void Player::SetVelocity(DirectX::SimpleMath::Vector3 v)
{
	m_velocity = v;
}
