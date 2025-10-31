/**
 * @file   UniquGem.cpp
 *
 * @brief  宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/10/24
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "UniquGem.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] type  宝石の種類
 * @param[in] value 宝石の効果値
 * @param[in] discription 宝石の効果説明
 */
UniquGem::UniquGem(UniqueType uniqeuType, GemAbility ability, GemImagePath image)
	:Gem{ ability,image }
{
}




/**
 * @brief デストラクタ
 */
UniquGem::~UniquGem()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UniquGem::Initialize()
{

}

void UniquGem::ApplyEffect()
{
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UniquGem::Finalize()
{

}


