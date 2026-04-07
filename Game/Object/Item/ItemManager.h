/**
 * @file   ItemManager.h
 *
 * @brief  アイテム管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/19
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Object/Item/Item.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief アイテム管理
  */
class ItemManager
{
// クラス定数の宣言 -------------------------------------------------
public:
	static  std::unordered_map<Item::EffectType, DirectX::SimpleMath::Vector3> ITEM_COLOR;

private:
	static constexpr char ATTACK[]   = "攻撃力";
	static constexpr char DIFFENCE[] = "防御力";
	static constexpr char OUTLINE[]  = "アウトライン";
	//アイテムデータのリスト
	using  ItemMap = std::unordered_map<int,Item::ItemInfo>;
	//生成関数定義
	using ItemFactory =std::function<std::unique_ptr<Item>(const Item::ItemInfo& itemInfo, const GameObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)>;
	//種類と生成関数を結びつける
	using ItemCreaterMap = std::unordered_map<Item::EffectType, ItemFactory>;
// メンバ関数の宣言 -------------------------------------------------
	
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	ItemManager();
	// デストラクタ
	~ItemManager();
// 操作
	//初期化処理
	void Initialize();
	//終了処理
	void Finalize();
	//アイテム生成
	std::vector<std::unique_ptr<Item>> GenerateItem(const std::string& spawnData);
//　内部操作
private:
	//アイテムデータ読み込み
	void LoadItemData();
// データメンバの宣言 -----------------------------------------------
private:
	//アイテムのデータ
	ItemMap m_itemInfoList;
	//アイテム生成マップ
	ItemCreaterMap m_itemCreater;
};

