/**
 * @file   GemFactory.h
 *
 * @brief  宝石の生成に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef UI_FACTORY_DEFINED
#define UI_FACTORY_DEFINED
// ヘッダファイルの読み込み ===================================================
#include <functional>
#include <memory>
#include <unordered_map>
#include"../Object/Gem/Gem.h"
// ファクトリクラスを定義する
class GemFactory 
{
private:
    using CreatorFunc = std::function<std::unique_ptr<Gem>(const Gem::GemAbility&, const Gem::GemImagePath&)>;

    static std::unordered_map<std::string, CreatorFunc> creators;
public:
    static GemFactory& Instance() {
        static GemFactory instance;
        return instance;
    }

    void Register(const std::string& name, CreatorFunc func) 
    {
        creators[name] = func; 
    }
    //宝石クラス生成
    std::unique_ptr<Gem> CreateGem(const std::string& className,const Gem::GemAbility& gemAbility,const Gem::GemImagePath& gemImagePath);
};

#endif		// UI_FACTORY_DEFINED

// 
#define REGISTER_GEM_CLASS(NAME, CLASS_TYPE) \
namespace { \
    const bool registered_##CLASS_TYPE = [] \
    { \
        GemFactory::Instance().Register(NAME, \
            [](const Gem::GemAbility& a, const Gem::GemImagePath& i) \
            { \
                return std::make_unique<CLASS_TYPE>(a, i); \
            }); \
        return true; \
    }(); \
}
