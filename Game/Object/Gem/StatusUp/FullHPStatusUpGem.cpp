/**
 * @file   FullHPStatusUpGem.cpp
 *
 * @brief  HP満タンでステータスが上がる宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/19
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "FullHPStatusUpGem.h"
#include"Game/Message/Messenger.h"
#include"Game/Factory/GemFactory.h"
#include"Game/Object/Character.h"
//ファクトリクラスへの登録
REGISTER_GEM_CLASS("FullHPStatusUpGem", FullHPStatusUpGem);

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] ability  宝石の詳細
 * @param[in] image 　 選択時の画像
 */
FullHPStatusUpGem::FullHPStatusUpGem(const GemAbility& ability,const GemImagePath& image)
	:
	StatusUpGem{ ability,image }
{
}

/**
 * @brief デストラクタ
 */
FullHPStatusUpGem ::~FullHPStatusUpGem()
{
}



/**
 * @brief 多態コピー
 *
 * @param[in] なし
 *
 * @return コピー
 */
std::unique_ptr<Gem> FullHPStatusUpGem::Clone() const
{
	return std::make_unique<FullHPStatusUpGem>(*this);
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
 * @brief ステータス補正
 *
 * @param[in] type  補正するステータス
 * @param[in] owner 所有者
 *
 * @return 補正値
 */
int FullHPStatusUpGem::ModifyStatus(const Gem::Type& type, const Character& owner) const
{
	const GemAbility ability = GetAbility();
	//補正するステータスが一致してなかったら
	if (ability.powerUp != type) 
	{
		return STATUS_MODIFIER_NONE;
	}
	//HPがMAXなら
	if (IsApplicable(owner.GetCurrentHP(), owner.GetMaxHP())) 
	{
		return ability.value;
	}
	return STATUS_MODIFIER_NONE;
}

/**
 * @brief 効果を適用するか判断
 *
 * @param[in] currentHP　現在HP
 * @param[in] maxHP      最大HP
 *
 * @return true   適用する
 * @return false  適用しない
 */
const bool FullHPStatusUpGem::IsApplicable(const int& currentHP, const int& maxHP) const
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