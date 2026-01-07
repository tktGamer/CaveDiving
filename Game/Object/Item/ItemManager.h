/**
 * @file   ItemManager.h
 *
 * @brief  アイテム管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/08/27
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"../Item/UniquItem/OutlineItem.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 敵管理
  */
class ItemManager
{
// クラス定数の宣言 -------------------------------------------------
public:
	static  std::unordered_map<Item::EffectType, DirectX::SimpleMath::Vector3> ITEM_COLOR;
	//アイテムデータのリスト
	using  ItemMap = std::unordered_map<int, Item::ItemInfo>;
	
	static constexpr char ATTACK[] = "攻撃力";
	static constexpr char DIFFENCE[] = "防御力";
	static constexpr char OUTLINE[] = "アウトライン";


// データメンバの宣言 -----------------------------------------------
private:
	//アイテムのデータ
	ItemMap m_itemInfoList;

	//アイテムリスト
	std::list<std::unique_ptr<Item>> m_items;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	ItemManager();

	// デストラクタ
	~ItemManager();


// 操作
public:
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//終了処理
	void Finalize();

	//敵生成
	void GenerateItem();

	
//　取得・設定
public:
	//アイテムを取得
	std::list<std::unique_ptr<Item>>& GetItems() { return m_items; }
//　内部操作
private:
	//アイテムを消去
	void DeleteItem();

	void LoadItemData();
};

