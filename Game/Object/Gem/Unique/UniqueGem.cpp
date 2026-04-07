/**
 * @file   UniqueGem.cpp
 *
 * @brief  特殊効果宝石の基底に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/04
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "UniqueGem.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] ability  宝石の詳細
 * @param[in] image 　 選択時の画像
 */
UniqueGem::UniqueGem(const UniqueType& uniqeuType, const GemAbility& ability, const GemImagePath& image)
	:Gem{ ability,image }
	, m_type{ uniqeuType }
{
}




/**
 * @brief デストラクタ
 */
UniqueGem::~UniqueGem()
{

}



/**
 * @brief 多態コピー
 *
 * @param[in] なし
 *
 * @return コピー
 */

std::unique_ptr<Gem> UniqueGem::Clone() const
{
	return std::make_unique<UniqueGem>(*this);
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


