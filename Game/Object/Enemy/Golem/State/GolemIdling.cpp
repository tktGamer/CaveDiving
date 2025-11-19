/**
 * @file   GolemIdling.cpp
 *
 * @brief  ゴーレムの待機状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/11/15
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Golem/State/GolemIdling.h"
#include "Game/Object/Enemy/Golem/Golem.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] golem ゴーレムのポインタ
 */
GolemIdling::GolemIdling(Golem* golem)
	:m_golem(golem)
{
}
/**
 * @brief デストラクタ
 */
GolemIdling::~GolemIdling()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemIdling::Initialize()
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
void GolemIdling::PreUpdate()
{
	m_golem->SetVelocity(DirectX::SimpleMath::Vector3::Zero);
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	//Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::MOVING);

	//一定時間経過したら移動状態へ遷移
	if (m_golem->GetFrameCount() > 2.0f) 
	{
		Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::MOVING);
	}

	//プレイヤーを取得
	GameObject* pPlayer =  Messenger::GetInstance()->GetObject(0);
	//プレイヤーか確認
	if (pPlayer && pPlayer->GetObjectType() == Tag::Player)
	{
		//現在位置とプレイヤーの位置の距離
		DirectX::SimpleMath::Vector3 playerPos = pPlayer->GetCurrentPosition();
		float distance = DirectX::SimpleMath::Vector3::Distance(playerPos , m_golem->GetCurrentPosition());
		//範囲内なら遷移
		if (distance < 15.0f)
		{
			Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::CHASING);
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
void GolemIdling::PostUpdate()
{
	m_golem->ResetFrameCount();
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemIdling::Render()
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
void GolemIdling::Finalize()
{
}
