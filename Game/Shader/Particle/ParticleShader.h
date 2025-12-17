/**
 * @file   ParticleShader.h
 *
 * @brief  モデル用シェーダーに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/08
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"../Shader.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief モデルシェーダー
  */
class ParticleShader : public Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//データ受け渡し用コンスタントバッファ(送信側)
	struct ParticleCB
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Light;

	};

	struct CameraCB
	{
		DirectX::SimpleMath::Vector3 cameraPos; // カメラの右方向ベクトル
		float dummy1 = 0;
		DirectX::SimpleMath::Vector3 cameraUp; // カメラの上方向ベクトル
		float dummy2 = 0;
	};

// データメンバの宣言 -----------------------------------------------
private:
	//カメラ情報のコンスタントバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cameraCB;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//	頂点情報関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> PARTICLE_INPUT_LAYOUT;
	// コンストラクタ
	ParticleShader(const ShaderPath& pathes);

	// デストラクタ
	~ParticleShader();


// 操作
public:
	void StartShader(const CameraCB& cameraCB);
//　取得・設定
public:

//　内部操作
private:
	
};

