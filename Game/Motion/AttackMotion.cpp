/**
 * @file   AttackMotion.cpp
 *
 * @brief  攻撃モーションの基底に関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "AttackMotion.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] attackPowerModifier モーションによる攻撃力補正
 */
AttackMotion::AttackMotion(const float& attackPowerModifier)
	:
	m_attackPowerModifier{attackPowerModifier}
{
}

/**
 * @brief デストラクタ
 */
AttackMotion::~AttackMotion()
{
}

/**
 * @brief 攻撃力補正値の取得
 *
 * @param[in] なし
 *
 * @return 攻撃力補正値
 */
float AttackMotion::GetAttackPowerModifier() const
{
	return m_attackPowerModifier;
}

/**
 * @brief 攻撃力補正値の設定
 *
 * @param[in] modifier 攻撃力補正値
 *
 * @return なし
 */
void AttackMotion::SetAttackPowerModifier(const float& modifier)
{
	m_attackPowerModifier = modifier;
}