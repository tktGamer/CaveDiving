/**
 * @file   CandleStick.h
 *
 * @brief  CandleStickに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Object/GameObject.h"
#include"Game/Common/Collision/Box.h"
#include"Game/Object/Light.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 燭台
  */
class CandleStick : public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	color;
	};


// データメンバの宣言 -----------------------------------------------
private:
	// メッセージID
	Message::MessageID m_messageID;

	Graphics* m_graphics;	// グラフィックスクラスのポインタ
	bool m_isOn; //ライトのオンオフ状態
	
	//AABB当たり判定
	Box m_box;

	std::unique_ptr<Light> m_light;
	DirectX::SimpleMath::Vector4 m_color;

	Ito::DisplayCollision m_display;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	CandleStick(Shader::PointLight lightData,GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~CandleStick();


// 操作
public:
	void Initialize(bool isOnlight);

	void Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

	void Finalize();

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);

	//衝突応答分岐
	void CollisionResponce(GameObject* other) override;

	//
	void OnLight();
//　取得・設定
public:
	bool IsOnLight();

//　内部操作
private:

};

