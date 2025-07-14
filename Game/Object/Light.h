/**
 * @file   Light.h
 *
 * @brief  Lightに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Object/GameObject.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief Light
  */
class Light : public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct LightBuffer
	{
		DirectX::SimpleMath::Vector3 LightPosition;      // ライト位置
		float LightInvSqrRadius; // ライトが届く距離（2乗の逆数）
		DirectX::SimpleMath::Vector3 LightColor;         // ライトカラー
		float LightIntensity;    // ライト強度
		DirectX::SimpleMath::Vector4	Attenuation;

	};


// データメンバの宣言 -----------------------------------------------
private:
	// オブジェクト番号
	int m_objectNumber;
	// メッセージID
	Message::MessageID m_messageID;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_lBuffer;
	LightBuffer m_lBuff;

	Graphics* m_graphics;	// グラフィックスクラスのポインタ
	bool m_isOn; //ライトのオンオフ状態
	
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Light(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// デストラクタ
	~Light();


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

	ID3D11Buffer* GetLightBuffer() const;

//　内部操作
private:

};

