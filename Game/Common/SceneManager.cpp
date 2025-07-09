// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Common/SceneManager.h"
#include"Game//Common/Scene.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
SceneManager::SceneManager()
	: m_scenes{}
	, m_pCurrentScene{}
	, m_pRequestedScene{ nullptr }
	, m_sharedData{}
	, m_isStackScene{ false }
{
}



/**
 * @brief デストラクタ
 */
SceneManager::~SceneManager()
{

}

/**
 * @brief シーンの登録
 *
 * @param[in] sceneName　シーンの登録名
 * @param[in] scene　登録シーン
 *
 * @return なし
 */
void SceneManager::Register(const std::string& sceneName, std::unique_ptr<Scene> scene)
{
	m_scenes.emplace(sceneName, std::move(scene));
}

/**
 * @brief 更新処理
 *
 * @param[in] key		 　入力デバイス
 * @param[in] elapsedTime　フレーム経過時間
 *
 * @return なし
 */
void SceneManager::Update(float elapsedTime)
{
	//エスケープキーが押されたら終了
	if (Graphics::GetInstance()->GetKeyboardTracker()->IsKeyPressed(DirectX::Keyboard::Escape))
	{
		PostQuitMessage(0);
	}
	//シーン変更が必要かどうかをチェック
	if (m_pRequestedScene != nullptr)
	{
		//シーンをスタックするかどうか
		if (m_isStackScene)
		{
			StackScene();
		}
		//シーンを変更する
		ChangeScene();
	}

	if (m_pCurrentScene.empty())
	{
		return;
	}
	//現在のシーンを更新
	m_pCurrentScene.top()->Update(elapsedTime);
}

/**
 * @brief 描画処理
 *
 * @param[in] context　　デバイスコンテキスト
 * @param[in] states　　コモンステート
 * @param[in] proj　　  射影行列
 *
 * @return なし
 */
void SceneManager::Render()
{

	if (m_pCurrentScene.empty())
	{
		return;
	}
	//現在のシーンを描画
	//int count = m_pCurrentScene.size();
	//for (int i = 0; i < count; ++i)
	//{
	//	m_pCurrentScene.top()->Render(context, states, proj);
	//}
	m_pCurrentScene.top()->Render();

}

/**
 * @brief 開始シーンの設定
 *
 * @param[in] startSceneName　開始シーン名
 *
 * @return なし
 */
void SceneManager::SetStratScene(const std::string& startSceneName)
{
	if (m_scenes.count(startSceneName) == 0)
	{
		return;
	}
	m_pCurrentScene.push(m_scenes[startSceneName].get());
	m_pCurrentScene.top()->Initialize();
}

/**
 * @brief シーン変更の要求
 *
 * @param[in] requestSceneName　変更予定のシーン名
 *
 * @return なし
 */
void SceneManager::RequestSceneChange(const std::string& nextSceneName)
{
	//シーンの登録がされているか確認
	if (m_scenes.count(nextSceneName) == 0)
	{
		return;
	}
	m_pRequestedScene = m_scenes[nextSceneName].get();
}

/**
 * @brief スタックするシーンの要求(ポーズ画面など)
 *
 * @param[in] nextSceneName　変更予定のシーン名
 *
 * @return なし
 */
void SceneManager::RequestStackScene(const std::string& nextSceneName)
{
	//シーンの登録がされているか確認
	if (m_scenes.count(nextSceneName) == 0)
	{
		return;
	}
	m_pRequestedScene = m_scenes[nextSceneName].get();
	m_isStackScene = true;
}

/**
 * @brief シーンのポップ
 *
 * @param[in] なし
 *
 * @return なし
 */
void SceneManager::PopScene()
{
	if (m_pCurrentScene.empty())
	{
		return;
	}
	//シーンの終了処理
	m_pCurrentScene.top()->Finalize();
	m_pCurrentScene.pop();
	
}

/**
 * @brief 共有データの取得
 *
 * @param[in] key　取得したい共有データのキー
 *
 * @return キー共有データ
 */
std::string SceneManager::GetSharedData(const std::string& key) const
{
	if (m_sharedData.count(key) == 0)
	{
		return std::string{};
	}
	return m_sharedData.at(key);
}

/**
 * @brief 共有データの設定
 *
 * @param[in] key　  設定したい共有データのキー
 * @param[in] vlaue　設定したい共有データの値
 *
 * @return なし
 */
void SceneManager::SetSharedData(const std::string& key, const std::string& value)
{
	m_sharedData[key] = value;
}

/**
 * @brief シーンの変更
 *
 * @param[in] なし
 *
 * @return なし
 */
void SceneManager::ChangeScene()
{
	if (!m_pRequestedScene)
	{
		return;
	}

	if (!m_pCurrentScene.empty())
	{
		//スタックしているシーンの数を取得
		int count = m_pCurrentScene.size();
		for (int i = 0; i < count; ++i)
		{
			//シーンの終了処理
			m_pCurrentScene.top()->Finalize();
			m_pCurrentScene.pop();
		}	
	}
	//次シーン
	m_pCurrentScene.push(m_pRequestedScene);
	m_pCurrentScene.top()->Initialize();

	m_pRequestedScene = nullptr;
}

/**
 * @brief スタックするシーン(ポーズ画面など)
 *
 * @param[in] なし
 *
 * @return なし
 */
void SceneManager::StackScene()
{
	if (!m_pRequestedScene)
	{
		return;
	}
	if (!m_pCurrentScene.empty())
	{
		//シーンをスタックする
		m_pCurrentScene.push(m_pRequestedScene);
		m_pCurrentScene.top()->Initialize();
	}
	
	m_pRequestedScene = nullptr;
	m_isStackScene = false;
}



