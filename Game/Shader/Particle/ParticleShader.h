/**
 * @file   ParticleShader.h
 *
 * @brief  パーティクル用シェーダーに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/29
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Shader.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクル用シェーダー
  */
class ParticleShader : public Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//パーティクル用コンスタントバッファ
	struct ParticleCB
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	diffuse;
	};
	//カメラ情報のコンスタントバッファ
	struct CameraCB
	{
		DirectX::SimpleMath::Vector3 cameraPos; // カメラの右方向ベクトル
		float dummy1 = 0;
		DirectX::SimpleMath::Vector3 cameraUp; // カメラの上方向ベクトル
		float dummy2 = 0;
	};

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//	頂点情報関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> PARTICLE_INPUT_LAYOUT;
	// コンストラクタ
	ParticleShader(const ShaderPath& pathes);
	// デストラクタ
	~ParticleShader();
// 操作
	//シェーダー開始
	void StartShader(const CameraCB& cameraCB);

//　内部操作
private:
	
// データメンバの宣言 -----------------------------------------------
private:
	//カメラ情報のコンスタントバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cameraCB;
};

