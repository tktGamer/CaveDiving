/**
 * @file   FullHPAttackUp.cpp
 *
 * @brief  HP満タンで攻撃力が上がる宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/11/19
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "FullHPAttackUp.h"
#include"Game/Message/Messenger.h"
#include"Game/Fuctory/GemFactory.h"
//ファクトリクラスへの登録
REGISTER_GEM_CLASS("FullHPAttackUp", FullHPAttackUp);

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] type  宝石の種類
 * @param[in] powerUp 宝石の強化項目
 * @param[in] value 宝石の効果値
 */
FullHPAttackUp::FullHPAttackUp(int id, std::string type, Type powerUp, int value)
	:Gem{ id,type,powerUp,value }
{
}

FullHPAttackUp::FullHPAttackUp(GemAbility ability, GemImagePath image)
	:Gem{ ability,image }
{
}




/**
 * @brief デストラクタ
 */
FullHPAttackUp ::~FullHPAttackUp()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void FullHPAttackUp::Initialize()
{

}

int FullHPAttackUp::GetAttackPower(const int& currentHP, const int& maxHP)
{
	if (currentHP == maxHP) 
	{
		return GetAbility().value;
	}
	return 0;
}





/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void FullHPAttackUp::Finalize()
{

}


