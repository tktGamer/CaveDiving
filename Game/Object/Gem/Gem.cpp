/**
 * @file   Gem.cpp
 *
 * @brief  宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/01/04
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Gem.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] ability  宝石の詳細
 * @param[in] image 　 選択時の画像
 */
Gem::Gem(const GemAbility& ability, const GemImagePath& image)
	:m_ability{ability}
	,m_gemImage{image}
{
}





/**
 * @brief デストラクタ
 */
Gem::~Gem()
{

}



/**
 * @brief 宝石の性能を取得
 *
 * @param[in] なし
 *
 * @return 宝石の性能
 */
const Gem::GemAbility& Gem::GetAbility() const
{
	return m_ability;
}

/**
 * @brief 宝石の画像パスの取得
 *
 * @param[in] なし
 *
 * @return 宝石の画像パス
 */
const Gem::GemImagePath& Gem::GetImagePath() const
{
	return m_gemImage;
}
