/**
 * @file   OutlineItem.h
 *
 * @brief  アウトラインアイテムに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/19
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "../Item.h"
#include "Game/Common/Collision/Box.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief アイテム
  */
class OutlineItem : public Item
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	OutlineItem(const Item::ItemInfo& info,
		const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);
	// デストラクタ
	~OutlineItem();
// 操作

//　内部操作
private:
protected:
	//アイテムがゲットされたときの追加処理
	void OnItemGetExtra(const GameObject* other) override;
// データメンバの宣言 -----------------------------------------------
private:
};

