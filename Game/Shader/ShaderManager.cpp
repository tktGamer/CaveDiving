/**
 * @file   ShaderManager.cpp
 *
 * @brief  シェーダー管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/19
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Common/ResourceManager.h"
#include"Game/Object/Light.h"
#include "ShaderManager.h"
// クラス定数の定義 ===========================================================

std::unique_ptr<ShaderManager> ShaderManager::s_shader = nullptr;

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
	case ShaderManager::Wall_Model:
		SetWallShader();
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

	//指定されたシェーダーを開始する
	//m_shaderMap[type]->StartShader();

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
	//switch (type)
	//{
	//case ShaderManager::Model:
	//	return m_modelShader->GetInputLayout();
	//	break;
	//case ShaderManager::Item_Model:
	//	return m_itemShader->GetInputLayout();
	//	break;
	//case ShaderManager::Rock_Model:
	//	return m_rockShader->GetInputLayout();
	//	break;
	//case ShaderManager::UI:
	//	return m_uiShader->GetInputLayout();
	//	break;
	//case ShaderManager::Number2D:
	//	return m_number2DShader->GetInputLayout();
	//	break;
	//case ShaderManager::Number3D:
	//	return m_number3DShader->GetInputLayout();
	//	break;
	//case ShaderManager::Particle:
	//	return m_particleShader->GetInputLayout();
	//	break;
	//case ShaderManager::Fade:
	//	return m_fadeShader->GetInputLayout();
	//	break;
	//case ShaderManager::Outline:
	//	return m_outlineShader->GetInputLayout();
	//	break;
	//default:
	//	break;
	//}
	//return nullptr;
	//指定されたシェーダーのインプットレイアウトをかえす
	return m_shaderMap[type]->GetInputLayout();

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
	//switch (type)
	//{
	//case ShaderManager::Model:
	//	return m_modelShader->GetConstantBuffer();
	//	break;
	//case ShaderManager::Item_Model:
	//	return m_itemShader->GetConstantBuffer();
	//	break;
	//case ShaderManager::Rock_Model:
	//	return m_rockShader->GetConstantBuffer();
	//	break;
	//case ShaderManager::UI:
	//	return m_uiShader->GetConstantBuffer();
	//	break;
	//case ShaderManager::Number2D:
	//	return m_number2DShader->GetConstantBuffer();
	//	break;
	//case ShaderManager::Number3D:
	//	return m_number3DShader->GetConstantBuffer();
	//	break;
	//case ShaderManager::Particle:
	//	return m_particleShader->GetConstantBuffer();
	//	break;
	//case ShaderManager::Fade:
	//	return m_fadeShader->GetConstantBuffer();
	//	break;
	//case ShaderManager::Outline:
	//	return m_outlineShader->GetConstantBuffer();
	//default:
	//	break;
	//}
	//return nullptr;
	
	//指定されたシェーダーのコンスタントバッファをかえす
	return m_shaderMap[type]->GetConstantBuffer();
}


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
	path.vsPath = ResourcePath::SHADER::MODEL_VS;
	path.psPath = ResourcePath::SHADER::MODEL_PS;
	path.gsPath = ResourcePath::SHADER::MODEL_GS;
	m_modelShader = std::make_unique<ModelShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Model, m_modelShader.get()));

	path.psPath = ResourcePath::SHADER::ITEM_MODEL_PS;
	m_itemShader = std::make_unique<ModelShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Item_Model, m_itemShader.get()));

	path.psPath = ResourcePath::SHADER::LUMI_ROCK_PS;
	m_rockShader = std::make_unique<ModelShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Rock_Model, m_rockShader.get()));

	path.psPath = ResourcePath::SHADER::WALL_MODEL_PS;
	m_wallShader = std::make_unique<WallShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Wall_Model, m_wallShader.get()));

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
	m_shaderMap.insert(std::make_pair(ShaderType::UI, m_uiShader.get()));

}

/**
 * @brief パーティクルシェーダーの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::LoadParticleShader()
{
	Shader::ShaderPath path;
	path.vsPath = L"Resources/Shaders/ParticleShader/ParticleVS.cso";
	path.psPath = L"Resources/Shaders/ParticleShader/ParticlePS.cso";
	path.gsPath = L"Resources/Shaders/ParticleShader/ParticleGS.cso";
	m_particleShader = std::make_unique<ParticleShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Particle, m_particleShader.get()));

}


/**
 * @brief フェードシェーダーの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::LoadFadeShader()
{
	Shader::ShaderPath path;
	path.vsPath = L"Resources/Shaders/FadeShader/FadeVS.cso";
	path.psPath = L"Resources/Shaders/FadeShader/FadePS.cso";
	path.gsPath = L"Resources/Shaders/FadeShader/FadeGS.cso";
	m_fadeShader = std::make_unique<FadeShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Fade, m_fadeShader.get()));

}

/**
 * @brief アウトラインシェーダーの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::LoadOutlineShader()
{
	Shader::ShaderPath path;
	path.vsPath = L"Resources/Shaders/OutlineShader/OutlineVS.cso";
	path.psPath = L"Resources/Shaders/OutlineShader/OutlinePS.cso";
	path.gsPath = L"Resources/Shaders/OutlineShader/OutlineGS.cso";
	m_outlineShader = std::make_unique<OutlineShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Outline, m_outlineShader.get()));

}

/**
 * @brief 数字UIシェーダーの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::LoadNumber2DShader()
{
	Shader::ShaderPath path;
	path.vsPath = L"Resources/Shaders/NumberShader/NumberVS.cso";
	path.psPath = L"Resources/Shaders/NumberShader/NumberPS.cso";
	path.gsPath = L"Resources/Shaders/NumberShader/NumberGS.cso";
	m_number2DShader = std::make_unique<Number2DShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Number2D, m_number2DShader.get()));

}

/**
 * @brief 3D空間上の数字シェーダーの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::LoadNumber3DShader()
{
	Shader::ShaderPath path;
	path.vsPath = L"Resources/Shaders/NumberShader/3D/Number3DVS.cso";
	path.psPath = L"Resources/Shaders/NumberShader/3D/Number3DPS.cso";
	path.gsPath = L"Resources/Shaders/NumberShader/3D/Number3DGS.cso";
	m_number3DShader = std::make_unique<ParticleShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Number3D, m_number3DShader.get()));

}

/**
 * @brief モデルシェーダーの開始
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::SetModelShader()
{

	m_modelShader->StartShader();

}


/**
 * @brief アイテム用モデルシェーダーの開始
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::SetItemShader()
{
	m_itemShader->StartShader();
}

/**
 * @brief 光る石用モデルシェーダーの開始
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::SetRockShader()
{
	m_rockShader->StartShader();
}


/**
 * @brief 壁用モデルシェーダーの開始
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::SetWallShader()
{
	m_wallShader->StartShader(m_cameraToPlayerCB);
}

/**
 * @brief UIシェーダーの開始
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::SetUIShader()
{
	m_uiShader->StartShader();
}

/**
 * @brief パーティクルシェーダーの開始
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::SetParticleShader()
{
	m_particleShader->StartShader(m_cameraCB);
}

/**
 * @brief フェードシェーダーの開始
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::SetFadeShader()
{
	m_fadeShader->StartShader();
}

/**
 * @brief アウトラインシェーダーの開始
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::SetOutlineShader()
{
	m_outlineShader->StartShader();
}

/**
 * @brief 数字UIシェーダーの開始
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::SetNumber2DShader()
{
	m_number2DShader->StartShader();
}

/**
 * @brief 3D空間上の数字シェーダーの開始
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::SetNumber3DShader()
{
	m_number3DShader->StartShader(m_cameraCB);
}


/**
 * @brief カメラとプレイヤーの位置情報バッファの設定
 *
 * @param[in] cameraToPlayerCB カメラとプレイヤーの位置情報
 *
 * @return なし
 */
void ShaderManager::SetCameraToPlayerCB(const WallShader::CameraToPlayerCB& cameraToPlayerCB)
{
	m_cameraToPlayerCB = cameraToPlayerCB;
}

/**
 * @brief カメラのコンスタントバッファの設定
 *
 * @param[in] cameraCB カメラの情報
 *
 * @return なし
 */
void ShaderManager::SetCameraCB(const ParticleShader::CameraCB& cameraCB)
{
	m_cameraCB = cameraCB;
}
