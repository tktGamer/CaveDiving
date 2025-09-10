/**
 * @file   BatAttack.cpp
 *
 * @brief  コウモリの攻撃状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/09/03
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Bat/State/BatAttack.h"
#include "Game/Object/Enemy/Bat/Bat.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] bat コウモリのポインタ
 */
BatAttack::BatAttack(Bat* bat, Wing* pRightWing, Wing* pLeftWing)
	:m_bat(bat)
	,m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();

	m_attackMotion = std::make_unique<BatAttackMotion>(bat,pRightWing,pLeftWing);
}
/**
 * @brief デストラクタ
 */
BatAttack::~BatAttack()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttack::Initialize()
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
void BatAttack::PreUpdate()
{
	m_attackMotion->Initialize();

	m_bat->SetVelocity(DirectX::SimpleMath::Vector3::Transform(Character::MOVE::FRONT*15.0f * Messenger::GetInstance()->GetElapsedTime(), m_bat->GetCurrentQuaternion()));

}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	DirectX::SimpleMath::Vector3 v = m_bat->GetVelocity();


	v.y += -0.05f * elapsedTime;


	m_bat->SetVelocity(v);

	m_bat->SetPosition(m_bat->GetPosition() + m_bat->GetVelocity());

}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttack::PostUpdate()
{
	m_attackMotion->Reset();
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttack::Render()
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
void BatAttack::Finalize()
{
}

