/**
 * @file   TitleScene.h
 *
 * @brief  ���S�V�[���Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

// ���d�C���N���[�h�̖h�~ =====================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "Game/Common/Scene.h"
#include"Game/Object/Camera.h"

#include"math.h"

// �N���X�̐錾 ===============================================================
class ResourceManager;    ///< ���\�[�X�}�l�[�W��
class SceneManager;       ///< �V�[���}�l�[�W��




// �N���X�̒�` ===============================================================
/**
 * @brief ���S�V�[��
 */
class TitleScene : public Scene
{
// �N���X�萔�̐錾 -------------------------------------------------
public:



// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// �V�X�e���֘A
	ResourceManager* m_pResourceManager;    ///< ���\�[�X�}�l�[�W��
	float m_length;
	float m_angle;

	// �I�u�W�F�N�g�֘A
	std::unique_ptr<Camera> m_camera;    ///< �J�����I�u�W�F�N�g
	ID3D11ShaderResourceView* m_titleTexture;	///< �^�C�g���摜

	TKTLib::ModelParams m_caveModelParams;    ///< ���A���f���p�����[�^
	TKTLib::ModelParams m_demoPlayerModelParams;    ///< �v���C���[���f���p�����[�^

// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	TitleScene(SceneManager* pSceneManager);

	// �f�X�g���N�^
	~TitleScene();


// ����
public:
	// ����������
	void Initialize() override;

	// �X�V����
	void Update(float elapsedTime) override;

	// �`�揈��
	void Render() override;

	// �I������
	void Finalize() override;


// �擾/�ݒ�
public:


// ��������
private:


};
