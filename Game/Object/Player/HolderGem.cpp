/**
 * @file   HolderGem.cpp
 *
 * @brief  所持宝石の管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/01/04
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "HolderGem.h"
#include"Game/Object/Gem/GemManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
HolderGem::HolderGem(const std::vector<int>& gemID)
{
    Clear();
    for (int i = 0; i < gemID.size(); i++)
    {
        const Gem* gem = GemManager::GetInstance()->GetIDNumberedGem(gemID[i]);
        if (gem) 
        {
            m_holdGems[i] =(std::move( gem->Clone()));
        }
    }
}



/**
 * @brief デストラクタ
 */
HolderGem::~HolderGem()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void HolderGem::Clear()
{
    m_holdGems.clear();
    for (int i = 0; i < MAX_GEM; i++) 
    {
        m_holdGems.emplace_back(nullptr);
    }
}

bool HolderGem::HasBlankSlot() const
{
    for (auto& g : m_holdGems) 
    {
        if (!g) return true;
    }
    return false;
}

void HolderGem::SetGem(const Gem* gem, int index)
{
    if (index >= 0 && index < MAX_GEM)
    {
        m_holdGems[index] =std::move(gem->Clone());
        return;
    }

    for (int i = 0; i < MAX_GEM; i++)
    {
        if (!m_holdGems[i])
        {
            m_holdGems[i] = std::move(gem->Clone());
            return;
        }
    }
}

const std::vector<std::unique_ptr<Gem>>& HolderGem::GetGems() const
{
    return m_holdGems;
}
