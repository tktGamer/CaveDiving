/**
 * @file   Motion.cpp
 *
 * @brief  モーションの基底に関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2025/09/04
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Motion.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Motion::Motion()
	:m_motionLerp{0.0f}
{

}



/**
 * @brief デストラクタ
 */
Motion::~Motion()
{

}







/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Motion::Reset()
{
	m_motionLerp = 0.0f;
}


/**
 * @brief モーション補間値の取得
 *
 * @param[in] なし
 *
 * @return モーションの補間値
 */
float Motion::GetMotionLerp() const
{
	return m_motionLerp;
}

/**
 * @brief モーション補間値の設定
 *
 * @param[in] モーション補間値
 *
 * @return なし
 */
void Motion::SetMotionLerp(const float& motionLerp)
{
	m_motionLerp = motionLerp;
}


