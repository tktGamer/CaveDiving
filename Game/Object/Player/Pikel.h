/**
 * @file   Pikel.h
 *
 * @brief  つるはし（プレイヤーの武器）に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Weapon.h"
#include"Game/Common/Collision/DisplayCollision.h"
#include"Game/Common/Collision/Sphere.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief つるはし（プレイヤーの武器）
  */
class Pikel : public Weapon
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:
	// グラフィックスクラスのポインタ
	Graphics* m_graphics;	

	// メッセージID
	Message::MessageID m_messageID;



	Ito::DisplayCollision m_display;
	//当たり判定
	Sphere m_sphere;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Pikel(Character* owner,const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~Pikel();


// 操作
public:
	//
	void Initialize();
	//
	void Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;

	//
	void Draw() override;
	//
	void Finalize();

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);

	//衝突応答分岐
	void CollisionResponce(GameObject* other) override;

	//　取得・設定
public:

//　内部操作
private:

};

