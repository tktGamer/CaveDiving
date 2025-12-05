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
#include"../Item/StatusUpItem.h"
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
	
	//アイテムデータ項目
	struct ItemData
	{
		// ID
		int id = 0;
		// 種類
		std::string type;
		//強化項目
		std::string item;
		// 効果
		int			effect = 0;
		//効果適用間隔
		int interval;


		//宝石の画像パス
		std::string  gem;
		//名前の画像パス
		std::string  name;
		//説明の画像パス
		std::string  explanation;

	};


// データメンバの宣言 -----------------------------------------------
private:
	// グラフィックスクラスのポインタ
	Graphics* m_graphics;	

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
};

