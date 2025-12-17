/**
 * @file   ShaderManager.cpp
 *
 * @brief  ＸＸＸＸに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Common/ResourceManager.h"
#include"Game/Object/Light.h"
#include "ShaderManager.h"
// クラス定数の定義 ===========================================================

std::unique_ptr<ShaderManager> ShaderManager::s_shader = nullptr;

//const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderManager::MODEL_INPUT_LAYOUT =
//{
//	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,								D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "NORMAL",	    0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
//};
//
//const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderManager::UI_INPUT_LAYOUT =
//{
//	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
//};
//const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderManager::NUMBER_INPUT_LAYOUT =
//{
//	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
//};
//
//const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderManager::PARTICLE_INPUT_LAYOUT =
//{
//	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
//};
//
//const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderManager::FADE_INPUT_LAYOUT =
//{
//	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
//};
//
//const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderManager::OUTLINE_INPUT_LAYOUT =
//{
//	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,								D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "NORMAL",	    0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
//};
//


/**
 * @brief クラスのインスタンスを取得する
 *
 * @param[in] なし
 *
 * @return クラスのインスタンスへのポインタ
 */
ShaderManager* const ShaderManager::GetInstance()
{
	if (!s_shader)
	{
		s_shader.reset(new ShaderManager());
	}
	return s_shader.get();
}

