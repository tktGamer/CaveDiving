/**
 * @file   GolemDamaged.cpp
 *
 * @brief  ゴーレムの待機状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Golem/State/GolemDamaged.h"
#include "Game/Object/Enemy/Golem/Golem.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] golem ゴーレムのポインタ
 */
GolemDamaged::GolemDamaged(Golem* golem)
	:m_golem{golem}
{
}
/**
 * @brief デストラクタ
 */
GolemDamaged::~GolemDamaged()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemDamaged::Initialize()
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
void GolemDamaged::PreUpdate()
{
	m_golem->SetVelocity(m_golem->GetDamageDirection());
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemDamaged::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	DirectX::SimpleMath::Vector3 velocity = m_golem->GetVelocity();
	//重力
	velocity.y += World::GRAVITY * elapsedTime;

	//一定時間経過したら移動状態へ遷移
	if (m_golem->GetFrameCount() > CHANGE_IDLING_TIME)
	{
		Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::IDLING);
	}
	//ノックバック時間
	else if (m_golem->GetFrameCount() < KNOCKBACK_TIME)
	{
		m_golem->SetVelocity(velocity);
		//位置更新
		m_golem->SetPosition(m_golem->GetPosition() + m_golem->GetVelocity() * KNOCKBACK_POWER * elapsedTime);
	}

	m_golem->SetVelocity(velocity);

	m_golem->SetPosition(m_golem->GetPosition() + m_golem->GetVelocity());

}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemDamaged::PostUpdate()
{
	//経過時間リセット
	m_golem->ResetFrameCount();

	m_golem->SetInvincible(false);
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemDamaged::Render()
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
void GolemDamaged::Finalize()
{
}