#pragma once
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include<memory>
#include<string>
#include<unordered_map>
#include<stack>
// �N���X�̐錾 ===============================================================

class Scene;
class ResourceManager;

class SceneManager
{
	//�G�C���A�X�錾 ----------------------------------------------------
private:
	using SceneCollection = std::unordered_map<std::string, std::unique_ptr<Scene>>;
	using SharedData = std::unordered_map<std::string, std::string>;
	// �N���X�萔�̐錾 -------------------------------------------------
public:



	// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	SceneCollection m_scenes;//�V�[���Q

	std::stack<Scene*> m_pCurrentScene;//���݂̃V�[��
	Scene* m_pRequestedScene;//�ύX�v���̂������V�[��
	bool m_isStackScene;//�X�^�b�N����V�[�����ǂ���
	SharedData m_sharedData;//���L�f�[�^


// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	SceneManager();

	// �f�X�g���N�^
	~SceneManager();


// ����
public:
	// �V�[���̓o�^
	void Register(const std::string& sceneName, std::unique_ptr<Scene> scene);

	// �X�V����
	void Update(float elapsedTime);

	// �`�揈��
	void Render();

	// �J�n�V�[���̐ݒ�
	void SetStratScene(const std::string& startSceneName);

	// �V�[���ύX�̗v��
	void RequestSceneChange(const std::string& nextSceneName);

	//�X�^�b�N����V�[���̗v��(�|�[�Y��ʂȂ�)
	void RequestStackScene(const std::string& nextSceneName);

	//���݂̃V�[�����v�b�V��
	void PopScene();
// �擾/�ݒ�
public:
	//���L�f�[�^�̎擾
	std::string GetSharedData(const std::string& key) const;

	//���L�f�[�^�̐ݒ�
	void SetSharedData(const std::string& key, const std::string& value);

// ��������
private:
	//�V�[���̕ύX
	void ChangeScene();

	//�V�[���̃X�^�b�N
	void StackScene();
};

