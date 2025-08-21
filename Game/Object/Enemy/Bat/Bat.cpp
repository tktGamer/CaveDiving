/**
 * @file   Bat.cpp
 *
 * @brief  コウモリの敵に関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Bat.h"
#include "Game/Common/Collision/CollisionManager.h"
#include"../CaveDiving/Game/Fuctory/CharacterFactory.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Bat::Bat(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:m_graphics{Graphics::GetInstance()}
	, Character(50,5,15,Tag::ObjectType::Enemy, parent, initialPosition, initialAngle)
	, m_objectNumber{ CountUpNumber() }
	, m_sphere{ GetPosition(), 2.0f } // 初期位置とサイズを設定
	, m_isAlive{ true }
{
	SetTexture(ResourceManager::GetInstance()->RequestTexture("bat.png"));

	SetModel(ResourceManager::GetInstance()->RequestModel(L"bat.sdkmesh"));

	SetShape(&m_sphere);

	m_leftWing = std::make_unique<Wing>(this, DirectX::SimpleMath::Vector3{-0.5f,0.0f,0.0f}, DirectX::XMConvertToRadians(0.0f));
	m_rightWing = std::make_unique<Wing>(this, DirectX::SimpleMath::Vector3{0.5f,0.0f,0.0f}, DirectX::XMConvertToRadians(180.0f));



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
	m_idlingState = std::make_unique<BatIdling>(this);
	m_movingState = std::make_unique<BatMoving>(this);
	m_attackState = std::make_unique<BatAttack>(this);
	SetState(m_idlingState.get());


	SetPosition(DirectX::SimpleMath::Vector3(0.0f, 1.0f, -5.0f));
	SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	SetScale(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));

}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Bat::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	//生きていない場合更新しない
	if (!m_isAlive)
	{
		return;
	}


	//現在の状態を更新
	GetState()->Update(elapsedTime);


	m_currentPosition = m_initialPosition + currentPosition + GetPosition();
	m_currentAngle = GetQuaternion() * currentAngle;
	m_sphere.SetCenter(m_currentPosition);

	m_leftWing->Update(elapsedTime, GetCurrentPosition(), GetCurrentQuaternion());
	m_rightWing->Update(elapsedTime, GetCurrentPosition(), GetCurrentQuaternion());
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
	if (!m_isAlive) 
	{
		return;
	}


	//現在の状態を描画
	GetState()->Render();

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

void Bat::OnMessegeAccepted(Message::MessageID messageID)
{
}

void Bat::CollisionResponce(GameObject* other)
{
	switch (other->GetObjectType())
	{
		case Tag::ObjectType::Player:
		{
			// プレイヤーとの衝突処理
			// ここでは何もしないが、必要に応じて実装
			break;
		}
		case Tag::ObjectType::Stage:
		{
			//ステージとの衝突応答　押し出し
			SetPosition(CollisionManager::GetInstance()->PushOut(dynamic_cast<Box*>(other->GetShape()), &m_sphere));
			//速度をリセット
			m_velocity.y = 0.0f;

			break;
		}
		case Tag::ObjectType::Pikel:
		{
			//ピッケルとの衝突応答
			//管理クラスに削除依頼を出す
			m_isAlive = false;

			break;
		}
	default:
		break;
	}
}


int Bat::GetObjectNumber()
{
	return m_objectNumber;
}

DirectX::SimpleMath::Vector3 Bat::GetVelocity()
{
	return m_velocity;
}

void Bat::SetVelocity(DirectX::SimpleMath::Vector3 v)
{
	m_velocity = v;
}

bool Bat::IsAlive() const
{
	return m_isAlive;
}
