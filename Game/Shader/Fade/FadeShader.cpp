/**
 * @file   FadeShader.cpp
 *
 * @brief  フェード用シェーダーに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/29
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "FadeShader.h"
// クラス定数の定義 ===========================================================

//頂点関数
const std::vector<D3D11_INPUT_ELEMENT_DESC> FadeShader::FADE_INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pathes　シェーダーのファイルパス
 */
FadeShader::FadeShader(const ShaderPath& pathes)
	:
	Shader{}
{
	CreateShader(pathes.vsPath, pathes.psPath, pathes.gsPath);
	CreateInputLayput(FADE_INPUT_LAYOUT, pathes.vsPath);
	CreateConstantBuffer<FadeCB>();
}

/**
 * @brief デストラクタ
 */
FadeShader::~FadeShader()
{
}