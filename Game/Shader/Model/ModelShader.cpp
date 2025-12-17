/**
 * @file   ModelShader.cpp
 *
 * @brief  モデル用シェーダーに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/08
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ModelShader.h"
#include "Game/Common/ResourceManager.h"
#include"Game/Object/Light.h"
// クラス定数の定義 ===========================================================


const std::vector<D3D11_INPUT_ELEMENT_DESC> ModelShader::MODEL_INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,								D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",	    0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
};





// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pathes
 */
ModelShader::ModelShader(const ShaderPath& pathes)
	:Shader{}
{
	CreateShader(pathes.vsPath, pathes.psPath, pathes.gsPath);
	CreateInputLayput(MODEL_INPUT_LAYOUT, pathes.vsPath);
	CreateConstantBuffer<ModelCB>();

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ModelShader::LightBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_lBuffer);

}


/**
 * @brief デストラクタ
 */
ModelShader::~ModelShader()
{
}


void ModelShader::StartShader()
{
	
	ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	
	//ライトの情報を渡す
	ModelShader::LightBuffer lB;
	lB.onLightCount = 0;
	for (Light* const& light : Messenger::GetInstance()->GetLights())
	{
		if (light->IsOn())
		{
			//ライトの情報を渡す
			lB.pointLights[lB.onLightCount] = light->GetLightData();
			//オンのライトの数を＋
			lB.onLightCount++;
		}
	}
	context->UpdateSubresource(m_lBuffer.Get(), 0, NULL, &lB, 0, 0);
	
	//ピクセルシェーダーにライトバッファを渡す
	ID3D11Buffer* lb[1] = { m_lBuffer.Get() };
	context->PSSetConstantBuffers(1, 1, lb);
	
	//明るさによって適用するTexを変えるテクスチャ
	context->PSSetShaderResources(1, 1, ResourceManager::GetInstance()->RequestTexture("toonmap.png"));
	
	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { GetConstantBuffer()};
	// コンスタントバッファを設定
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	// シェーダーを設定
	context->VSSetShader(GetVertexShader(), nullptr, 0);
	context->PSSetShader(GetPixelShader(), nullptr, 0);
	context->GSSetShader(GetGeometryShader(), nullptr, 0);
	

}