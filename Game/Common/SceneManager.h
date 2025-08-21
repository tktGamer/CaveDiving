#pragma once
// ヘッダファイルの読み込み ===================================================
#include<memory>
#include<string>
#include<unordered_map>
#include<stack>
#include<thread>
#include<mutex>
#include<future>
// クラスの宣言 ===============================================================
template <typename T>
class SceneManager;

// クラスの定義 ===============================================================
/**
  * @brief シーンの基底クラス
  */
template <typename T>
class Scene
{
private:

	// シーンマネージャーへのポインタ
	SceneManager<T>* m_sceneManager;

public:

	// コンストラクタ
	Scene() : m_sceneManager(nullptr) {}

	// デストラクタ
	virtual ~Scene() = default;

	// 初期化
	virtual void Initialize() = 0;

	// 更新
	virtual void Update(float elapsedTime) = 0;

	// 描画
	virtual void Render() = 0;

	// 終了処理
	virtual void Finalize() = 0;

	// デバイスに依存するリソースを作成する関数
	virtual void CreateDeviceDependentResources() {}

	// ウインドウサイズに依存するリソースを作成する関数
	virtual void CreateWindowSizeDependentResources() {}

	// デバイスロストした時に呼び出される関数
	virtual void OnDeviceLost() {}

public:

	// シーンマネージャー設定関数
	void SetSceneManager(SceneManager<T>* sceneManager) { m_sceneManager = sceneManager; }

	// シーンの切り替え関数
	template <typename U>
	void ChangeScene();

	template <typename U, typename V>
	void ChangeScene();


};


template <typename T>
// シーンマネージャークラス
class SceneManager
{
private:


	// 実行中のシーンへのポインタ
	std::unique_ptr<Scene<T>> m_scene;
	//std::stack<Scene<T>> m_pCurrentScene;//現在のシーン


	// 次のシーンへのポインタ
	std::unique_ptr<Scene<T>> m_nextScene;

	// ロード画面 
	std::unique_ptr<Scene<T>> m_loadingScreen;

	//スレッド＋共有変数（mutexによる排他制御）
	//std::thread m_loadingThread;
	//std::mutex m_loadingMutex;
	//bool m_isLoading;

	////スレッド＋共有変数（atomicによる排他制御）
	//std::thread m_loadingThread;
	//std::atomic<bool> m_isLoading;

	////スレッド＋mutexによるスレッドロック
	//std::thread m_loadingThread;
	//std::mutex m_loadingMutex;


	////スレッド＋共有変数（mutexによる排他制御）
	std::future<void> m_loadingFuture;

	// シーン削除関数
	void DeleteScene();

public:

	// コンストラクタ
	SceneManager(T* graphics=nullptr)
		: m_scene()
		, m_nextScene()
		, m_loadingScreen()
	{
	};

	// デストラクタ
	virtual ~SceneManager()
	{
		DeleteScene();

		// ロードスレッドが実行中なら終了を待つ
		/*if (m_loadingThread.joinable())
		{
			m_loadingThread.join();
		}*/
	};

	// 更新
	void Update(float elapsedTime);

	// 描画
	void Render();

	// デバイスに依存するリソースを作成する関数
	void CreateDeviceDependentResources();

	// ウインドウサイズに依存するリソースを作成する関数
	void CreateWindowSizeDependentResources();

	// デバイスロストした時に呼び出される関数
	virtual void OnDeviceLost();

	// シーンの設定関数
	template <typename U>
	void SetScene();

	// 次のシーンのリクエスト関数
	template <typename U>
	bool RequestSceneChange();

	template <typename U, typename V>
	bool RequestSceneChange();

	template <typename U>
	bool RequestSceneStack();

	//
	void PrepareNextScene(std::function<std::unique_ptr<Scene<T>>()> sceneFactory);

	bool IsLoading();

};

template<typename T>
template<typename U>
inline void Scene<T>::ChangeScene()
{
	m_sceneManager->RequestSceneChange<U>();

}

template <typename T>
template <typename U, typename V>
void Scene<T>::ChangeScene()
{
	m_sceneManager->RequestSceneChange<U, V>();
}