void ShaderManager::SetCameraCB(const ParticleShader::CameraCB& cameraCB)
{
	m_cameraCB = cameraCB;
}


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
ShaderManager::ShaderManager()
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
void ShaderManager::Initialize()
{

}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::Update()
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
void ShaderManager::StartShader(const ShaderType& type)
{
	switch (type)
	{
	case ShaderManager::Model:
		SetModelShader();
		break;
	case ShaderManager::Item_Model:
		SetItemShader();
		break;
	case ShaderManager::Rock_Model:
		SetRockShader();
		break;
	case ShaderManager::UI:
		SetUIShader();
		break;
	case ShaderManager::Particle:
		SetParticleShader();
		break;
	case ShaderManager::Fade:
		SetFadeShader();
		break;
	case ShaderManager::Outline:
		SetOutlineShader();
		break;
	case ShaderManager::Number2D:
		SetNumber2DShader();
		break;
	case ShaderManager::Number3D:
		SetNumber3DShader();
		break;
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
void ShaderManager::EndShader()
{
	ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
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
void ShaderManager::Finalize()
{

}




/**
 * @brief インプットレイアウトの取得
 *
 * @param[in] type 取得するインプットレイアウトの種類
 *
 * @return インプットレイアウトのポインタ
 */
ID3D11InputLayout* ShaderManager::GetInputLayout(ShaderType type)
{
	switch (type)
	{
	case ShaderManager::Model:
		return m_modelShader->GetInputLayout();
		break;
	case ShaderManager::Item_Model:
		return m_itemShader->GetInputLayout();
		break;
	case ShaderManager::Rock_Model:
		return m_rockShader->GetInputLayout();
		break;
	case ShaderManager::UI:
		return m_uiShader->GetInputLayout();
		break;
	case ShaderManager::Number2D:
		return m_number2DShader->GetInputLayout();
		break;
	case ShaderManager::Number3D:
		return m_number3DShader->GetInputLayout();
		break;
	case ShaderManager::Particle:
		return m_particleShader->GetInputLayout();
		break;
	case ShaderManager::Fade:
		return m_fadeShader->GetInputLayout();
		break;
	case ShaderManager::Outline:
		return m_outlineShader->GetInputLayout();
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
ID3D11Buffer* ShaderManager::GetCBuffer(ShaderType type)
{
	switch (type)
	{
	case ShaderManager::Model:
		return m_modelShader->GetConstantBuffer();
		break;
	case ShaderManager::Item_Model:
		return m_itemShader->GetConstantBuffer();
		break;
	case ShaderManager::Rock_Model:
		return m_rockShader->GetConstantBuffer();
		break;
	case ShaderManager::UI:
		return m_uiShader->GetConstantBuffer();
		break;
	case ShaderManager::Number2D:
		return m_number2DShader->GetConstantBuffer();
		break;
	case ShaderManager::Number3D:
		return m_number3DShader->GetConstantBuffer();
		break;
	case ShaderManager::Particle:
		return m_particleShader->GetConstantBuffer();
		break;
	case ShaderManager::Fade:
		return m_fadeShader->GetConstantBuffer();
		break;
	case ShaderManager::Outline:
		return m_outlineShader->GetConstantBuffer();
	default:
		break;
	}
	return nullptr;
}

//
///**
// * @brief モデルの頂点シェーダーを取得する
// *
// * @param[in] なし
// *
// * @return モデルの頂点シェーダーへのポインタ
// */
//ID3D11VertexShader* ShaderManager::GetModelVS()
//{
//	return m_modelVS.Get();
//}
//
//
///**
// * @brief モデルのピクセルシェーダーを取得する
// *
// * @param[in] なし
// *
// * @return モデルのピクセルシェーダーへのポインタ
// */
//ID3D11PixelShader* ShaderManager::GetModelPS()
//{
//	return m_modelPS.Get();
//}
//
//
///**
// * @brief モデルのジオメトリシェーダーを取得する
// *
// * @param[in] なし
// *
// * @return モデルのジオメトリシェーダーへのポインタ
// */
//ID3D11GeometryShader* ShaderManager::GetModelGS()
//{
//	return m_modelGS.Get();
//}
//
//ID3D11PixelShader* ShaderManager::GetItemPS()
//{
//	return m_itemPS.Get();
//}
//
//ID3D11PixelShader* ShaderManager::GetRockPS()
//{
//	return m_rockPS.Get();
//}
//
//void ShaderManager::RegisterLight(Light* light)
//{
//	m_lights.push_back(light);
//}
//
//void ShaderManager::UnRegisterLight()
//{
//	for (auto& light : m_lights)
//	{
//		if (light)
//		{
//			light->Finalize();
//		}
//	}
//	m_lights.clear();
//}


/**
 * @brief シェーダーの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::CreateShader()
{
	LoadModelShader();
	LoadUIShader();
	LoadParticleShader();
	LoadFadeShader();
	LoadOutlineShader();
	LoadNumber2DShader();
	LoadNumber3DShader();
}

/**
 * @brief モデルシェーダーの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::LoadModelShader()
{
	Shader::ShaderPath path;
	path.vsPath = L"Resources/Shaders/ModelShader/ModelVS.cso";
	path.psPath = L"Resources/Shaders/ModelShader/ModelPS.cso";
	path.gsPath = L"Resources/Shaders/ModelShader/ModelGS.cso";
	m_modelShader = std::make_unique<ModelShader>(path);

	path.psPath = L"Resources/Shaders/ModelShader/ItemModelPS.cso";
	m_itemShader = std::make_unique<ModelShader>(path);

	path.psPath = L"Resources/Shaders/LumiRockShader/LumiRockPS.cso";
	m_rockShader = std::make_unique<ModelShader>(path);

	//// シェーダーのバイナリデータを読み込む
	//ResourceManager* resourceManager = ResourceManager::GetInstance();
	//BinaryFile vertexShader = resourceManager->RequestBinaryFile(L"Resources/Shaders/ModelShader/ModelVS.cso");
	//BinaryFile pixelShader = resourceManager->RequestBinaryFile(L"Resources/Shaders/ModelShader/ModelPS.cso");
	//BinaryFile geometryShader = resourceManager->RequestBinaryFile(L"Resources/Shaders/ModelShader/ModelGS.cso");
	//// シェーダーを作成する
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
	//	vertexShader.GetData(), vertexShader.GetSize(), nullptr, m_modelVS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
	//	pixelShader.GetData(), pixelShader.GetSize(), nullptr, m_modelPS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
	//	geometryShader.GetData(), geometryShader.GetSize(), nullptr, m_modelGS.ReleaseAndGetAddressOf());



	//pixelShader = resourceManager->RequestBinaryFile(L"Resources/Shaders/ModelShader/ItemModelPS.cso");
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
	//	pixelShader.GetData(), pixelShader.GetSize(), nullptr, m_itemPS.ReleaseAndGetAddressOf());
	//pixelShader = resourceManager->RequestBinaryFile(L"Resources/Shaders/LumiRockShader/LumiRockPS.cso");
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
	//	pixelShader.GetData(), pixelShader.GetSize(), nullptr, m_rockPS.ReleaseAndGetAddressOf());

	////インプットレイアウトの作成
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
	//	&MODEL_INPUT_LAYOUT[0],
	//	static_cast<UINT>(MODEL_INPUT_LAYOUT.size()),
	//	vertexShader.GetData(),
	//	vertexShader.GetSize(),
	//	m_modelInputLayout.GetAddressOf());

	////	シェーダーにデータを渡すためのコンスタントバッファ生成
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(ConstBuffer);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_modelCBuffer);

	////	シェーダーにデータを渡すためのコンスタントバッファ生成
	//D3D11_BUFFER_DESC bd2;
	//ZeroMemory(&bd2, sizeof(bd2));
	//bd2.Usage = D3D11_USAGE_DEFAULT;
	//bd2.ByteWidth = sizeof(LightBuffer);
	//bd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd2.CPUAccessFlags = 0;
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd2, nullptr, &m_lBuffer);

}

/**
 * @brief UIシェーダーの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::LoadUIShader()
{
	Shader::ShaderPath path;
	path.vsPath = L"Resources/Shaders/UIShader/UIVS.cso";
	path.psPath = L"Resources/Shaders/UIShader/UIPS.cso";
	path.gsPath = L"Resources/Shaders/UIShader/UIGS.cso";
	m_uiShader = std::make_unique<UIShader>(path);

	//// シェーダーのバイナリデータを読み込む
	//ResourceManager* resourceManager = ResourceManager::GetInstance();
	//BinaryFile VSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/UIShader/UIVS.cso");
	//BinaryFile PSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/UIShader/UIPS.cso");
	//BinaryFile GSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/UIShader/UIGS.cso");
	//// シェーダーを作成する
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
	//	VSData.GetData(), VSData.GetSize(), nullptr, m_UIVS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
	//	PSData.GetData(), PSData.GetSize(), nullptr, m_UIPS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
	//	GSData.GetData(), GSData.GetSize(), nullptr, m_UIGS.ReleaseAndGetAddressOf());

	////インプットレイアウトの作成
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
	//	&UI_INPUT_LAYOUT[0],
	//	static_cast<UINT>(UI_INPUT_LAYOUT.size()),
	//	VSData.GetData(),
	//	VSData.GetSize(),
	//	m_UIInputLayout.GetAddressOf());

	////	シェーダーにデータを渡すためのコンスタントバッファ生成
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(UIConstBuffer);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_UICBuffer);


}

void ShaderManager::LoadParticleShader()
{
	Shader::ShaderPath path;
	path.vsPath = L"Resources/Shaders/ParticleShader/ParticleVS.cso";
	path.psPath = L"Resources/Shaders/ParticleShader/ParticlePS.cso";
	path.gsPath = L"Resources/Shaders/ParticleShader/ParticleGS.cso";
	m_particleShader = std::make_unique<ParticleShader>(path);

	//// シェーダーのバイナリデータを読み込む
	//ResourceManager* resourceManager = ResourceManager::GetInstance();
	//BinaryFile VSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/ParticleShader/ParticleVS.cso");
	//BinaryFile PSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/ParticleShader/ParticlePS.cso");
	//BinaryFile GSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/ParticleShader/ParticleGS.cso");
	//// シェーダーを作成する
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
	//	VSData.GetData(), VSData.GetSize(), nullptr, m_ParticleVS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
	//	PSData.GetData(), PSData.GetSize(), nullptr, m_ParticlePS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
	//	GSData.GetData(), GSData.GetSize(), nullptr, m_ParticleGS.ReleaseAndGetAddressOf());

	////インプットレイアウトの作成
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
	//	&PARTICLE_INPUT_LAYOUT[0],
	//	static_cast<UINT>(PARTICLE_INPUT_LAYOUT.size()),
	//	VSData.GetData(),
	//	VSData.GetSize(),
	//	m_ParticleInputLayout.GetAddressOf());

	////	シェーダーにデータを渡すためのコンスタントバッファ生成
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(ParticleConstBuffer);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_ParticleCBuffer);


}

void ShaderManager::LoadFadeShader()
{
	Shader::ShaderPath path;
	path.vsPath = L"Resources/Shaders/FadeShader/FadeVS.cso";
	path.psPath = L"Resources/Shaders/FadeShader/FadePS.cso";
	path.gsPath = L"Resources/Shaders/FadeShader/FadeGS.cso";
	m_fadeShader = std::make_unique<FadeShader>(path);

	//// シェーダーのバイナリデータを読み込む
	//ResourceManager* resourceManager = ResourceManager::GetInstance();
	//BinaryFile VSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/FadeShader/FadeVS.cso");
	//BinaryFile PSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/FadeShader/FadePS.cso");
	//BinaryFile GSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/FadeShader/FadeGS.cso");
	//// シェーダーを作成する
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
	//	VSData.GetData(), VSData.GetSize(), nullptr, m_fadeVS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
	//	PSData.GetData(), PSData.GetSize(), nullptr, m_fadePS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
	//	GSData.GetData(), GSData.GetSize(), nullptr, m_fadeGS.ReleaseAndGetAddressOf());

	////インプットレイアウトの作成
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
	//	&FADE_INPUT_LAYOUT[0],
	//	static_cast<UINT>(FADE_INPUT_LAYOUT.size()),
	//	VSData.GetData(),
	//	VSData.GetSize(),
	//	m_fadeInputLayout.GetAddressOf());

	////	シェーダーにデータを渡すためのコンスタントバッファ生成
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(FadeConstBuffer);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_fadeCBuffer);

}

void ShaderManager::LoadOutlineShader()
{
	Shader::ShaderPath path;
	path.vsPath = L"Resources/Shaders/OutlineShader/OutlineVS.cso";
	path.psPath = L"Resources/Shaders/OutlineShader/OutlinePS.cso";
	path.gsPath = L"Resources/Shaders/OutlineShader/OutlineGS.cso";
	m_outlineShader = std::make_unique<OutlineShader>(path);

	//// シェーダーのバイナリデータを読み込む
	//ResourceManager* resourceManager = ResourceManager::GetInstance();
	//BinaryFile VSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/OutlineShader/OutlineVS.cso");
	//BinaryFile PSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/OutlineShader/OutlinePS.cso");
	//BinaryFile GSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/OutlineShader/OutlineGS.cso");
	//// シェーダーを作成する
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
	//	VSData.GetData(), VSData.GetSize(), nullptr, m_outlineVS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
	//	PSData.GetData(), PSData.GetSize(), nullptr, m_outlinePS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
	//	GSData.GetData(), GSData.GetSize(), nullptr, m_outlineGS.ReleaseAndGetAddressOf());

	////インプットレイアウトの作成
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
	//	&OUTLINE_INPUT_LAYOUT[0],
	//	static_cast<UINT>(OUTLINE_INPUT_LAYOUT.size()),
	//	VSData.GetData(),
	//	VSData.GetSize(),
	//	m_outlineInputLayout.GetAddressOf());

	////	シェーダーにデータを渡すためのコンスタントバッファ生成
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(OutlineConstBuffer);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_outlineCBuffer);

}

void ShaderManager::LoadNumber2DShader()
{
	Shader::ShaderPath path;
	path.vsPath = L"Resources/Shaders/NumberShader/NumberVS.cso";
	path.psPath = L"Resources/Shaders/NumberShader/NumberPS.cso";
	path.gsPath = L"Resources/Shaders/NumberShader/NumberGS.cso";
	m_number2DShader = std::make_unique<Number2DShader>(path);

	//// シェーダーのバイナリデータを読み込む
	//ResourceManager* resourceManager = ResourceManager::GetInstance();
	//BinaryFile VSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/NumberShader/NumberVS.cso");
	//BinaryFile PSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/NumberShader/NumberPS.cso");
	//BinaryFile GSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/NumberShader/NumberGS.cso");
	//// シェーダーを作成する
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
	//	VSData.GetData(), VSData.GetSize(), nullptr, m_numberVS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
	//	PSData.GetData(), PSData.GetSize(), nullptr, m_numberPS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
	//	GSData.GetData(), GSData.GetSize(), nullptr, m_numberGS.ReleaseAndGetAddressOf());

	////インプットレイアウトの作成
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
	//	&NUMBER_INPUT_LAYOUT[0],
	//	static_cast<UINT>(NUMBER_INPUT_LAYOUT.size()),
	//	VSData.GetData(),
	//	VSData.GetSize(),
	//	m_numberInputLayout.GetAddressOf());

	////	シェーダーにデータを渡すためのコンスタントバッファ生成
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(NumberConstBuffer);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_numberCBuffer);

}

void ShaderManager::LoadNumber3DShader()
{
	Shader::ShaderPath path;
	path.vsPath = L"Resources/Shaders/NumberShader/3D/Number3DVS.cso";
	path.psPath = L"Resources/Shaders/NumberShader/3D/Number3DPS.cso";
	path.gsPath = L"Resources/Shaders/NumberShader/3D/Number3DGS.cso";
	m_number3DShader = std::make_unique<ParticleShader>(path);


	//// シェーダーのバイナリデータを読み込む
	//ResourceManager* resourceManager = ResourceManager::GetInstance();
	//BinaryFile VSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/NumberShader/3D/Number3DVS.cso");
	//BinaryFile PSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/NumberShader/3D/Number3DPS.cso");
	//BinaryFile GSData = resourceManager->RequestBinaryFile(L"Resources/Shaders/NumberShader/3D/Number3DGS.cso");
	//// シェーダーを作成する
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
	//	VSData.GetData(), VSData.GetSize(), nullptr, m_number3DVS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
	//	PSData.GetData(), PSData.GetSize(), nullptr, m_number3DPS.ReleaseAndGetAddressOf());
	//m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
	//	GSData.GetData(), GSData.GetSize(), nullptr, m_number3DGS.ReleaseAndGetAddressOf());

	////インプットレイアウトの作成
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
	//	&PARTICLE_INPUT_LAYOUT[0],
	//	static_cast<UINT>(PARTICLE_INPUT_LAYOUT.size()),
	//	VSData.GetData(),
	//	VSData.GetSize(),
	//	m_number3DInputLayout.GetAddressOf());

	////	シェーダーにデータを渡すためのコンスタントバッファ生成
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(ParticleConstBuffer);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_number3DCBuffer);

}

void ShaderManager::SetModelShader()
{

	m_modelShader->StartShader();

	//ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();



	//LightBuffer lB;
	//lB.onLightCount = 0;
	//for (auto& light : m_lights) 
	//{
	//	if (light->IsOn())
	//	{
	//		lB.pointLights[lB.onLightCount] = light->GetLightData();
	//		lB.onLightCount++;
	//	}
	//}
	//context->UpdateSubresource(m_lBuffer.Get(), 0, NULL, &lB, 0, 0);


	//ID3D11Buffer* lb[1] = { m_lBuffer.Get()};

	//context->PSSetConstantBuffers(1, 1, lb);


	//context->PSSetShaderResources(1, 1, ResourceManager::GetInstance()->RequestTexture("toonmap.png"));

	////	シェーダーにバッファを渡す
	//ID3D11Buffer* cb[1] = { cBuffer };
	//// コンスタントバッファを設定
	//context->VSSetConstantBuffers(0, 1, cb);
	//context->PSSetConstantBuffers(0, 1, cb);
	//context->GSSetConstantBuffers(0, 1, cb);
	//// シェーダーを設定
	//context->VSSetShader(m_modelVS.Get(), nullptr, 0);
	//context->PSSetShader(m_modelPS.Get(), nullptr, 0);
	//context->GSSetShader(m_modelGS.Get(), nullptr, 0);

}

void ShaderManager::SetItemShader()
{
	m_itemShader->StartShader();
}

void ShaderManager::SetRockShader()
{
	m_rockShader->StartShader();
}

void ShaderManager::SetUIShader()
{
	m_uiShader->StartShader();

}

void ShaderManager::SetParticleShader()
{

	m_particleShader->StartShader(m_cameraCB);
	//ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	////	シェーダーにバッファを渡す
	//ID3D11Buffer* cb[1] = { cBuffer };

	//// コンスタントバッファを設定
	//context->VSSetConstantBuffers(0, 1, cb);
	//context->PSSetConstantBuffers(0, 1, cb);
	//context->GSSetConstantBuffers(0, 1, cb);
	//// シェーダーを設定
	//context->VSSetShader(m_ParticleVS.Get(), nullptr, 0);
	//context->PSSetShader(m_ParticlePS.Get(), nullptr, 0);
	//context->GSSetShader(m_ParticleGS.Get(), nullptr, 0);


}

void ShaderManager::SetFadeShader()
{
	m_fadeShader->StartShader();
	//ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	////	シェーダーにバッファを渡す
	//ID3D11Buffer* cb[1] = { cBuffer };

	//// コンスタントバッファを設定
	//context->VSSetConstantBuffers(0, 1, cb);
	//context->PSSetConstantBuffers(0, 1, cb);
	//context->GSSetConstantBuffers(0, 1, cb);
	//// シェーダーを設定
	//context->VSSetShader(m_fadeVS.Get(), nullptr, 0);
	//context->PSSetShader(m_fadePS.Get(), nullptr, 0);
	//context->GSSetShader(m_fadeGS.Get(), nullptr, 0);

}

void ShaderManager::SetOutlineShader()
{
	m_outlineShader->StartShader();
	//ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	////	シェーダーにバッファを渡す
	//ID3D11Buffer* cb[1] = { cBuffer };

	//// コンスタントバッファを設定
	//context->VSSetConstantBuffers(0, 1, cb);
	//context->PSSetConstantBuffers(0, 1, cb);
	//context->GSSetConstantBuffers(0, 1, cb);
	//// シェーダーを設定
	//context->VSSetShader(m_outlineVS.Get(), nullptr, 0);
	//context->PSSetShader(m_outlinePS.Get(), nullptr, 0);
	//context->GSSetShader(m_outlineGS.Get(), nullptr, 0);


}

void ShaderManager::SetNumber2DShader()
{
	m_number2DShader->StartShader();
	//ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	////	シェーダーにバッファを渡す
	//ID3D11Buffer* cb[1] = { cBuffer };

	//// コンスタントバッファを設定
	//context->VSSetConstantBuffers(0, 1, cb);
	//context->PSSetConstantBuffers(0, 1, cb);
	//context->GSSetConstantBuffers(0, 1, cb);
	//// シェーダーを設定
	//context->VSSetShader(m_numberVS.Get(), nullptr, 0);
	//context->PSSetShader(m_numberPS.Get(), nullptr, 0);
	//context->GSSetShader(m_numberGS.Get(), nullptr, 0);


}

void ShaderManager::SetNumber3DShader()
{
	m_number3DShader->StartShader(m_cameraCB);
	//ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	////	シェーダーにバッファを渡す
	//ID3D11Buffer* cb[1] = { cBuffer };

	//// コンスタントバッファを設定
	//context->VSSetConstantBuffers(0, 1, cb);
	//context->PSSetConstantBuffers(0, 1, cb);
	//context->GSSetConstantBuffers(0, 1, cb);
	//// シェーダーを設定
	//context->VSSetShader(m_number3DVS.Get(), nullptr, 0);
	//context->PSSetShader(m_number3DPS.Get(), nullptr, 0);
	//context->GSSetShader(m_number3DGS.Get(), nullptr, 0);

}
