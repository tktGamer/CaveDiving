/**
 * @file   HolderGem.cpp
 *
 * @brief  所持宝石の管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/29
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "HolderGem.h"
#include"Game/Object/Gem/GemManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] gemID　セットする宝石のID
 */
HolderGem::HolderGem(const std::vector<int>& gemID)
{
    //念のためクリア
    Clear();
    for (int i = 0; i < gemID.size(); i++)
    {
        //宝石を取得
        const Gem* gem = GemManager::GetInstance()->GetIDNumberedGem(gemID[i]);
        if (gem) 
        {
            //宝石をコピーしてリストに格納
            m_holdGems[i] =(std::move(gem->Clone()));
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
 * @brief 更新
 *
 * @param[in] owner  所有者のアドレス
 *
 * @return なし
 */
void HolderGem::Update(Character& owner) const
{
    for (const std::unique_ptr<Gem>& gem : m_holdGems)
    {
        //スロットが空なら
        if (!gem)
        {
            continue;
        }
        //各宝石のフレーム更新処理を実行
        gem->OnUpdate(owner);
    }
}

/**
 * @brief 宝石によるステータス補正値の合計を取得
 *
 * @param[in] type  強化するステータスの項目（攻撃力・防御力など）
 *
 * @return 補正値
 */
int HolderGem::ApplyStatus(const Gem::Type& type, const Character& owner) const
{
    //補正値の合計
    int total = 0;
    //
    for (const std::unique_ptr<Gem>& gem : m_holdGems)
    {
        //スロットが空なら
        if (!gem) 
        {
            continue;
        }
        // 各宝石のステータス補正を加算
        total += gem->ModifyStatus(type, owner);
    }
    return total;
}

/**
 * @brief 宝石による被弾時の処理
 *
 * @param[in] owner   所有者
 * @param[in] damage  受けたダメージ
 *
 * @return 最終的なダメージ量
 */
int HolderGem::OnTakeDamage(Character& owner, int damage)
{
    for (std::unique_ptr<Gem>& gem : m_holdGems)
    {
        //スロットが空なら
        if (!gem)
        {
            continue;
        }
        // 各宝石の被弾時の処理
        damage += gem->OnTakeDamage(owner,damage);
    }

    return damage;
}

/**
 * @brief リストの初期化
 *
 * @param[in] なし
 *
 * @return なし
 */
void HolderGem::Clear()
{
    //中身をクリア
    m_holdGems.clear();
    //格納できる分の要素を作っておく　
    for (int i = 0; i < MAX_GEM; i++) 
    {
        m_holdGems.emplace_back(nullptr);
    }
}

/**
 * @brief リストに空きがあるか
 *
 * @param[in] なし
 *
 * @return true   あり
 * @return false  なし
 */
bool HolderGem::HasBlankSlot() const
{
    //nullptrがあるか調べる
    for (auto& g : m_holdGems) 
    {
        if (!g) return true;
    }
    return false;
}

/**
 * @brief リストに宝石をセット
 *
 * @param[in] gem  宝石のポインタ
 * @param[in] index 格納する要素番号  指定がなかったら空いているスロットにセット
 *
 * @return なし
 */
void HolderGem::SetGem(const Gem* gem, const int& index)
{
    //指定された番号が要素数の内にあるか
    if (index >= 0 && index < MAX_GEM)
    {
        //宝石をコピーして格納して終了
        m_holdGems[index] =std::move(gem->Clone());
        return;
    }

    //空きがあるか調べる
    if(!HasBlankSlot())
    {
        //なかったので終了
        return;
    }
    //あるので空きスロットに格納
    for (int i = 0; i < MAX_GEM; i++)
    {
        if (!m_holdGems[i])
        {
            //宝石をコピーして格納して終了
            m_holdGems[i] = std::move(gem->Clone());
            return;
        }
    }
}

/**
 * @brief リストの宝石を取得
 *
 * @param[in] なし
 *
 * @return 宝石のリスト
 */
const std::vector<std::unique_ptr<Gem>>& HolderGem::GetGems() const
{
    return m_holdGems;
}