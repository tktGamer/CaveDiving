/**
 * @file   BatMoving.cpp
 *
 * @brief  コウモリの移動状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Bat/State/BatMoving.h"
#include "Game/Object/Enemy/Bat/Bat.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] bat コウモリのポインタ
 */
BatMoving::BatMoving(Bat* bat)
	: 
	m_bat(bat)
{
}

/**
 * @brief デストラクタ
 */
BatMoving::~BatMoving()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::Initialize()
{
	PreUpdate();
}

/**
 * @brief 事前処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::PreUpdate()
{
	//進む方向を決める
	float directionX = static_cast<float>(TKTLib::GetRand(Character::MOVE::LEFT.x,Character::MOVE::RIGHT.x));
	float directionZ = static_cast<float>(TKTLib::GetRand(Character::MOVE::FRONT.z,Character::MOVE::BACK.z));

	DirectX::SimpleMath::Vector3 direction = { directionX,0.0f,directionZ };

	direction.Normalize();

	// X-Z 平面上での角度を計算
	float angle = std::atan2(-direction.z, direction.x);

	//目標の角度
	DirectX::SimpleMath::Quaternion rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, angle);
	m_bat->SetLocalQuaternion(rotate);

	//向いている方向に進む
	m_bat->SetVelocity(DirectX::SimpleMath::Vector3::Transform(Character::MOVE::FRONT * MOVING_SPEED *
		Messenger::GetInstance()->GetElapsedTime(), m_bat->GetLocalQuaternion()));
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	//座標更新
	m_bat->SetLocalPosition(m_bat->GetLocalPosition() + m_bat->GetVelocity());

	//一定時間経ったら遷移
	if (m_bat->GetFrameCount() >= CHANGE_IDLING_TIME) 
	{
		//待機状態へ
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::IDLING);
	}

	//プレイヤーを取得
	Messenger* messenger = Messenger::GetInstance();
	GameObject* pPlayer = messenger->GetObject(messenger->GetPlayerObjectID());
	//プレイヤーか確認
	if (pPlayer && pPlayer->GetObjectType() == Tag::Player)
	{
		//現在位置とプレイヤーの位置の距離
		DirectX::SimpleMath::Vector3 playerPos = pPlayer->Cast<GameObject3D>()->GetCurrentPosition();
		float distance = DirectX::SimpleMath::Vector3::Distance(playerPos, m_bat->GetCurrentPosition());
		//範囲内なら遷移
		if (distance < Bat::CHASE_RANGE)
		{
			//追跡状態へ
			Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::CHASING);
		}
	}
}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::PostUpdate()
{
	//経過時間リセット
	m_bat->ResetFrameCount();
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::Render()
{
#ifdef _DEBUG
#endif // DEBUG
}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::Finalize()
{
}