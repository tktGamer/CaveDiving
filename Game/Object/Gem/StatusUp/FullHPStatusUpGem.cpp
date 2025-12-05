/**
 * @file   FullHPStatusUpGem.cpp
 *
 * @brief  HP満タンでステータスが上がる宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/12/03
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "FullHPStatusUpGem.h"
#include"Game/Message/Messenger.h"
#include"Game/Fuctory/GemFactory.h"
//ファクトリクラスへの登録
REGISTER_GEM_CLASS("FullHPStatusUpGem", FullHPStatusUpGem);

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] ability  宝石の詳細
 * @param[in] image 　 選択時の画像
 */
FullHPStatusUpGem::FullHPStatusUpGem(GemAbility ability, GemImagePath image)
	:StatusUpGem{ ability,image }
{
}




/**
 * @brief デストラクタ
 */
FullHPStatusUpGem ::~FullHPStatusUpGem()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void FullHPStatusUpGem::Initialize()
{

}


/**
 * @brief 効果を適用するか判断
 *
 * @param[in] currentHP
 * @param[in] maxHP
 *
 * @return なし
 */
const bool& FullHPStatusUpGem::IsApplicable(const int& currentHP, const int& maxHP) const
{
	if (currentHP >= maxHP) 
	{
		return true;
	}
	return false;
}






/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void FullHPStatusUpGem::Finalize()
{

}


