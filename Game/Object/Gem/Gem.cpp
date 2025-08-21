/**
 * @file   Gem.cpp
 *
 * @brief  宝石に関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Gem.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 */
Gem::Gem()
{
}
/**
 * @brief コンストラクタ
 *
 * @param[in] type  宝石の種類
 * @param[in] value 宝石の効果値
 * @param[in] discription 宝石の効果説明
 */
Gem::Gem(Type type, int value, std::string discription)
	:m_ability{ type, value, discription }
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



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Gem::Update()
{

}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Gem::Draw()
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

Gem::GemImagePath Gem::GetImagePath() const
{
	return m_gemImage;
}
