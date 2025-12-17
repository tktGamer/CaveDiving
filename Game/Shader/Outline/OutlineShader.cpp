/**
 * @file   OutlineShader.cpp
 *
 * @brief  モデル用シェーダーに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/08
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "OutlineShader.h"
#include "Game/Common/ResourceManager.h"
// クラス定数の定義 ===========================================================


const std::vector<D3D11_INPUT_ELEMENT_DESC> OutlineShader::OUTLINE_INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,								D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",	    0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
};





// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pathes
 */
OutlineShader::OutlineShader(const ShaderPath& pathes)
	:Shader{}
{
	CreateShader(pathes.vsPath, pathes.psPath, pathes.gsPath);
	CreateInputLayput(OUTLINE_INPUT_LAYOUT, pathes.vsPath);
	CreateConstantBuffer<OutlineCB>();
}


/**
 * @brief デストラクタ
 */
OutlineShader::~OutlineShader()
{
}

