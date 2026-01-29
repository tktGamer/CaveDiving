/**
 * @file   ModelShader.h
 *
 * @brief  モデル用シェーダーに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/01/29
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
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
	//	モデル用コンスタントバッファ(送信側)
	struct ModelCB
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		//白くする　xを使用
		DirectX::SimpleMath::Vector4	flash;

	};
	//	アイテムモデル用コンスタントバッファ(送信側)
	struct ItemCB
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		//アイテムの色
		DirectX::SimpleMath::Vector4	color;

	};

	//	ポイントライト用コンスタントバッファ
	struct PointLightCB
	{
		DirectX::SimpleMath::Vector3 LightPosition;      // ライト位置
		float LightInvSqrRadius =0.0f;						 // ライトの届く距離
		DirectX::SimpleMath::Vector3 LightColor;         // ライトカラー
		float LightIntensity = 1.0f;					 // ライト強度
		DirectX::SimpleMath::Vector4	Attenuation;

	};
	//ライトの最大数
	static constexpr int MAX_LIGHT = 8;
	//モデルシェーダーに送るライトの総データ
	struct LightBuffer 
	{
		PointLightCB pointLights[MAX_LIGHT];
		int onLightCount = 0;
		DirectX::SimpleMath::Vector3 dammy;

	};

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//	頂点情報関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> MODEL_INPUT_LAYOUT;
	// コンストラクタ
	ModelShader(const ShaderPath& pathes);
	// デストラクタ
	~ModelShader();
// 操作
	//シェーダー開始
	void StartShader() override;
//　内部操作
private:
	
// データメンバの宣言 -----------------------------------------------
private:
	//LightBuffer用の変数
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_lBuffer;
};