/**
 * @file   StatusUpGem.cpp
 *
 * @brief  宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/10/27
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "StatusUpGem.h"
#include"Game/Fuctory/GemFactory.h"
REGISTER_GEM_CLASS("StatusUpGem", StatusUpGem);
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] type  宝石の種類
 * @param[in] powerUp 宝石の強化項目
 * @param[in] value 宝石の効果値
 */

StatusUpGem::StatusUpGem(Gem::GemAbility ability, Gem::GemImagePath image)
	:Gem{ability,image}
{
}




/**
 * @brief デストラクタ
 */
StatusUpGem::~StatusUpGem()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void StatusUpGem::Initialize()
{

}




/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void StatusUpGem::Finalize()
{

}

