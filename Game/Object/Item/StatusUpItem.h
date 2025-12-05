/**
 * @file   StatusUpItem.h
 *
 * @brief  アイテムの基底に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025//11//19
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "../Item/Item.h"
#include "Game/Common/Collision/Box.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief アイテム
  */
class StatusUpItem : public Item
{
// クラス定数の宣言 -------------------------------------------------
public:
	enum UniqueEffect
	{
		Outline,
	};

	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix	 matWorld;
		DirectX::SimpleMath::Matrix	 matView;
		DirectX::SimpleMath::Matrix	 matProj;
		DirectX::SimpleMath::Vector4 color;
	};

// データメンバの宣言 -----------------------------------------------
private:

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	StatusUpItem(EffectType upStatus, int increase,
		GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	virtual ~StatusUpItem();


// 操作
public:
	//更新
	void Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;

	//描画
	void Draw() override;

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);

	//衝突応答分岐
	void CollisionResponce(GameObject* other);

//　取得・設定
public:
//　内部操作
private:
};