// シーンの設定関数
template <typename T>
template <typename U>
void SceneManager<T>::SetScene()
{
	assert(m_scene == nullptr);

	RequestSceneChange<U>();
}

// シーンの設定関数
template <typename T>
template <typename U>
bool SceneManager<T>::RequestSceneChange()
{
	if (!m_nextScene)
	{
		// シーンを生成
		PrepareNextScene([]() {return std::make_unique<U>(); });
		return true;
	}

	return false;
}

template <typename T>
template <typename U, typename V>
bool SceneManager<T>::RequestSceneChange()
{
	if (RequestSceneChange<U>())
	{
		// ロード画面を作成
		m_loadingScreen = std::make_unique<V>();
		m_loadingScreen->SetSceneManager(this);
		m_loadingScreen->Initialize();
	}

	return false;
}

template<typename T>
template<typename U>
inline bool SceneManager<T>::RequestSceneStack()
{
	return false;
}

// 更新関数
template <typename T>
void SceneManager<T>::Update(float elapsedTime)
{
	// ESCキーで終了
	auto kb = DirectX::Keyboard::Get().GetState();
	if (kb.Escape) PostQuitMessage(0);

	// シーンの切り替え処理
	if (!IsLoading() && m_nextScene)
	{
		DeleteScene();

		assert(m_scene == nullptr);

		// シーンを切り替え
		m_scene = std::move(m_nextScene);

		if (m_loadingScreen)
		{
			m_loadingScreen->Finalize();
			m_loadingScreen.reset();
		}
	}



	if (m_loadingScreen)
	{
		m_loadingScreen->Update(elapsedTime);
		return;
	}

	// シーンの更新
 	if (m_scene) m_scene->Update(elapsedTime);

}

// 描画関数
template <typename T>
void SceneManager<T>::Render()
{
	if (m_loadingScreen)
	{
		m_loadingScreen->Render();
		return;
	}

	// シーンの描画
	if (m_scene) m_scene->Render();

	auto debugFont = Graphics::GetInstance()->GetDebugFont();


}

// デバイスに依存するリソースを作成する関数
template <typename T>
void SceneManager<T>::CreateDeviceDependentResources()
{
	if (m_scene) m_scene->CreateDeviceDependentResources();
}

// ウインドウサイズに依存するリソースを作成する関数
template <typename T>
void SceneManager<T>::CreateWindowSizeDependentResources()
{
	if (m_scene) m_scene->CreateWindowSizeDependentResources();
}

// デバイスロストした時に呼び出される関数
template <typename T>
void SceneManager<T>::OnDeviceLost()
{
	if (m_scene) m_scene->OnDeviceLost();
}

// シーンの削除関数
template <typename T>
void SceneManager<T>::DeleteScene()
{
	if (m_scene)
	{
		m_scene->Finalize();

		m_scene.reset();
	}
}


template<typename T>
inline void SceneManager<T>::PrepareNextScene(std::function<std::unique_ptr<Scene<T>>()> sceneFactory)
{
	//if (m_loadingThread.joinable())
	//{
	//	m_loadingThread.join();
	//}
 //
	//m_isLoading = true;
	//m_loadingThread = std::thread
	//{
	//	[=]()
	//	{

	//		//m_loadingMutex.lock();
	//		m_nextScene = sceneFactory();
	//		m_nextScene->SetSceneManager(this);
	//		m_nextScene->Initialize();

	//		//m_isLoading = false;

	//		//m_loadingMutex.unlock();
	//	}
	//};

	m_loadingFuture = std::async(
		std::launch::async,
		[=]()
		{
			m_nextScene = sceneFactory();
			m_nextScene->SetSceneManager(this);
			m_nextScene->Initialize();
		}
	);
}

template<typename T>
inline bool SceneManager<T>::IsLoading()
{
	//m_loadingMutex.lock();
	//bool isLoading = m_isLoading;
	//m_loadingMutex.unlock();
	//return isLoading;

	//if (m_loadingMutex.try_lock())
	//{
	//	m_loadingMutex.unlock();
	//	return false;
	//}
	//return true;

	//return m_isLoading;

	std::future_status status = m_loadingFuture.wait_for(std::chrono::nanoseconds::zero());
	return (status != std::future_status::ready);
}
