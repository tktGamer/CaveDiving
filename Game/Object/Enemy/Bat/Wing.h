/**
 * @file   Wing.h
 *
 * @brief  �H�Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"Game/Object/GameObject.h"

// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief Wing
  */
class Wing : public GameObject
{
// �N���X�萔�̐錾 -------------------------------------------------
public:


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	Graphics* m_graphics;	// �O���t�B�b�N�X�N���X�̃|�C���^
	// �I�u�W�F�N�g�ԍ�
	int m_objectNumber;

	DirectX::SimpleMath::Matrix m_world;


	DirectX::SimpleMath::Quaternion m_motionAngle;
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Wing(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// �f�X�g���N�^
	~Wing();


// ����
public:
	void Initialize() override;

	void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

	void Finalize();

	// ���b�Z�[�W���擾����
	void OnMessegeAccepted(Message::MessageID messageID);
	//�@�擾�E�ݒ�
public:
	int GetObjectNumber() override;

	DirectX::SimpleMath::Quaternion GetMotionAngle();
	void SetMotionAngle(DirectX::SimpleMath::Quaternion angle);
//�@��������
private:

};

