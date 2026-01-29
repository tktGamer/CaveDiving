/**
 * @file   Number3DShader.cpp
 *
 * @brief  3D上の数字シェーダーに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/29
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Number3DShader.h"
// クラス定数の定義 ===========================================================

//頂点関数
const std::vector<D3D11_INPUT_ELEMENT_DESC> Number3DShader::NUMBER_3D_INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pathes　シェーダーのパス
 */
Number3DShader::Number3DShader(const ShaderPath& pathes)
	:
	Shader{}
{
	CreateShader(pathes.vsPath, pathes.psPath, pathes.gsPath);
	CreateInputLayput(NUMBER_3D_INPUT_LAYOUT, pathes.vsPath);
	CreateConstantBuffer<Number3DCB>();

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CameraCB);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_cameraCB);

}

/**
 * @brief デストラクタ
 */
Number3DShader::~Number3DShader()
{
}

/**
 * @brief シェーダーの開始
 *
 * @param[in]　cameraCB  カメラのデータ
 *
 * @return なし
 */
void Number3DShader::StartShader(const CameraCB& cameraCB)
{
	//追加処理------------
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//カメラの情報を渡す
	context->UpdateSubresource(m_cameraCB.Get(), 0, NULL, &cameraCB, 0, 0); // b1 に渡す
	ID3D11Buffer* lb[1] = { m_cameraCB.Get() };
	context->GSSetConstantBuffers(1, 1, lb);
	//--------------------
	//元の処理へ
	Shader::StartShader();
}