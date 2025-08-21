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
#include"../Common/SceneManager.h"
#include"Game/UserResources.h"
#include"Game/Common/Sound.h"
#include"Game/Object/Camera.h"
#include"Game/Common/Collision/DisplayCollision.h"
#include"Game/Common/Collision/CollisionManager.h"
#include"Game/UI/GemSelect/GemSelect.h"
#include"Game/UI/Gauge/Gauge.h"
#include"Game/Object/Player/Player.h"
#include"Game/Object/Stage.h"
#include"../Object/Enemy/EnemyManager.h"
// �N���X�̐錾 ===============================================================
class ResourceManager;    ///< ���\�[�X�}�l�[�W��




// �N���X�̒�` ===============================================================
/**
 * @brief �Q�[���V�[��
 */
class GameScene : public Scene<UserResources>
{
// �N���X�萔�̐錾 -------------------------------------------------
public:


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// �V�X�e���֘A
	ResourceManager* m_pResourceManager;    ///< ���\�[�X�}�l�[�W��
	//�Փ˕\���I�u�W�F�N�g
	std::unique_ptr<Ito::DisplayCollision> m_displayCollision;
	CollisionManager* m_cM;
	// �I�u�W�F�N�g�֘A
	std::unique_ptr<EnemyManager> m_enemyManager; //<�G�Ǘ��I�u�W�F�N�g
	std::unique_ptr<Camera> m_camera;    ///< �J�����I�u�W�F�N�g
	std::unique_ptr<Player> m_player;    ///< �v���C���[�I�u�W�F�N�g
	std::unique_ptr<Stage> m_stage;    ///< �X�e�[�W�I�u�W�F�N�g

	std::unique_ptr<GemSelect> m_gemSelectUI;
	std::unique_ptr<Gauge> m_hpGauge;
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	GameScene();

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

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateDeviceDependentResources() override;

	// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateWindowSizeDependentResources() override;

	// �f�o�C�X���X�g�������ɌĂяo�����֐�
	void OnDeviceLost() override;

// �擾/�ݒ�
public:


// ��������
private:
	//�X�e�[�W�P�̏I������
	bool IsClear();
};
