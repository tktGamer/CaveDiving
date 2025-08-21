/**
 * @file   LoadScene.h
 *
 * @brief  ���[�h�V�[���Ɋւ���w�b�_�t�@�C��
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

#include"Game/Object/Camera.h"

#include"math.h"

// �N���X�̐錾 ===============================================================
class ResourceManager;    ///< ���\�[�X�}�l�[�W��





// �N���X�̒�` ===============================================================
/**
 * @brief ���S�V�[��
 */
class LoadScene : public  Scene<UserResources>
{
// �N���X�萔�̐錾 -------------------------------------------------
public:



// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// �V�X�e���֘A
	ResourceManager* m_pResourceManager;    ///< ���\�[�X�}�l�[�W��

	// �I�u�W�F�N�g�֘A
	std::unique_ptr<Camera> m_camera;    ///< �J�����I�u�W�F�N�g
	ID3D11ShaderResourceView* m_nowloadingTexture;	///< NowLoading�摜
	ID3D11ShaderResourceView* m_backTexture;	///< �w�i�摜

	RECT m_nowloadingRect;	///< NowLoading�摜�̋�`
	//���Ԍv��
	float m_time;
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	LoadScene();

	// �f�X�g���N�^
	~LoadScene();


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


};
