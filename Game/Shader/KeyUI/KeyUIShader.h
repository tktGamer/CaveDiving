/**
 * @file   KeyUIShader.h
 *
 * @brief  UI用シェーダーに関するヘッダファイル
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
  * @brief UIシェーダー
  */
class KeyUIShader : public Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//UI用コンスタントバッファ(送信側)
	struct KeyUICB
	{
		DirectX::SimpleMath::Vector2	windowSize;
		float AlphaData = 0.0f;
		float dammy = 0.0f;
	};
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//	頂点情報関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> KEY_UI_INPUT_LAYOUT;
	// コンストラクタ
	KeyUIShader(const ShaderPath& pathes);
	// デストラクタ
	~KeyUIShader();
// 操作

//　内部操作
private:
	
// データメンバの宣言 -----------------------------------------------
private:
};