/**
 * @file   AllSpenningAttackGem.cpp
 *
 * @brief  攻撃を回転攻撃にする宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/01/04
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "AllSpenningAttackGem.h"
#include"Game/Message/Messenger.h"
#include"Game/Factory/GemFactory.h"
//ファクトリクラスへの登録
REGISTER_GEM_CLASS("AllSpenningAttackGem", AllSpenningAttackGem);

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] ability  宝石の詳細
 * @param[in] image 　 選択時の画像
 */
AllSpenningAttackGem::AllSpenningAttackGem(const GemAbility& ability, const GemImagePath& image)
	:Gem{ ability,image }
{
}




/**
 * @brief デストラクタ
 */
AllSpenningAttackGem ::~AllSpenningAttackGem()
{

}



std::unique_ptr<Gem> AllSpenningAttackGem::Clone() const
{
	return std::make_unique<AllSpenningAttackGem>(*this);
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


