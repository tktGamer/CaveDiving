/**
 * @file   GemManager.h
 *
 * @brief  ��΂̊Ǘ��Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"Game/Common/Graphics.h"
#include"Game/Object/Gem/Gem.h"
#include<fstream>
#include<sstream>
// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief GemManager
  */
class GemManager
{
// �N���X�萔�̐錾 -------------------------------------------------
public:
	//��΃f�[�^����
	struct GemData
	{
		int id=0;		// ���O
		std::string type;	// ���
		std::string item;   //��������
		int			effect=0;		// ����
		std::string description;	// ����
	};

// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	Graphics* m_graphics;	// �O���t�B�b�N�X�N���X�̃|�C���^

	std::vector<std::unique_ptr<Gem>> m_gemList;	// ��΂̃��X�g
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	GemManager();

	// �f�X�g���N�^
	~GemManager();


// ����
public:
	void Initialize();

	void Update();

	void Draw();

	void Finalize();

	
//�@�擾�E�ݒ�
public:
	//��΂̎�ނ����肷��
	Gem::Type DecisinType(const std::string& type);
//�@��������
private:
	// ��΃f�[�^�̓ǂݍ���
	void LoadGemData();
};

