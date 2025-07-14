/**
 * @file   Shader.cpp
 *
 * @brief  ＸＸＸＸに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Shader.h"
#include "Game/Common/ResourceManager.h"
#include"Game/Object/Light.h"
// クラス定数の定義 ===========================================================

std::unique_ptr<Shader> Shader::s_shader = nullptr;

const std::vector<D3D11_INPUT_ELEMENT_DESC> Shader::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,								D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",	    0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Shader::Shader()
	:m_graphics{Graphics::GetInstance()}
	,m_inputLayout{}				// 入力レイアウト

{
	CreateShader();
}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Shader::Initialize()
{
	
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Shader::Update()
{

}

void Shader::StartShader(ShaderType type, ID3D11Buffer* cBuffer)
{
	switch (type)
	{
	case Shader::Model:
		SetModelShader(cBuffer);
		break;
	case Shader::UI:
		break;
	default:
		break;
	}
}



void Shader::EndShader()
{
	ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	// シェーダーを無効化
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	// コンスタントバッファを無効化
	ID3D11Buffer* nullBuffer = nullptr;
	context->VSSetConstantBuffers(0, 1, &nullBuffer);
	context->PSSetConstantBuffers(0, 1, &nullBuffer);
	context->PSSetConstantBuffers(0, 1, &nullBuffer);
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Shader::Draw()
{
	ID3D11DeviceContext*		 context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = m_graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = m_graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = m_graphics->GetProjectionMatrix();
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Shader::Finalize()
{

}


/**
 * @brief クラスのインスタンスを取得する
 *
 * @param[in] なし
 *
 * @return クラスのインスタンスへのポインタ
 */
Shader* const Shader::GetInstance()
{
	if (!s_shader)
	{
		s_shader.reset(new Shader());
	}
	return s_shader.get();
}


/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
ID3D11InputLayout* Shader::GetInputLayout()
{
	return m_inputLayout.Get();
}


/**
 * @brief モデルの頂点シェーダーを取得する
 *
 * @param[in] なし
 *
 * @return モデルの頂点シェーダーへのポインタ
 */
ID3D11VertexShader* Shader::GetModelVS()
{
	return m_modelVS.Get();
}


/**
 * @brief モデルのピクセルシェーダーを取得する
 *
 * @param[in] なし
 *
 * @return モデルのピクセルシェーダーへのポインタ
 */
ID3D11PixelShader* Shader::GetModelPS()
{
	return m_modelPS.Get();
}


/**
 * @brief モデルのジオメトリシェーダーを取得する
 *
 * @param[in] なし
 *
 * @return モデルのジオメトリシェーダーへのポインタ
 */
ID3D11GeometryShader* Shader::GetModelGS()
{
	return m_modelGS.Get();
}

void Shader::RegisterLight(Light* light)
{
	m_lights.push_back(light);
}

void Shader::UnRegisterLight()
{
	for (auto& light : m_lights)
	{
		if (light)
		{
			light->Finalize();
		}
	}
	m_lights.clear();
}

void Shader::CreateShader()
{
	// シェーダーのバイナリデータを読み込む
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	BinaryFile vertexShader = resourceManager->RequestBinaryFile(L"Resources/Shaders/ModelShader/ModelVS.cso");
	BinaryFile pixelShader = resourceManager->RequestBinaryFile(L"Resources/Shaders/ModelShader/ModelPS.cso");
	BinaryFile geometryShader = resourceManager->RequestBinaryFile(L"Resources/Shaders/ModelShader/ModelGS.cso");
	// シェーダーを作成する
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
		vertexShader.GetData(), vertexShader.GetSize(), nullptr, m_modelVS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
		pixelShader.GetData(), pixelShader.GetSize(), nullptr, m_modelPS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
		geometryShader.GetData(), geometryShader.GetSize(), nullptr, m_modelGS.ReleaseAndGetAddressOf());


	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd2;
	ZeroMemory(&bd2, sizeof(bd2));
	bd2.Usage = D3D11_USAGE_DEFAULT;
	bd2.ByteWidth = sizeof(LightBuffer);
	bd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd2.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd2, nullptr, &m_lBuffer);

}

void Shader::SetModelShader(ID3D11Buffer* cBuffer)
{
	ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { cBuffer };

	LightBuffer lbuff;
	lbuff.LightPosition = DirectX::SimpleMath::Vector3(0.0f, 2.0f, 0.0f);
	lbuff.LightInvSqrRadius = 1.0f / (100.0f * 100.0f); //ライトが届く距離（２乗の逆数）
	lbuff.LightColor = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	lbuff.LightIntensity = 3.0f;
	lbuff.Attenuation = DirectX::SimpleMath::Vector4(1.0f, 0.0f, 0.005f, 0.0f); // デフォルトの減衰

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_lBuffer.Get(), 0, NULL, &lbuff, 0, 0);

	ID3D11Buffer* lb[1] = { m_lights[0]->GetLightBuffer()};

	context->PSSetConstantBuffers(1, 1, lb);


	// コンスタントバッファを設定
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	// シェーダーを設定
	context->VSSetShader(m_modelVS.Get(), nullptr, 0);
	context->PSSetShader(m_modelPS.Get(), nullptr, 0);
	context->GSSetShader(m_modelGS.Get(), nullptr, 0);

}
