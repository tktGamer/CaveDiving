/**
 * @file   Gem.cpp
 *
 * @brief  宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/10/27
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Gem.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] type  宝石の種類
 * @param[in] powerUp 宝石の強化項目
 * @param[in] value 宝石の効果値
 */
Gem::Gem(int id ,std::string type,Type powerUp, int value)
	:m_ability{id,type , powerUp, value}
{
}

Gem::Gem(GemAbility ability, GemImagePath image)
	:m_ability{ ability }
	, m_gemImage{ image }
{
}




/**
 * @brief デストラクタ
 */
Gem::~Gem()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Gem::Initialize()
{

}

void Gem::ApplyEffect()
{
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Gem::Finalize()
{

}


/**
 * @brief 宝石の性能を取得
 *
 * @param[in] なし
 *
 * @return 宝石の性能
 */
Gem::GemAbility Gem::GetAbility() const
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
Gem::GemImagePath Gem::GetImagePath() const
{
	return m_gemImage;
}
