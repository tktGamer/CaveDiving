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
		// ID
		int id=0;		
		// ���
		std::string type;	
		//��������
		std::string item;   
		// ����
		int			effect=0;		
		// ����
		std::string description;	

		//��΂̉摜�p�X
		std::string  gem;
		//���O�̉摜�p�X
		std::string  name;
		//�����̉摜�p�X
		std::string  explanation;

	};

// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// GemManager�N���X�̃C���X�^���X�ւ̃��j�[�N�|�C���^�u�V���O���g��������v
	static std::unique_ptr<GemManager> s_gemManager;

	Graphics* m_graphics;	// �O���t�B�b�N�X�N���X�̃|�C���^

	std::vector<std::unique_ptr<Gem>> m_gemList;	// ��΂̃��X�g
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	GemManager();
	// �C���X�^���X���R�s�[���邱�Ƃ��֎~����
	void operator=(const GemManager&) = delete;
	// �C���X�^���X�����[�u���邱�Ƃ��֎~����
	GemManager& operator= (GemManager&&) = delete;
	// �R�s�[�R���X�g���N�^�͋֎~����
	GemManager(const GemManager&) = delete;
	// ���[�u�R���X�g���N�^�͋֎~����
	GemManager(GemManager&&) = delete;


	// �f�X�g���N�^
	~GemManager();


// ����
public:
	// GemManager�N���X�̃C���X�^���X���擾����
	static GemManager* const GetInstance();

	// ��΃f�[�^�̓ǂݍ���
	void LoadGemData();

	void Update();


	void Finalize();

	//�����_���ɕ�΂�I������
	Gem* RandomSelection();
//�@�擾�E�ݒ�
public:
	//��΂̎�ނ����肷��
	Gem::Type DecisinType(const std::string& type);
//�@��������
private:
};

