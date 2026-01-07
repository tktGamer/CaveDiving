/**
 * @file   Wall.h
 *
 * @brief  地面に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/08/27
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
  * @brief 地面
  */
class Wall :public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:
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
	Graphics* m_graphics;	// グラフィックスクラスのポインタ

	// メッセージID
	Message::MessageID m_messageID;

	// 当たり判定用の形状
	Sphere m_sphere;
	Ito::DisplayCollision m_display;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Wall(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~Wall();


// 操作
public:
	void Initialize();

	void Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

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

