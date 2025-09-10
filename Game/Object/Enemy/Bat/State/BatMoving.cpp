/**
 * @file   BatMoving.cpp
 *
 * @brief  コウモリの移動状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2025/09/03
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Bat/State/BatMoving.h"
#include "Game/Object/Enemy/Bat/Bat.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player プレイヤーのポインタ
 */
BatMoving::BatMoving(Bat* bat)
	: m_bat(bat)
	, m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
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
	//８方向から進む方向を決める
	float directionX = TKTLib::GetRand(-1.0f,1.0f);
	float directionZ = TKTLib::GetRand(-1.0f,1.0f);

	DirectX::SimpleMath::Vector3 direction = { directionX,0.0f,directionZ };

	direction.Normalize();

	// X-Z 平面上での角度を計算
	float angle = std::atan2(-direction.z, direction.x);

	//目標の角度
	DirectX::SimpleMath::Quaternion rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, angle);

	m_bat->SetQuaternion(rotate);

	//m_bat->SetVelocity(direction);

	//向いている方向に進む
	m_bat->SetVelocity(DirectX::SimpleMath::Vector3::Transform(Character::MOVE::FRONT * 5.0f * Messenger::GetInstance()->GetElapsedTime(), m_bat->GetQuaternion()));

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


	m_bat->SetPosition(m_bat->GetPosition() + m_bat->GetVelocity());

	//一定時間経ったら待機状態へ遷移
	if (m_bat->GetFrameCount() >= 2.0f) 
	{
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::IDLING);

	}


	//プレイヤーを取得
	GameObject* pPlayer = Messenger::GetInstance()->GetObject(0);
	//プレイヤーか確認
	if (pPlayer && pPlayer->GetObjectType() == Tag::Player)
	{
		//現在位置とプレイヤーの位置の距離
		DirectX::SimpleMath::Vector3 playerPos = pPlayer->GetCurrentPosition();
		float distance = DirectX::SimpleMath::Vector3::Distance(playerPos, m_bat->GetCurrentPosition());
		//範囲内なら遷移
		if (distance < 15.0f)
		{
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
