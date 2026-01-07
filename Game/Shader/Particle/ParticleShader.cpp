/**
 * @file   ParticleShader.cpp
 *
 * @brief  パーティクルエフェクト用シェーダーに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/08
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ParticleShader.h"
#include "Game/Common/ResourceManager.h"
#include"Game/Object/Light.h"
// クラス定数の定義 ===========================================================


const std::vector<D3D11_INPUT_ELEMENT_DESC> ParticleShader::PARTICLE_INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR"	,	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};





// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pathes
 */
ParticleShader::ParticleShader(const ShaderPath& pathes)
	:Shader{}
{
	CreateShader(pathes.vsPath, pathes.psPath, pathes.gsPath);
	CreateInputLayput(PARTICLE_INPUT_LAYOUT, pathes.vsPath);
	CreateConstantBuffer<ParticleCB>();

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ParticleShader::CameraCB);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_cameraCB);

}


/**
 * @brief デストラクタ
 */
ParticleShader::~ParticleShader()
{
}

void ParticleShader::StartShader(const CameraCB& cameraCB)
{
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//カメラの情報を渡す
	context->UpdateSubresource(m_cameraCB.Get(), 0, NULL, &cameraCB, 0, 0); // b1 に渡す
	ID3D11Buffer* lb[1] = { m_cameraCB.Get() };
	context->GSSetConstantBuffers(1, 1, lb);

	Shader::StartShader();

}

