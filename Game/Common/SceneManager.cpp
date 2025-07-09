// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Game/Common/SceneManager.h"
#include"Game//Common/Scene.h"
// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
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
 * @brief �f�X�g���N�^
 */
SceneManager::~SceneManager()
{

}

/**
 * @brief �V�[���̓o�^
 *
 * @param[in] sceneName�@�V�[���̓o�^��
 * @param[in] scene�@�o�^�V�[��
 *
 * @return �Ȃ�
 */
void SceneManager::Register(const std::string& sceneName, std::unique_ptr<Scene> scene)
{
	m_scenes.emplace(sceneName, std::move(scene));
}

/**
 * @brief �X�V����
 *
 * @param[in] key		 �@���̓f�o�C�X
 * @param[in] elapsedTime�@�t���[���o�ߎ���
 *
 * @return �Ȃ�
 */
void SceneManager::Update(float elapsedTime)
{
	//�G�X�P�[�v�L�[�������ꂽ��I��
	if (Graphics::GetInstance()->GetKeyboardTracker()->IsKeyPressed(DirectX::Keyboard::Escape))
	{
		PostQuitMessage(0);
	}
	//�V�[���ύX���K�v���ǂ������`�F�b�N
	if (m_pRequestedScene != nullptr)
	{
		//�V�[�����X�^�b�N���邩�ǂ���
		if (m_isStackScene)
		{
			StackScene();
		}
		//�V�[����ύX����
		ChangeScene();
	}

	if (m_pCurrentScene.empty())
	{
		return;
	}
	//���݂̃V�[�����X�V
	m_pCurrentScene.top()->Update(elapsedTime);
}

/**
 * @brief �`�揈��
 *
 * @param[in] context�@�@�f�o�C�X�R���e�L�X�g
 * @param[in] states�@�@�R�����X�e�[�g
 * @param[in] proj�@�@  �ˉe�s��
 *
 * @return �Ȃ�
 */
void SceneManager::Render()
{

	if (m_pCurrentScene.empty())
	{
		return;
	}
	//���݂̃V�[����`��
	//int count = m_pCurrentScene.size();
	//for (int i = 0; i < count; ++i)
	//{
	//	m_pCurrentScene.top()->Render(context, states, proj);
	//}
	m_pCurrentScene.top()->Render();

}

/**
 * @brief �J�n�V�[���̐ݒ�
 *
 * @param[in] startSceneName�@�J�n�V�[����
 *
 * @return �Ȃ�
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
 * @brief �V�[���ύX�̗v��
 *
 * @param[in] requestSceneName�@�ύX�\��̃V�[����
 *
 * @return �Ȃ�
 */
void SceneManager::RequestSceneChange(const std::string& nextSceneName)
{
	//�V�[���̓o�^������Ă��邩�m�F
	if (m_scenes.count(nextSceneName) == 0)
	{
		return;
	}
	m_pRequestedScene = m_scenes[nextSceneName].get();
}

/**
 * @brief �X�^�b�N����V�[���̗v��(�|�[�Y��ʂȂ�)
 *
 * @param[in] nextSceneName�@�ύX�\��̃V�[����
 *
 * @return �Ȃ�
 */
void SceneManager::RequestStackScene(const std::string& nextSceneName)
{
	//�V�[���̓o�^������Ă��邩�m�F
	if (m_scenes.count(nextSceneName) == 0)
	{
		return;
	}
	m_pRequestedScene = m_scenes[nextSceneName].get();
	m_isStackScene = true;
}

/**
 * @brief �V�[���̃|�b�v
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void SceneManager::PopScene()
{
	if (m_pCurrentScene.empty())
	{
		return;
	}
	//�V�[���̏I������
	m_pCurrentScene.top()->Finalize();
	m_pCurrentScene.pop();
	
}

/**
 * @brief ���L�f�[�^�̎擾
 *
 * @param[in] key�@�擾���������L�f�[�^�̃L�[
 *
 * @return �L�[���L�f�[�^
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
 * @brief ���L�f�[�^�̐ݒ�
 *
 * @param[in] key�@  �ݒ肵�������L�f�[�^�̃L�[
 * @param[in] vlaue�@�ݒ肵�������L�f�[�^�̒l
 *
 * @return �Ȃ�
 */
void SceneManager::SetSharedData(const std::string& key, const std::string& value)
{
	m_sharedData[key] = value;
}

/**
 * @brief �V�[���̕ύX
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void SceneManager::ChangeScene()
{
	if (!m_pRequestedScene)
	{
		return;
	}

	if (!m_pCurrentScene.empty())
	{
		//�X�^�b�N���Ă���V�[���̐����擾
		int count = m_pCurrentScene.size();
		for (int i = 0; i < count; ++i)
		{
			//�V�[���̏I������
			m_pCurrentScene.top()->Finalize();
			m_pCurrentScene.pop();
		}	
	}
	//���V�[��
	m_pCurrentScene.push(m_pRequestedScene);
	m_pCurrentScene.top()->Initialize();

	m_pRequestedScene = nullptr;
}

/**
 * @brief �X�^�b�N����V�[��(�|�[�Y��ʂȂ�)
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void SceneManager::StackScene()
{
	if (!m_pRequestedScene)
	{
		return;
	}
	if (!m_pCurrentScene.empty())
	{
		//�V�[�����X�^�b�N����
		m_pCurrentScene.push(m_pRequestedScene);
		m_pCurrentScene.top()->Initialize();
	}
	
	m_pRequestedScene = nullptr;
	m_isStackScene = false;
}



