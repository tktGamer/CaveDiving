/**
 * @file   GemFactory.cpp
 *
 * @brief  宝石生成に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/11/25
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GemFactory.h"
std::unordered_map<std::string, GemFactory::CreatorFunc> GemFactory::creators;

// メンバ関数の定義 ===========================================================
/**
 * @brief 「宝石」の生成
 *
 * @param[in] className     生成する宝石のクラス名
 * @param[in] gemAbility  　データ
 * @param[in] gemImagePath  選択UIのテクスチャパス
 *
 * @return 宝石選択UIクラス
 */
std::unique_ptr<Gem> GemFactory::CreateGem(const std::string& className, const Gem::GemAbility& gemAbility, const Gem::GemImagePath& gemImagePath)
{
    auto it = creators.find(className);
    if (it != creators.end())
        return it->second(gemAbility, gemImagePath);
    return nullptr;
}
