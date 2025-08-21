/**
 * @file   Box.h
 *
 * @brief  AABB�����蔻��Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ��@���n�M��
 *
 * @date   ���t�@2025/07/02
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "../Collision/Shape.h"
// �N���X�̐錾 ===============================================================
class Sphere;
// �N���X�̒�` ===============================================================
/**
  * @brief AABB
  */
class Box :public Shape
{
// �N���X�萔�̐錾 -------------------------------------------------
public:


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// ���S���W
	DirectX::SimpleMath::Vector3 m_center; 
	// �����̃T�C�Y
	DirectX::SimpleMath::Vector3 m_halfSize; 

// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Box(DirectX::SimpleMath::Vector3 center,DirectX::SimpleMath::Vector3 halfSize);

	// �f�X�g���N�^
	~Box();


// ����
public:
	//�����蔻��
	bool Intersects(Shape* other) override;

//�@�擾�E�ݒ�
public:
	//�����蔻��`��N���X�ɒǉ�
	void AddDisplayCollision(Ito::DisplayCollision* dC);

	// ���S���W��ݒ肷��
	void SetCenter(const DirectX::SimpleMath::Vector3& center);
	// ���S���W���擾����
	DirectX::SimpleMath::Vector3 GetCenter() const;
	// �����̃T�C�Y��ݒ肷��
	void SetHalfSize(const DirectX::SimpleMath::Vector3& halfSize);
	// �����̃T�C�Y���擾����
	DirectX::SimpleMath::Vector3 GetHalfSize() const;
//�@��������
private:
	//AABB�Ƃ̓����蔻��
	bool IntersectBox(Box* other);
	//���Ƃ̓����蔻��
	bool IntersectSphere(Sphere* other) const;

};

