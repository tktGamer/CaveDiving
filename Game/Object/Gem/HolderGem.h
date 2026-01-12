/**
 * @file   HolderGem.h
 *
 * @brief  所持宝石の管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/01/08
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
	//所持できる上限
    static constexpr int MAX_GEM = 3;
	
// データメンバの宣言 -----------------------------------------------
private:
	//所持宝石リスト
   std::vector<std::unique_ptr<Gem>> m_holdGems = std::vector<std::unique_ptr<Gem>>(MAX_GEM);
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	HolderGem(const std::vector<int>& gemID = std::vector<int>(MAX_GEM,Gem::BLANK_ID));

	// デストラクタ
	~HolderGem();


// 操作
public:
	//リストクリア
    void Clear();
	//リストに空きがあるか
    bool HasBlankSlot() const;
	//リストに宝石をセット
    void SetGem(const Gem* gem,const int& index = Gem::BLANK_ID);
	//リストの宝石を取得
    const std::vector<std::unique_ptr<Gem>>& GetGems() const;


	//指定の宝石を取得
	template<typename T>
	const std::vector<T*>  FindHasGem() const;

//　取得・設定
public:

//　内部操作
private:

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
