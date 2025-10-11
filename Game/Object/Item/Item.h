/**
 * @file   Item.h
 *
 * @brief  アイテムの基底に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "../GameObject.h"
#include "Game/Common/Collision/Box.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief キャラクター
  */
class Item : public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:
	enum UpStatus 
	{
		Attack,
		Diffece,
		Speed
	};

	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4 color;
	};

// データメンバの宣言 -----------------------------------------------
private:
	Ito::DisplayCollision m_display;
	//球状当たり判定
	Box m_box;

	//上昇するステータス
	UpStatus m_upStatus;
	//上昇量
	int m_increase;
	//効果時間
	float m_time;

	//ゲットされたか
	bool m_isGet;

	DirectX::SimpleMath::Vector4 m_color;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Item(UpStatus upStatus,int increase,
		GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	virtual ~Item();


// 操作
public:

	void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);

	//衝突応答分岐
	void CollisionResponce(GameObject* other);

//　取得・設定
public:
	//上昇するステータス
	UpStatus GetUpStatus() const;
	//上昇量
	int GetIncrease() const;
	//効果時間
	float GetTime() const;

	bool IsGet() const;

	const DirectX::SimpleMath::Vector4& GetColor();
//　内部操作
private:
	void DecideColor();
};

