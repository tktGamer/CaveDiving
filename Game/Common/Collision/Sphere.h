/**
 * @file   Sphere.h
 *
 * @brief  ���󓖂��蔻��Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ��@���n�M��
 *
 * @date   ���t�@2025/7/02
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "../Collision/Shape.h"
// �N���X�̐錾 ===============================================================
class Box;
// �N���X�̒�` ===============================================================
/**
  * @brief Sphere
  */
class Sphere :public Shape
{
// �N���X�萔�̐錾 -------------------------------------------------
public:


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	DirectX::SimpleMath::Vector3 m_center; ///< ���S���W
	float m_radius; ///< ���a
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Sphere(DirectX::SimpleMath::Vector3 center,float radius);

	// �f�X�g���N�^
	~Sphere();


// ����
public:

	bool Intersects(Shape* other) override;

//�@�擾�E�ݒ�
public:
	//�����蔻��`��N���X�ɒǉ�
	void AddDisplayCollision(Ito::DisplayCollision* dC);

	// ���S���W��ݒ肷��
	void SetCenter(const DirectX::SimpleMath::Vector3& center);
	// ���S���W���擾����
	DirectX::SimpleMath::Vector3 GetCenter() const;
	//���a��ݒ肷��
	void SetRadius(float radius);
	// ���a���擾����
	float GetRadius() const;
//�@��������
private:
	bool IntersectSphere(Sphere* other) const;
	bool IntersectBox(Box* other) const;
};

