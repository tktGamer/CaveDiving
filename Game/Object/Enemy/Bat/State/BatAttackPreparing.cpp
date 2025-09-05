/**
 * @file   BatAttackPreparing.cpp
 *
 * @brief  コウモリの攻撃準備状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/09/03
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Bat/State/BatAttackPreparing.h"
#include "Game/Object/Enemy/Bat/Bat.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] bat コウモリのポインタ
 */
BatAttackPreparing::BatAttackPreparing(Bat* bat, Wing* pRightWing, Wing* pLeftWing)
	:m_bat(bat)
	, m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();

	m_attackPreparingMotion = std::make_unique<BatAttackPreparingMotion>(pRightWing,pLeftWing);

}
/**
 * @brief デストラクタ
 */
BatAttackPreparing::~BatAttackPreparing()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttackPreparing::Initialize()
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
void BatAttackPreparing::PreUpdate()
{
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttackPreparing::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	//m_bat->SetVelocity(m_bat->GetVelocity() * 0.8f);

	//Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::IDLING);
	//m_bat->SetPosition(m_bat->GetPosition() + m_bat->GetVelocity());

}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttackPreparing::PostUpdate()
{
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttackPreparing::Render()
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
void BatAttackPreparing::Finalize()
{
}

