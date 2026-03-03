/**
 * @file   KeyUIShader.cpp
 *
 * @brief  UI用シェーダーに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/29
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "KeyUIShader.h"
#include "Game/Common/ResourceManager.h"
// クラス定数の定義 ===========================================================

//頂点関数
const std::vector<D3D11_INPUT_ELEMENT_DESC> KeyUIShader::KEY_UI_INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pathes  シェーダーのパス
 */
KeyUIShader::KeyUIShader(const ShaderPath& pathes)
	:
	Shader{}
{
	CreateShader(pathes.vsPath, pathes.psPath, pathes.gsPath);
	CreateInputLayput(KEY_UI_INPUT_LAYOUT, pathes.vsPath);
	CreateConstantBuffer<KeyUICB>();
}

/**
 * @brief デストラクタ
 */
KeyUIShader::~KeyUIShader()
{
}