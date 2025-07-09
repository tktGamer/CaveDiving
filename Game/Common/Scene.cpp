// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Scene.h"
#include"Game//Common/SceneManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pSceneManager　シーンマネージャ
 */
Scene::Scene(SceneManager* pSceneManager)
	:m_pSceneManager{pSceneManager}
{
	m_pGraphics = Graphics::GetInstance();
}

/**
 * @brief デストラクタ
 */
Scene::~Scene()
{
}


/**
 * @brief シーンの変更
 *
 * @param[in] nextSceneName　変更先のシーン
 * @param[in] isStack　シーンをスタックするかどうか
 *
 * @return なし
 */
void Scene::ChangeScene(const std::string& nextSceneName, bool isStack)
{
	if (isStack) 
	{
		//現在のシーンにスタックする
		m_pSceneManager->RequestStackScene(nextSceneName);
	}
	else
	{
		//現在のシーンから変更する
		m_pSceneManager->RequestSceneChange(nextSceneName);
	}
}


/**
 * @brief シーンのポップ
 *
 * @param[in] なし
 *
 * @return なし
 */
void Scene::PopScene()
{
	m_pSceneManager->PopScene();
}


/**
 * @brief 共有データの読み込み
 *
 * @param[in] key　   共有データのキー
 * @param[in] pValue　読み込み先
 *
 * @return なし
 */
void Scene::ReadSharedData(const std::string& key, int* pValue) const
{
	*pValue = std::stoi(m_pSceneManager->GetSharedData(key));
}

void Scene::ReadSharedData(const std::string& key, float* pValue) const
{
	*pValue = std::stof(m_pSceneManager->GetSharedData(key));
}

void Scene::ReadSharedData(const std::string& key, std::string* pValue) const
{
	*pValue = m_pSceneManager->GetSharedData(key);

}

void Scene::ReadSharedData(const std::string& key, bool* pValue) const
{
	*pValue = std::stoi(m_pSceneManager->GetSharedData(key));
}

/**
 * @brief 共有データの書き込み
 *
 * @param[in] key　   共有データのキー
 * @param[in] value　 書き込む値
 *
 * @return なし
 */
void Scene::WriteSharedData(const std::string& key, int value) const
{
	m_pSceneManager->SetSharedData(key, std::to_string(value));
}

void Scene::WtiteSharedData(const std::string& key, float value) const
{
	m_pSceneManager->SetSharedData(key, std::to_string(value));

}

void Scene::WriteSharedData(const std::string& key, std::string value) const
{
	m_pSceneManager->SetSharedData(key, value);

}

void Scene::WriteSharedData(const std::string& key, bool value) const
{
	m_pSceneManager->SetSharedData(key, std::to_string(value));
}

/**
 * @brief グラフィックスの取得
 *
 * @param[in] なし
 *
 * @return グラフィックス
 */
Graphics* Scene::GetGraphics() 
{
	return m_pGraphics;
}

