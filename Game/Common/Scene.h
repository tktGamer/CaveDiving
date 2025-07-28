#pragma once
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"pch.h"
#include <string>
#include"Game/Common/Graphics.h"
#include"Game/Shader.h"
// �N���X�̐錾 ===============================================================

class SceneManager;


// �N���X�̒�` ===============================================================
/**
  * @brief �V�[���̊��N���X
  */
class Scene
{
	// �N���X�萔�̐錾 -------------------------------------------------
public:



// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	SceneManager* m_pSceneManager;	///< �V�[���}�l�[�W��
	Graphics* m_pGraphics;	///< �O���t�B�b�N�X
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Scene(SceneManager* pSceneManager);

	// �f�X�g���N�^
	virtual ~Scene();


	// ����
public:
	// ����������
	virtual void Initialize() = 0;

	// �X�V����
	virtual void Update(float elapsedTime) = 0;

	// �`�揈��
	virtual void Render() = 0;

	// �I������
	virtual void Finalize() = 0;


// �擾/�ݒ�
public:


// ��������
protected:
	//�V�[���̕ύX
	void ChangeScene(const std::string& nextSceneName,bool isStack=false);
	//�V�[���̃|�b�v
	void PopScene();

	//���L�f�[�^�̓ǂݍ���
	void ReadSharedData(const std::string& key, int* pValue) const;
	void ReadSharedData(const std::string& key, float* pValue) const;
	void ReadSharedData(const std::string& key, std::string* pValue) const;
	void ReadSharedData(const std::string& key, bool* pValue) const;

	//���L�f�[�^�̓ǂݍ���
	void WriteSharedData(const std::string& key, int		 value) const;
	void WtiteSharedData(const std::string& key, float		 value) const;
	void WriteSharedData(const std::string& key, std::string value) const;
	void WriteSharedData(const std::string& key, bool value) const;

	//�O���t�B�b�N�X�̎擾
	Graphics* GetGraphics();
};

