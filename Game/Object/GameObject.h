/**
 * @file   GameObject.h
 *
 * @brief  �I�u�W�F�N�g�̊��N���X�Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"Game/Common/Graphics.h"
#include"Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
#include"Game/Interface/IState.h"
#include"Game/Shader.h"
#include"Game/Common/Collision/Shape.h"
#include"Game/Tag.h"
// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief GameObject
  */
class GameObject : public IObserver
{
// �N���X�萔�̐錾 -------------------------------------------------
public:

// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// �X�e�[�g
	IState* m_pCurrentState; 
	// �I�u�W�F�N�g�ԍ�
	static int s_objectNumber;
	// ���݂̃��b�Z�[�W
	Message m_currentMessage;
	// �I�u�W�F�N�g�̎��
	Tag::ObjectType m_objectType;
	// �O���t�B�b�N�X�N���X�̃|�C���^
	Graphics* m_graphics; 
	// �����蔻��p�̌`��
	Shape* m_shape; 



	//�e�N�X�`��
	ID3D11ShaderResourceView** m_texture;
	// ���f���f�[�^
	DirectX::Model* m_model;	
	// ���f���̈ʒu
	DirectX::SimpleMath::Vector3 m_position = { 0.0f,0.0f,0.0f };	
	// ���f���̉�]
	DirectX::SimpleMath::Quaternion m_quaternion = { 0.0f,0.0f,0.0f,1.0f }; // ���f���̃N�H�[�^�j�I����]
	// ���f���̊g�嗦
	DirectX::SimpleMath::Vector3 m_scale = { 1.0f,1.0f,1.0f };	

protected:
	// �e�I�u�W�F�N�g�ւ̃|�C���^
	GameObject* m_parent; 
	//�������W
	DirectX::SimpleMath::Vector3 m_initialPosition;
	//������]�p
	DirectX::SimpleMath::Quaternion m_initialAngle;
	// ���݂̈ʒu
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// ���݂̉�]�p
	DirectX::SimpleMath::Quaternion m_currentAngle;


// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	GameObject(Tag::ObjectType m_objectType, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// �f�X�g���N�^
	~GameObject();


// ����
public:
	virtual void Initialize();

	virtual void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)=0;

	virtual void Draw()=0;

	void Finalize();

	//�Փˉ�������
	void CollisionResponce(GameObject* other) {};
//�@�擾�E�ݒ�
public:
	
	//�e�N�X�`���̐ݒ�
	void SetTexture(ID3D11ShaderResourceView** tex);
	//�e�N�X�`���̎擾
	ID3D11ShaderResourceView** GetTexture();
	//���f���̐ݒ�
	void SetModel(DirectX::Model* model) { m_model = model; };
	//���W�̐ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	//��]�̐ݒ�
	void SetQuaternion(const DirectX::SimpleMath::Quaternion& q) { m_quaternion = q; }
	//�g�嗦�̐ݒ�
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }

	// �����蔻��p�̌`���ݒ�
	void SetShape(Shape* shape) { m_shape = shape; }
	// �����蔻��p�̌`����擾
	Shape* GetShape() const { return m_shape; }

	// ���f���f�[�^�̎擾
	DirectX::Model* GetModel() { return m_model; }
	// ���f���̈ʒu�̎擾
	DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }
	// ���f���̉�]�̎擾
	DirectX::SimpleMath::Quaternion& GetQuaternion() { return m_quaternion; }
	// ���f���̊g�嗦�̎擾
	DirectX::SimpleMath::Vector3& GetScale()  { return m_scale; }
	//
	DirectX::SimpleMath::Vector3& GetCurrentPosition() { return m_currentPosition; }
	DirectX::SimpleMath::Quaternion& GetCurrentQuaternion() { return m_currentAngle; }
	
	// �I�u�W�F�N�g�̎�ނ��擾����
	Tag::ObjectType GetObjectType() const; 
	// �O���t�B�b�N�X�N���X�̃|�C���^���擾����
	Graphics* GetGraphics() const; 

	// �I�u�W�F�N�g���J�E���g�A�b�v����
	static int CountUpNumber();
	// ��Ԃ��擾����
	IState* GetState() { return m_pCurrentState; }
	// ��Ԃ�ݒ肷��
	void SetState(IState* state) { m_pCurrentState = state; }
	// ���݂̏�Ԃ�ύX����
	void ChangeState(IState* state)
	{
		// �V�K�̏�ԑJ�ڑO�Ɏ���X�V���s��
		m_pCurrentState->PostUpdate();
		// �V�K�̏�Ԃ����݂̏�Ԃɐݒ肷��
		m_pCurrentState = state;
		// �V�K�̏�ԑJ�ڌ�Ɏ��O�X�V���s��
		m_pCurrentState->PreUpdate();
	}
	// ���b�Z�[�W���擾����
	Message GetCurrentMessage() const { return m_currentMessage; }
	// ���b�Z�[�W��ݒ肷��
	void SetCurrentMessage(Message currentMessage) { m_currentMessage = currentMessage; }

	virtual int GetObjectNumber()=0;

//�@��������
private:

};

