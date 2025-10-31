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

const std::vector<D3D11_INPUT_ELEMENT_DESC> Shader::MODEL_INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,								D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",	    0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

const std::vector<D3D11_INPUT_ELEMENT_DESC> Shader::UI_INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
const std::vector<D3D11_INPUT_ELEMENT_DESC> Shader::NUMBER_INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

const std::vector<D3D11_INPUT_ELEMENT_DESC> Shader::PARTICLE_INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

const std::vector<D3D11_INPUT_ELEMENT_DESC> Shader::FADE_INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

const std::vector<D3D11_INPUT_ELEMENT_DESC> Shader::OUTLINE_INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,								D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",	    0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
};



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


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Shader::Shader()
	:m_graphics{Graphics::GetInstance()}
	//モデルシェーダー用変数
	,m_modelInputLayout{}				// 入力レイアウト
	,m_modelCBuffer{}
	,m_modelVS{}
	,m_modelPS{}
	,m_modelGS{}
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


/**
 * @brief シェーダー有効化
 *
 * @param[in] type  使用するシェーダー
 * @param[in] cBuffer VS・GS・PS共通のコンスタントバッファ(個々に必要なものは手動で設定)
 *
 * @return なし
 */
void Shader::StartShader(ShaderType type, ID3D11Buffer* cBuffer)
{
	switch (type)
	{
	case Shader::Model:
		SetModelShader(cBuffer);
		break;
	case Shader::UI:
		SetUIShader(cBuffer);
		break;
	case Shader::Particle:
		SetParticleShader(cBuffer);
		break;
	case Shader::Fade:
		SetFadeShader(cBuffer);
		break;
	case Shader::Outline:
		SetOutlineShader(cBuffer);
		break;
	case Shader::Number2D:
		SetNumber2DShader(cBuffer);
	default:
		break;
	}
}




/**
 * @brief シェーダー無効化
 *
 * @param[in] なし
 *
 * @return なし
 */
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
 * @brief インプットレイアウトの取得
 *
 * @param[in] type 取得するインプットレイアウトの種類
 *
 * @return インプットレイアウトのポインタ
 */
ID3D11InputLayout* Shader::GetInputLayout(ShaderType type)
{
	switch (type)
	{
	case Shader::Model:
		return m_modelInputLayout.Get();
		break;
	case Shader::UI:
		return m_UIInputLayout.Get();
		break;
	case Shader::Number2D:
		return m_numberInputLayout.Get();
		break;
	case Shader::Particle:
		return m_ParticleInputLayout.Get();
		break;
	case Shader::Fade:
		return m_fadeInputLayout.Get();
		break;
	case Shader::Outline:
		return m_outlineInputLayout.Get();
		break;
	default:
		break;
	}
	return nullptr;
}

/**
 * @brief コンスタントバッファの取得
 *
 * @param[in] type 取得するコンスタントバッファの種類
 *
 * @return コンスタントバッファのポインタ
 */
