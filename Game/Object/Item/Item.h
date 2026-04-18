/**
 * @file   Item.h
 *
 * @brief  アイテムの基底に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/19
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "../GameObject3D.h"
#include "Game/Common/Collision/Box.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief アイテム
  */
class Item : public GameObject3D
{
// クラス定数の宣言 -------------------------------------------------
public:
	//アイテム効果の種類
	enum EffectType 
	{
		Attack,
		Diffece,
		Speed,
		Outline
	};
	//アイテムの情報
	struct ItemInfo 
	{
		EffectType type;
		int increase;
		float time;
	};
//非公開定数
private:
	//AABB当たり判定サイズ
	static constexpr DirectX::SimpleMath::Vector3 BOX_COLLISION_SIZE = { 1.0f,2.0f,1.0f };

	// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//アイテム情報
	const Item::ItemInfo& GetItemInfo();
	//上昇するステータス
	const EffectType& GetEffectType() const;
	//上昇量
	const int& GetIncrease() const;
	//効果時間
	const float& GetTime() const;
	//取得されたか
	bool IsAlive() const override;
	//取得状態のセット
	void SetIsGet(const bool& isGet);
	//オブジェクトが取られた位置
	void SetItemGetObjectPos(const DirectX::SimpleMath::Vector3& pos);
	//オブジェクトが取られた位置の取得
	const DirectX::SimpleMath::Vector3& GetItemGetObjectPos();
	//色の取得
	const DirectX::SimpleMath::Vector4& GetColor();
// コンストラクタ/デストラクタ
	// コンストラクタ
	Item(const ItemInfo& itemInfo,
		const GameObject3D* parent, const Transform& initialTransform);
	// デストラクタ
	virtual ~Item();
// 操作
	//更新
	virtual void Update() override;
	//描画
	virtual void Draw() override;
	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);
	//衝突応答分岐
	void CollisionResponce(GameObject3D* other) override;
	//当たり範囲更新
	void UpdateCollision(const DirectX::SimpleMath::Vector3& center);
//　内部操作
private:
	//アイテムの色を決める
	void DecideColor();
protected:
	//アイテムがゲットされたときの追加処理
	virtual void OnItemGetExtra(const GameObject* other) { other; };
// データメンバの宣言 -----------------------------------------------
private:
	Ito::DisplayCollision m_display;

	//球状当たり判定
	Box m_box;
	//アイテムの情報
	ItemInfo m_itemInfomation;

	//ゲットされたか
	bool m_isGet = false;
	//アイテムをゲットしたオブジェクトの位置
	const DirectX::SimpleMath::Vector3* m_gotObjectPos;
	//アイテムの色
	DirectX::SimpleMath::Vector4 m_color;
};