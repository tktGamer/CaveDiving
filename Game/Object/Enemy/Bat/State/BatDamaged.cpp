/**
 * @file   BatDamaged.cpp
 *
 * @brief  コウモリの待機状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Bat/State/BatDamaged.h"
#include "Game/Object/Enemy/Bat/Bat.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] bat コウモリのポインタ
 */
BatDamaged::BatDamaged(Bat* bat)
	:m_bat(bat)
	,m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
}
/**
 * @brief デストラクタ
 */
BatDamaged::~BatDamaged()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatDamaged::Initialize()
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
void BatDamaged::PreUpdate()
{
	m_bat->SetVelocity(m_bat->GetDamageDirection());
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatDamaged::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	DirectX::SimpleMath::Vector3 velocity= m_bat->GetVelocity();
	//重力
	velocity.y += -0.8f * elapsedTime;

	//一定時間経過したら移動状態へ遷移
	if (m_bat->GetFrameCount() > 1.5f) 
	{
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::IDLING);
	}
	//ノックバック時間
	else if (m_bat->GetFrameCount() < 0.5f)
	{
		m_bat->SetVelocity(velocity);
		//位置更新
		m_bat->SetPosition(m_bat->GetPosition() + m_bat->GetVelocity() * 15.0f * elapsedTime);
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
void BatDamaged::PostUpdate()
{
	m_bat->ResetFrameCount();

	m_bat->SetInvincible(false);
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatDamaged::Render()
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
void BatDamaged::Finalize()
{
}
