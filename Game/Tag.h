/**
 * @file   Tag.h
 *
 * @brief  �I�u�W�F�N�g�̎�ނɊւ���w�b�_�t�@�C��
 *
 * @author ����Җ� ���n�M��
 *
 * @date   ���t 2025/07/16
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

class Tag
{
public:
	// �I�u�W�F�N�g�̎��
	enum  ObjectType : int
	{
		None,	// �Ȃ�
		Player,	// �v���C���[
		Pikel,  // ��͂�
		Enemy,	// �G
		Item,	// �A�C�e��
		Light,
		Stage,
	};
};


