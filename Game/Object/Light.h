/**
 * @file   Light.h
 *
 * @brief  Lightに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2025/09/17
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Object/GameObject.h"
#include"Game/Shader.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief Light
  */
class Light : public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:

	

// データメンバの宣言 -----------------------------------------------
private:
	// メッセージID
	Message::MessageID m_messageID;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_lBuffer;
	Shader::PointLight m_pointLight;
	Graphics* m_graphics;	// グラフィックスクラスのポインタ
	bool m_isOn; //ライトのオンオフ状態
	

	DirectX::SimpleMath::Vector3 m_color;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Light(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~Light();


// 操作
public:
	void Initialize();

	void Update( const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

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
	ID3D11Buffer* GetLightBuffer() const;

	Shader::PointLight GetLightData();

	void SetLightData(const Shader::PointLight& lightData);

	void SetLightColor(const DirectX::SimpleMath::Vector3& color);
//　内部操作
private:

};

