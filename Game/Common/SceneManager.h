#pragma once
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include<memory>
#include<string>
#include<unordered_map>
#include<stack>
#include<thread>
#include<mutex>
#include<future>
// �N���X�̐錾 ===============================================================
template <typename T>
class SceneManager;

// �N���X�̒�` ===============================================================
/**
  * @brief �V�[���̊��N���X
  */
template <typename T>
class Scene
{
private:

	// �V�[���}�l�[�W���[�ւ̃|�C���^
	SceneManager<T>* m_sceneManager;

public:

	// �R���X�g���N�^
	Scene() : m_sceneManager(nullptr) {}

	// �f�X�g���N�^
	virtual ~Scene() = default;

	// ������
	virtual void Initialize() = 0;

	// �X�V
	virtual void Update(float elapsedTime) = 0;

	// �`��
	virtual void Render() = 0;

	// �I������
	virtual void Finalize() = 0;

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	virtual void CreateDeviceDependentResources() {}

	// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
	virtual void CreateWindowSizeDependentResources() {}

	// �f�o�C�X���X�g�������ɌĂяo�����֐�
	virtual void OnDeviceLost() {}

public:

	// �V�[���}�l�[�W���[�ݒ�֐�
	void SetSceneManager(SceneManager<T>* sceneManager) { m_sceneManager = sceneManager; }

	// �V�[���̐؂�ւ��֐�
	template <typename U>
	void ChangeScene();

	template <typename U, typename V>
	void ChangeScene();


};


template <typename T>
// �V�[���}�l�[�W���[�N���X
class SceneManager
{
private:


	// ���s���̃V�[���ւ̃|�C���^
	std::unique_ptr<Scene<T>> m_scene;
	//std::stack<Scene<T>> m_pCurrentScene;//���݂̃V�[��


	// ���̃V�[���ւ̃|�C���^
	std::unique_ptr<Scene<T>> m_nextScene;

	// ���[�h��� 
	std::unique_ptr<Scene<T>> m_loadingScreen;

	//�X���b�h�{���L�ϐ��imutex�ɂ��r������j
	//std::thread m_loadingThread;
	//std::mutex m_loadingMutex;
	//bool m_isLoading;

	////�X���b�h�{���L�ϐ��iatomic�ɂ��r������j
	//std::thread m_loadingThread;
	//std::atomic<bool> m_isLoading;

	////�X���b�h�{mutex�ɂ��X���b�h���b�N
	//std::thread m_loadingThread;
	//std::mutex m_loadingMutex;


	////�X���b�h�{���L�ϐ��imutex�ɂ��r������j
	std::future<void> m_loadingFuture;

	// �V�[���폜�֐�
	void DeleteScene();

public:

	// �R���X�g���N�^
	SceneManager(T* graphics=nullptr)
		: m_scene()
		, m_nextScene()
		, m_loadingScreen()
	{
	};

	// �f�X�g���N�^
	virtual ~SceneManager()
	{
		DeleteScene();

		// ���[�h�X���b�h�����s���Ȃ�I����҂�
		/*if (m_loadingThread.joinable())
		{
			m_loadingThread.join();
		}*/
	};

	// �X�V
	void Update(float elapsedTime);

	// �`��
	void Render();

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateDeviceDependentResources();

	// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateWindowSizeDependentResources();

	// �f�o�C�X���X�g�������ɌĂяo�����֐�
	virtual void OnDeviceLost();

	// �V�[���̐ݒ�֐�
	template <typename U>
	void SetScene();

	// ���̃V�[���̃��N�G�X�g�֐�
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



// �V�[���̐ݒ�֐�
template <typename T>
template <typename U>
void SceneManager<T>::SetScene()
{
	assert(m_scene == nullptr);

	RequestSceneChange<U>();
}

// �V�[���̐ݒ�֐�
template <typename T>
template <typename U>
bool SceneManager<T>::RequestSceneChange()
{
	if (!m_nextScene)
	{
		// �V�[���𐶐�
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
		// ���[�h��ʂ��쐬
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

// �X�V�֐�
template <typename T>
void SceneManager<T>::Update(float elapsedTime)
{
	// ESC�L�[�ŏI��
	auto kb = DirectX::Keyboard::Get().GetState();
	if (kb.Escape) PostQuitMessage(0);

	// �V�[���̐؂�ւ�����
	if (!IsLoading() && m_nextScene)
	{
		DeleteScene();

		assert(m_scene == nullptr);

		// �V�[����؂�ւ�
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

	// �V�[���̍X�V
 	if (m_scene) m_scene->Update(elapsedTime);

}

// �`��֐�
template <typename T>
void SceneManager<T>::Render()
{
	if (m_loadingScreen)
	{
		m_loadingScreen->Render();
		return;
	}

	// �V�[���̕`��
	if (m_scene) m_scene->Render();

	auto debugFont = Graphics::GetInstance()->GetDebugFont();


}

// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
template <typename T>
void SceneManager<T>::CreateDeviceDependentResources()
{
	if (m_scene) m_scene->CreateDeviceDependentResources();
}

// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
template <typename T>
void SceneManager<T>::CreateWindowSizeDependentResources()
{
	if (m_scene) m_scene->CreateWindowSizeDependentResources();
}

// �f�o�C�X���X�g�������ɌĂяo�����֐�
template <typename T>
void SceneManager<T>::OnDeviceLost()
{
	if (m_scene) m_scene->OnDeviceLost();
}

// �V�[���̍폜�֐�
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
