/**
 * @file   Wall.h
 *
 * @brief  壁に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/22
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include "Game/Object/GameObject.h"
#include "Game/Common/Collision/Sphere.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 壁
  */
class Wall :public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:
	static constexpr float SPHERE_SIZE = 60.0f;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
//　取得・設定
	// コンストラクタ
public:
	Wall(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);
	// デストラクタ
	~Wall();
// 操作
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
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	// メッセージID
	Message::MessageID m_messageID;
	// 当たり判定用の形状
	Sphere m_sphere;
	Ito::DisplayCollision m_display;
};

