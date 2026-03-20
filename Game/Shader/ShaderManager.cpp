/**
 * @file   ShaderManager.cpp
 *
 * @brief  シェーダー管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/02/10
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Common/ResourceManager.h"
#include"Game/Object/Light.h"
#include "ShaderManager.h"
// クラス定数の定義 ===========================================================

// ShaderManagerクラスのインスタンスへのユニークポインタ「シングルトン化する」
std::unique_ptr<ShaderManager> ShaderManager::s_shader = nullptr;
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
ShaderManager::ShaderManager()
{
	//シェーダー作成
	CreateShader();
}

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
	case ShaderManager::KeyUI:
		SetKeyUIShader();
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
	case ShaderManager::Animation2D:
		SetAnimation2DShader();
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
	LoadKeyUIShader();
	LoadParticleShader();
	LoadFadeShader();
	LoadOutlineShader();
	LoadNumber2DShader();
	LoadNumber3DShader();
	LoadAnimation2DShader();
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
	Shader::ShaderPath path{};
	//モデルのシェーダー
	path.vsPath = ResourcePath::SHADER::MODEL_VS;
	path.psPath = ResourcePath::SHADER::MODEL_PS;
	path.gsPath = ResourcePath::SHADER::MODEL_GS;
	m_modelShader = std::make_unique<ModelShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Model, m_modelShader.get()));
	//アイテムのシェーダー
	path.psPath = ResourcePath::SHADER::ITEM_MODEL_PS;
	m_itemShader = std::make_unique<ModelShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Item_Model, m_itemShader.get()));
	//光る石のシェーダー
	path.psPath = ResourcePath::SHADER::LUMI_ROCK_PS;
	m_rockShader = std::make_unique<ModelShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Rock_Model, m_rockShader.get()));
	//壁にシェーダー
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
	path.vsPath = ResourcePath::SHADER::UI_VS;
	path.psPath = ResourcePath::SHADER::UI_PS;
	path.gsPath = ResourcePath::SHADER::UI_GS;
	m_uiShader = std::make_unique<UIShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::UI, m_uiShader.get()));

}

/**
 * @brief KeyUIシェーダーの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::LoadKeyUIShader()
{
	Shader::ShaderPath path{};
	path.vsPath = ResourcePath::SHADER::KEY_UI_VS;
	path.psPath = ResourcePath::SHADER::KEY_UI_PS;
	path.gsPath = ResourcePath::SHADER::KEY_UI_GS;
	m_keyUIShader = std::make_unique<KeyUIShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::KeyUI, m_keyUIShader.get()));
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
	path.vsPath = ResourcePath::SHADER::PARTICLE_VS;
	path.psPath = ResourcePath::SHADER::PARTICLE_PS;
	path.gsPath = ResourcePath::SHADER::PARTICLE_GS;
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
	path.vsPath = ResourcePath::SHADER::FADE_VS;
	path.psPath = ResourcePath::SHADER::FADE_PS;
	path.gsPath = ResourcePath::SHADER::FADE_GS;
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
	path.vsPath = ResourcePath::SHADER::OUTLINE_VS;
	path.psPath = ResourcePath::SHADER::OUTLINE_PS;
	path.gsPath = ResourcePath::SHADER::OUTLINE_GS;
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
	path.vsPath = ResourcePath::SHADER::NUMBER2D_VS;
	path.psPath = ResourcePath::SHADER::NUMBER2D_PS;
	path.gsPath = ResourcePath::SHADER::NUMBER2D_GS;
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
	path.vsPath = ResourcePath::SHADER::NUMBER3D_VS;
	path.psPath = ResourcePath::SHADER::NUMBER3D_PS;
	path.gsPath = ResourcePath::SHADER::NUMBER3D_GS;
	m_number3DShader = std::make_unique<ParticleShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Number3D, m_number3DShader.get()));

}

/**
 * @brief 2Dアニメーションシェーダーの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
void ShaderManager::LoadAnimation2DShader()
{
	Shader::ShaderPath path;
	path.vsPath = ResourcePath::SHADER::ANIMATION2D_VS;
	path.psPath = ResourcePath::SHADER::ANIMATION2D_PS;
	path.gsPath = ResourcePath::SHADER::ANIMATION2D_GS;
	m_animation2DShader = std::make_unique<Animation2DShader>(path);
	m_shaderMap.insert(std::make_pair(ShaderType::Animation2D, m_animation2DShader.get()));

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

void ShaderManager::SetKeyUIShader()
{
	m_keyUIShader->StartShader();
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

void ShaderManager::SetAnimation2DShader()
{
	m_animation2DShader->StartShader();
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
