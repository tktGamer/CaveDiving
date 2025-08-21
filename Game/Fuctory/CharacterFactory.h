/**
 * @file   CharacterFactory.h
 *
 * @brief  �L�����N�^�[�̐����Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once
#ifndef CHARACTER_FACTORY_DEFINED
#define CHARACTER_FACTORY_DEFINED
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"../Object/Character.h"
// ���i�t�@�N�g���N���X���`����
class CharacterFactory 
{
public:
	// �u�v���C���[�v�𐶐�����
	static std::unique_ptr<Character> CreatePlayer(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// �u�v���C���[�̎�v�𐶐�����
	static std::unique_ptr<GameObject> CreateHand(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// �u�s�b�P���v�𐶐�����
	static std::unique_ptr<GameObject> CreatePikle(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// �u�R�E�����̓G�v�𐶐�����
	static std::unique_ptr<Character> CreateBat(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// �u�R�E�����̉H�v�𐶐�����
	static std::unique_ptr<GameObject> CreateBatWing(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// �u�C���C�g�v�𐶐�����
	static std::unique_ptr<Character> CreateTurretGun(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// �u�C���v���[�g�v�𐶐�����
	static std::unique_ptr<Character> CreateTurretPlate(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// �u�C���r�v�𐶐�����
	static std::unique_ptr<Character> CreateTurretFoot(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);
};

#endif		// CHARACTER_FACTORY_DEFINED