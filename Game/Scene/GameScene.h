/**
 * @file   GameScene.h
 *
 * @brief  �Q�[���V�[���Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

// ���d�C���N���[�h�̖h�~ =====================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "Game/Common/Scene.h"
#include"Game/Common/Sound.h"
#include"Game/Object/Camera.h"
#include"Game/Object/Player/Player.h"
#include"Game/Object/Stage.h"
#include"Game/Common/Collision/DisplayCollision.h"

// �N���X�̐錾 ===============================================================
class ResourceManager;    ///< ���\�[�X�}�l�[�W��
class SceneManager;       ///< �V�[���}�l�[�W��




// �N���X�̒�` ===============================================================
/**
 * @brief �Q�[���V�[��
 */
class GameScene : public Scene
{
// �N���X�萔�̐錾 -------------------------------------------------
public:


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// �V�X�e���֘A
	ResourceManager* m_pResourceManager;    ///< ���\�[�X�}�l�[�W��
	//�Փ˕\���I�u�W�F�N�g
	std::unique_ptr<Ito::DisplayCollision> m_displayCollision;

	// �I�u�W�F�N�g�֘A
	std::unique_ptr<Camera> m_camera;    ///< �J�����I�u�W�F�N�g
	std::unique_ptr<Player> m_player;    ///< �v���C���[�I�u�W�F�N�g
	std::unique_ptr<Stage> m_stage;    ///< �X�e�[�W�I�u�W�F�N�g
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	GameScene(SceneManager* pSceneManager);

	// �f�X�g���N�^
	~GameScene();


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
