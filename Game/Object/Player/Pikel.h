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
#include "Game/Object/GameObject.h"
#include"Game/Common/Collision/DisplayCollision.h"
#include"Game/Common/Collision/Sphere.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief Pikel
  */
class Pikel : public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:
	Graphics* m_graphics;	// グラフィックスクラスのポインタ

	DirectX::SimpleMath::Matrix m_world;

	Ito::DisplayCollision m_display;
	//当たり判定
	Sphere m_sphere;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Pikel(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// デストラクタ
	~Pikel();


// 操作
public:
	void Initialize();

	void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

	void Finalize();

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);
	//　取得・設定
public:
	int GetObjectNumber() override;

//　内部操作
private:

};

