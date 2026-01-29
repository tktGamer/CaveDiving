/**
 * @file   StatusUpGem.cpp
 *
 * @brief  宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/01/19
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "StatusUpGem.h"
#include"Game/Factory/GemFactory.h"
//ファクトリクラスへの登録
REGISTER_GEM_CLASS("StatusUpGem", StatusUpGem);
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] ability  宝石の詳細
 * @param[in] image 　 選択時の画像
 */
StatusUpGem::StatusUpGem(const Gem::GemAbility& ability,const Gem::GemImagePath& image)
	:
	Gem{ability,image}
{
}

/**
 * @brief デストラクタ
 */
StatusUpGem::~StatusUpGem()
{
}

/**
 * @brief 多態コピー
 *
 * @param[in] なし
 *
 * @return コピー
 */
std::unique_ptr<Gem> StatusUpGem::Clone() const
{
	return std::make_unique<StatusUpGem>(*this);
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