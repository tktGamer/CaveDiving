/**
 * @file   Light.h
 *
 * @brief  ライトに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2025/09/17
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Object/GameObject.h"
#include"Game/Shader/Model/ModelShader.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief ライト
  */
class Light : public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:

	

// データメンバの宣言 -----------------------------------------------
private:
	// メッセージID
	Message::MessageID m_messageID;
	ModelShader::PointLightCB  m_pointLight;
	//ライトのオンオフ状態
	bool m_isOn; 
	

	DirectX::SimpleMath::Vector3 m_color;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Light(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~Light();


// 操作
public:
	//初期化
	void Initialize();
	//更新
	void Update( const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;

	//描画
	void Draw() override;
	//終了
	void Finalize();

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);

	//衝突応答分岐
	void CollisionResponce(GameObject* other) override;

	//ライトを点ける
	void LightOn();
//　取得・設定
public:
	//ライトが点いているか
	bool IsOn()const;

	const ModelShader::PointLightCB& GetLightData();

	void SetLightData(const ModelShader::PointLightCB& lightData);

	void SetLightColor(const DirectX::SimpleMath::Vector3& color);
//　内部操作
private:

};

