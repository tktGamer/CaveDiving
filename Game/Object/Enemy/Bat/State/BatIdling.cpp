/**
 * @file   BatIdling.cpp
 *
 * @brief  コウモリの待機状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/12/03
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Bat/State/BatIdling.h"
#include "Game/Object/Enemy/Bat/Bat.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] bat コウモリのポインタ
 */
BatIdling::BatIdling(Bat* bat)
	:m_bat(bat)
{
}
/**
 * @brief デストラクタ
 */
BatIdling::~BatIdling()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatIdling::Initialize()
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
void BatIdling::PreUpdate()
{
	m_bat->SetVelocity(DirectX::SimpleMath::Vector3::Zero);
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	//Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::MOVING);

	//一定時間経過したら移動状態へ遷移
	if (m_bat->GetFrameCount() > 5.0f) 
	{
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::MOVING);
	}

	//プレイヤーを取得
	GameObject* pPlayer =  Messenger::GetInstance()->GetObject(0);
	//プレイヤーか確認
	if (pPlayer && pPlayer->GetObjectType() == Tag::Player)
	{
		//現在位置とプレイヤーの位置の距離
		DirectX::SimpleMath::Vector3 playerPos = pPlayer->GetCurrentPosition();
		float distance = DirectX::SimpleMath::Vector3::Distance(playerPos , m_bat->GetCurrentPosition());
		//範囲内なら遷移
		if (distance < 15.0f)
		{
			Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::CHASING);
		}
	}


	//DirectX::SimpleMath::Vector3 v = m_bat->GetVelocity();
	//
	//v.y += -0.8f * elapsedTime;

	//m_bat->SetVelocity(v);

	//m_bat->SetPosition(m_bat->GetPosition() + m_bat->GetVelocity());

}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatIdling::PostUpdate()
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
void BatIdling::Render()
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
void BatIdling::Finalize()
{
}
