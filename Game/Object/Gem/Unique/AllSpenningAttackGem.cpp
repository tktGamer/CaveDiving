/**
 * @file   AllSpenningAttackGem.cpp
 *
 * @brief  宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/10/27
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "AllSpenningAttackGem.h"
#include"Game/Message/Messenger.h"
#include"Game/Fuctory/GemFactory.h"
//ファクトリクラスへの登録
REGISTER_GEM_CLASS("AllSpenningAttackGem", AllSpenningAttackGem);

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] type  宝石の種類
 * @param[in] powerUp 宝石の強化項目
 * @param[in] value 宝石の効果値
 */
AllSpenningAttackGem::AllSpenningAttackGem(int id, std::string type, Type powerUp, int value)
	:Gem{ id,type,powerUp,value }
{
}

AllSpenningAttackGem::AllSpenningAttackGem(GemAbility ability, GemImagePath image)
	:Gem{ ability,image }
{
}




/**
 * @brief デストラクタ
 */
AllSpenningAttackGem ::~AllSpenningAttackGem()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void AllSpenningAttackGem::Initialize()
{

}

void AllSpenningAttackGem::UniqueEffect()
{
}




/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void AllSpenningAttackGem::Finalize()
{

}


