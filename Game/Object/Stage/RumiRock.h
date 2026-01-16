/**
 * @file   RumiRock.h
 *
 * @brief  光る石に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/0108
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Object/GameObject.h"
#include"Game/Common/Collision/Box.h"
#include"Game/Object/Light.h"
#include"Game/Common/Sound.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 光る石
  */
class RumiRock : public GameObject
{
// クラス定数の宣言 -------------------------------------------------
private:
	//AABB当たり判定サイズ
	static constexpr DirectX::SimpleMath::Vector3 BOX_COLLISION_SIZE = { 1.3f,1.3f,1.3f };
public:

// データメンバの宣言 -----------------------------------------------
private:
	// メッセージID
	Message::MessageID m_messageID;

	//ライトのオンオフ状態
	bool m_isOn = false;

	//AABB当たり判定
	Box m_box;
	//ライト
	std::unique_ptr<Light> m_light;
	DirectX::SimpleMath::Vector4 m_color = { 1.0f,1.0f,1.0f,1.0f };

	std::unique_ptr<Sound> m_LightOnSound;
	Ito::DisplayCollision m_display;
	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	RumiRock(const ModelShader::PointLightCB& lightData,const GameObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~RumiRock();


// 操作
public:
	//初期化
	void Initialize(bool isOnlight);
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

	//ライトをオンにする
	void OnLight();
//　取得・設定
public:
	bool IsOnLight();

//　内部操作
private:

};

