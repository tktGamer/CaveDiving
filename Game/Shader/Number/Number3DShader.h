/**
 * @file   Number3DShader.h
 *
 * @brief  3D上の数字シェーダーに関するヘッダファイル
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
  * @brief 3D上の数字シェーダー
  */
class Number3DShader : public Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//3D上の数字用コンスタントバッファ
	struct Number3DCB
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
	};

	//カメラ情報用コンスタントバッファ
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
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> NUMBER_3D_INPUT_LAYOUT;
	// コンストラクタ
	Number3DShader(const ShaderPath& pathes);
	// デストラクタ
	~Number3DShader();
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

