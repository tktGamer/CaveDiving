/**
 * @file   Ground.h
 *
 * @brief  地面に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/08
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Collision/Box.h"
#include"Game/Object/GameObject.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 地面
  */
class Ground :public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:
	//地面の初期位置
	static constexpr DirectX::SimpleMath::Vector3 INITIAL_GROUND_POS = { 0.0f, -1.5f, 0.0f };
	//地面の初期サイズ
	static constexpr DirectX::SimpleMath::Vector3 INITIAL_GROUND_SCALE = { 70.0f, 1.0f, 70.0f };


// データメンバの宣言 -----------------------------------------------
private:
	// メッセージID
	Message::MessageID m_messageID;

	// 当たり判定用の形状
	Box m_box;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Ground(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~Ground();


// 操作
public:
	//初期化
	void Initialize();
	//更新
	void Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;

	//描画
	void Draw() override;
	//終了
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

