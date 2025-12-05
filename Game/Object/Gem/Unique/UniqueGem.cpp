/**
 * @file   UniqueGem.cpp
 *
 * @brief  宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/10/24
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "UniqueGem.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] type  宝石の種類
 * @param[in] value 宝石の効果値
 * @param[in] discription 宝石の効果説明
 */
UniqueGem::UniqueGem(UniqueType uniqeuType, GemAbility ability, GemImagePath image)
	:Gem{ ability,image }
{
}




/**
 * @brief デストラクタ
 */
UniqueGem::~UniqueGem()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UniqueGem::Initialize()
{

}

void UniqueGem::ApplyEffect()
{
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UniqueGem::Finalize()
{

}


