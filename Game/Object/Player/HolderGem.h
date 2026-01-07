/**
 * @file   HolderGem.h
 *
 * @brief  所持宝石の管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/01/04
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Object/Gem/Gem.h"
#include<vector>
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 所持宝石の管理
  */
class HolderGem
{
// クラス定数の宣言 -------------------------------------------------
public:
    static constexpr int MAX_GEM = 3;

// データメンバの宣言 -----------------------------------------------
private:
   std::vector<std::unique_ptr<Gem>> m_holdGems = std::vector<std::unique_ptr<Gem>>(MAX_GEM);
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	HolderGem(const std::vector<int>& gemID);

	// デストラクタ
	~HolderGem();


// 操作
public:
    void Clear();

    bool HasBlankSlot() const;
    void SetGem(const Gem* gem, int index = -1);
    const std::vector<std::unique_ptr<Gem>>& GetGems() const;


	//指定の宝石をもっているか
	template<typename T>
	const std::vector<T*>  IsHasGem()const ;

//　取得・設定
public:

//　内部操作
private:

};


template<typename T>
inline const std::vector<T*> HolderGem::IsHasGem() const
{
	std::vector<T*> result;

	for (int i = 0; i < m_holdGems.size(); ++i)
	{
		if (auto& gem = m_holdGems[i])
		{
			if (auto targetGem = dynamic_cast<T*>(gem.get()))
			{
				//T型のGemを追加
				result.push_back(targetGem);
			}
		}
	}
	return result;
}
