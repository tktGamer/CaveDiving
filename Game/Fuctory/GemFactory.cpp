#include "pch.h"
#include "GemFactory.h"
std::unordered_map<std::string, GemFactory::CreatorFunc> GemFactory::creators;



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
