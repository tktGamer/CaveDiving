/**
 * @file   HolderGem.h
 *
 * @brief  所持宝石の管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/19
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Object/Gem/Gem.h"
#include<vector>
// クラスの宣言 ===============================================================
class Character;
// クラスの定義 ===============================================================
/**
  * @brief 所持宝石の管理
  */
class HolderGem
{
// クラス定数の宣言 -------------------------------------------------
public:
	//所持できる上限
    static constexpr int MAX_GEM = 3;
	
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//リストに宝石をセット
    void SetGem(const Gem* gem,const int& index = Gem::BLANK_ID);
	//リストの宝石を取得
    const std::vector<std::unique_ptr<Gem>>& GetGems() const;
	//指定の宝石を取得
	template<typename T>
	const std::vector<T*>  FindHasGem() const;
// コンストラクタ/デストラクタ
	// コンストラクタ
	HolderGem(const std::vector<int>& gemID = std::vector<int>(MAX_GEM,Gem::BLANK_ID));
	// デストラクタ
	~HolderGem();
// 操作
	//更新
	void Update(Character& owner) const;
	//ステータス補正取得
	int ApplyStatus(const Gem::Type& type, const Character& owner) const;
	//被弾時の処理
	int OnTakeDamage(Character& owner,int damage);
	//リストクリア
    void Clear();
	//リストに空きがあるか
    bool HasBlankSlot() const;
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	//所持宝石リスト
   std::vector<std::unique_ptr<Gem>> m_holdGems = std::vector<std::unique_ptr<Gem>>(MAX_GEM);
};

/**
 * @brief 指定した宝石を取得
 * 
 * @tparam T 取得する宝石のクラス
 * @param[in] なし
 *
 * @return 指定した宝石のクラスリスト
 */
template<typename T>
inline const std::vector<T*> HolderGem::FindHasGem() const
{
	//指定の宝石を格納するリスト
	std::vector<T*> result;
	//リストに宝石があるか調べる
	for (int i = 0; i < m_holdGems.size(); ++i)
	{
		if (auto& gem = m_holdGems[i])
		{
			//宝石の型を調べる
			if (auto targetGem = dynamic_cast<T*>(gem.get()))
			{
				//T型のGemを追加
				result.push_back(targetGem);
			}
		}
	}
	return result;
}