ID3D11Buffer* Shader::GetCBuffer(ShaderType type)
{
	switch (type)
	{
	case Shader::Model:
		return m_modelCBuffer.Get();
		break;
	case Shader::UI:
		return m_UICBuffer.Get();
		break;
	case Shader::Number2D:
		return m_numberCBuffer.Get();
		break;
	case Shader::Particle:
		return m_ParticleCBuffer.Get();
		break;
	case Shader::Fade:
		return m_fadeCBuffer.Get();
		break;
	case Shader::Outline:
		return m_outlineCBuffer.Get();
	default:
		break;
	}
	return nullptr;
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

ID3D11PixelShader* Shader::GetItemPS()
{
	return m_itemPS.Get();
}

ID3D11PixelShader* Shader::GetRockPS()
{
	return m_rockPS.Get();
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


/**
 * @brief シェーダーの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
void Shader::CreateShader()
{
	LoadModelShader();
	LoadUIShader();
	LoadParticleShader();
	LoadFadeShader();
	LoadOutlineShader();
	LoadNumber2DShader();
}

/**
 * @brief モデルシェーダーの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
void Shader::LoadModelShader()
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



	pixelShader = resourceManager->RequestBinaryFile(L"Resources/Shaders/ModelShader/ItemModelPS.cso");
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
		pixelShader.GetData(), pixelShader.GetSize(), nullptr, m_itemPS.ReleaseAndGetAddressOf());
	pixelShader = resourceManager->RequestBinaryFile(L"Resources/Shaders/LumiRockShader/LumiRockPS.cso");
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
		pixelShader.GetData(), pixelShader.GetSize(), nullptr, m_rockPS.ReleaseAndGetAddressOf());

	//インプットレイアウトの作成
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
		&MODEL_INPUT_LAYOUT[0],
		static_cast<UINT>(MODEL_INPUT_LAYOUT.size()),
		vertexShader.GetData(),
		vertexShader.GetSize(),
		m_modelInputLayout.GetAddressOf());

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_modelCBuffer);

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd2;
	ZeroMemory(&bd2, sizeof(bd2));
	bd2.Usage = D3D11_USAGE_DEFAULT;
	bd2.ByteWidth = sizeof(LightBuffer);
	bd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd2.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd2, nullptr, &m_lBuffer);

}

/**
 * @brief UIシェーダーの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
void Shader::LoadUIShader()
{
	// シェーダーのバイナリデータを読み込む
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	BinaryFile VSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/UIShader/UIVS.cso");
	BinaryFile PSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/UIShader/UIPS.cso");
	BinaryFile GSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/UIShader/UIGS.cso");
	// シェーダーを作成する
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
		VSData.GetData(), VSData.GetSize(), nullptr, m_UIVS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
		PSData.GetData(), PSData.GetSize(), nullptr, m_UIPS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
		GSData.GetData(), GSData.GetSize(), nullptr, m_UIGS.ReleaseAndGetAddressOf());

	//インプットレイアウトの作成
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
		&UI_INPUT_LAYOUT[0],
		static_cast<UINT>(UI_INPUT_LAYOUT.size()),
		VSData.GetData(),
		VSData.GetSize(),
		m_UIInputLayout.GetAddressOf());

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(UIConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_UICBuffer);


}

void Shader::LoadParticleShader()
{
	// シェーダーのバイナリデータを読み込む
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	BinaryFile VSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/ParticleShader/ParticleVS.cso");
	BinaryFile PSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/ParticleShader/ParticlePS.cso");
	BinaryFile GSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/ParticleShader/ParticleGS.cso");
	// シェーダーを作成する
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
		VSData.GetData(), VSData.GetSize(), nullptr, m_ParticleVS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
		PSData.GetData(), PSData.GetSize(), nullptr, m_ParticlePS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
		GSData.GetData(), GSData.GetSize(), nullptr, m_ParticleGS.ReleaseAndGetAddressOf());

	//インプットレイアウトの作成
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
		&PARTICLE_INPUT_LAYOUT[0],
		static_cast<UINT>(PARTICLE_INPUT_LAYOUT.size()),
		VSData.GetData(),
		VSData.GetSize(),
		m_ParticleInputLayout.GetAddressOf());

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ParticleConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_ParticleCBuffer);


}

void Shader::LoadFadeShader()
{
	// シェーダーのバイナリデータを読み込む
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	BinaryFile VSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/FadeShader/FadeVS.cso");
	BinaryFile PSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/FadeShader/FadePS.cso");
	BinaryFile GSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/FadeShader/FadeGS.cso");
	// シェーダーを作成する
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
		VSData.GetData(), VSData.GetSize(), nullptr, m_fadeVS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
		PSData.GetData(), PSData.GetSize(), nullptr, m_fadePS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
		GSData.GetData(), GSData.GetSize(), nullptr, m_fadeGS.ReleaseAndGetAddressOf());

	//インプットレイアウトの作成
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
		&FADE_INPUT_LAYOUT[0],
		static_cast<UINT>(FADE_INPUT_LAYOUT.size()),
		VSData.GetData(),
		VSData.GetSize(),
		m_fadeInputLayout.GetAddressOf());

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(FadeConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_fadeCBuffer);

}

void Shader::LoadOutlineShader()
{

	// シェーダーのバイナリデータを読み込む
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	BinaryFile VSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/OutlineShader/OutlineVS.cso");
	BinaryFile PSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/OutlineShader/OutlinePS.cso");
	BinaryFile GSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/OutlineShader/OutlineGS.cso");
	// シェーダーを作成する
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
		VSData.GetData(), VSData.GetSize(), nullptr, m_outlineVS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
		PSData.GetData(), PSData.GetSize(), nullptr, m_outlinePS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
		GSData.GetData(), GSData.GetSize(), nullptr, m_outlineGS.ReleaseAndGetAddressOf());

	//インプットレイアウトの作成
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
		&OUTLINE_INPUT_LAYOUT[0],
		static_cast<UINT>(OUTLINE_INPUT_LAYOUT.size()),
		VSData.GetData(),
		VSData.GetSize(),
		m_outlineInputLayout.GetAddressOf());

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(OutlineConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_outlineCBuffer);

}

void Shader::LoadNumber2DShader()
{
	// シェーダーのバイナリデータを読み込む
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	BinaryFile VSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/NumberShader/NumberVS.cso");
	BinaryFile PSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/NumberShader/NumberPS.cso");
	BinaryFile GSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/NumberShader/NumberGS.cso");
	// シェーダーを作成する
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
		VSData.GetData(), VSData.GetSize(), nullptr, m_numberVS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
		PSData.GetData(), PSData.GetSize(), nullptr, m_numberPS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
		GSData.GetData(), GSData.GetSize(), nullptr, m_numberGS.ReleaseAndGetAddressOf());

	//インプットレイアウトの作成
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
		&NUMBER_INPUT_LAYOUT[0],
		static_cast<UINT>(NUMBER_INPUT_LAYOUT.size()),
		VSData.GetData(),
		VSData.GetSize(),
		m_numberInputLayout.GetAddressOf());

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(NumberConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_numberCBuffer);

}

void Shader::SetModelShader(ID3D11Buffer* cBuffer)
{
	ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { cBuffer };


	LightBuffer lB;
	lB.onLightCount = 0;
	for (auto& light : m_lights) 
	{
		if (light->IsOn())
		{
			lB.pointLights[lB.onLightCount] = light->GetLightData();
			lB.onLightCount++;
		}
	}
	context->UpdateSubresource(m_lBuffer.Get(), 0, NULL, &lB, 0, 0);


	ID3D11Buffer* lb[1] = { m_lBuffer.Get()};

	context->PSSetConstantBuffers(1, 1, lb);


	context->PSSetShaderResources(1, 1, ResourceManager::GetInstance()->RequestTexture("toonmap.png"));

	// コンスタントバッファを設定
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	// シェーダーを設定
	context->VSSetShader(m_modelVS.Get(), nullptr, 0);
	context->PSSetShader(m_modelPS.Get(), nullptr, 0);
	context->GSSetShader(m_modelGS.Get(), nullptr, 0);

}

void Shader::SetUIShader(ID3D11Buffer* cBuffer)
{
	
	ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { cBuffer };

	// コンスタントバッファを設定
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	// シェーダーを設定
	context->VSSetShader(m_UIVS.Get(), nullptr, 0);
	context->PSSetShader(m_UIPS.Get(), nullptr, 0);
	context->GSSetShader(m_UIGS.Get(), nullptr, 0);


}

void Shader::SetParticleShader(ID3D11Buffer* cBuffer)
{
	ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { cBuffer };

	// コンスタントバッファを設定
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	// シェーダーを設定
	context->VSSetShader(m_ParticleVS.Get(), nullptr, 0);
	context->PSSetShader(m_ParticlePS.Get(), nullptr, 0);
	context->GSSetShader(m_ParticleGS.Get(), nullptr, 0);


}

void Shader::SetFadeShader(ID3D11Buffer* cBuffer)
{
	ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { cBuffer };

	// コンスタントバッファを設定
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	// シェーダーを設定
	context->VSSetShader(m_fadeVS.Get(), nullptr, 0);
	context->PSSetShader(m_fadePS.Get(), nullptr, 0);
	context->GSSetShader(m_fadeGS.Get(), nullptr, 0);

}

void Shader::SetOutlineShader(ID3D11Buffer* cBuffer)
{
	ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { cBuffer };

	// コンスタントバッファを設定
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	// シェーダーを設定
	context->VSSetShader(m_outlineVS.Get(), nullptr, 0);
	context->PSSetShader(m_outlinePS.Get(), nullptr, 0);
	context->GSSetShader(m_outlineGS.Get(), nullptr, 0);


}

void Shader::SetNumber2DShader(ID3D11Buffer* cBuffer)
{

	ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { cBuffer };

	// コンスタントバッファを設定
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	// シェーダーを設定
	context->VSSetShader(m_numberVS.Get(), nullptr, 0);
	context->PSSetShader(m_numberPS.Get(), nullptr, 0);
	context->GSSetShader(m_numberGS.Get(), nullptr, 0);


}
