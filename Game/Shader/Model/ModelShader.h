/**
 * @file   ModelShader.h
 *
 * @brief  モデル用シェーダーに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　22025/10/24
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"../Shader.h"
// クラスの宣言 ===============================================================
class Light;

// クラスの定義 ===============================================================
/**
  * @brief モデルシェーダー
  */
class ModelShader : public Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ModelCB
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	flash;

	};
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ItemCB
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	color;

	};

	//	データ受け渡し用コンスタントバッファ(送信側)
	struct PointLightCB
	{
		DirectX::SimpleMath::Vector3 LightPosition;      // ライト位置
		float LightInvSqrRadius;						 // ライトの届く距離
		DirectX::SimpleMath::Vector3 LightColor;         // ライトカラー
		float LightIntensity = 1.0f;					 // ライト強度
		DirectX::SimpleMath::Vector4	Attenuation;

	};

	static constexpr int MAX_LIGHT = 8;
	struct LightBuffer 
	{
		PointLightCB pointLights[MAX_LIGHT];
		int onLightCount;
		DirectX::SimpleMath::Vector3 dammy;

	};



// データメンバの宣言 -----------------------------------------------
private:


	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_lBuffer;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//	頂点情報関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> MODEL_INPUT_LAYOUT;
	// コンストラクタ
	ModelShader(const ShaderPath& pathes);

	// デストラクタ
	~ModelShader();


// 操作
public:
	void StartShader() override;
//　取得・設定
public:

//　内部操作
private:
	
};

