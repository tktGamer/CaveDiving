/**
 * @file   OutlineShader.h
 *
 * @brief  アウトライン用シェーダーに関するヘッダファイル
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
  * @brief アウトライン用シェーダー
  */
class OutlineShader : public Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//アウトライン用コンスタントバッファ
	struct OutlineCB
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		//アウトラインの太さ
		float outlineThickness = 0.0f;
		DirectX::SimpleMath::Vector3 dummy;
	};
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//	頂点情報関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> OUTLINE_INPUT_LAYOUT;
	// コンストラクタ
	OutlineShader(const ShaderPath& pathes);
	// デストラクタ
	~OutlineShader();
// 操作

//　内部操作
private:
	
// データメンバの宣言 -----------------------------------------------
private:

};