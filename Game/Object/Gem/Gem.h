/**
 * @file   Gem.h
 *
 * @brief  ��΂Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================

// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief ���
  */
class Gem
{
// �N���X�萔�̐錾 -------------------------------------------------
public:
	enum class Type
	{
		HP = 0, //�̗�
		STR,    //�U����
		DEF,    //�h���
		UNIQUE, //����
	};

	struct GemAbility
	{
		Type m_type; ///< ��΂̎��
		int m_value; ///< ��΂̌��ʒl
		std::string m_discription; ///< ��΂̌��ʐ���

	};
// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	GemAbility m_ability; ///< ��΂̔\�͒l
	// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Gem();
	// ��΂̎�ނƌ��ʒl���w�肵�ď�����
	Gem(Type type,int value,std::string discription);
	Gem(GemAbility ability);

	// �f�X�g���N�^
	~Gem();


//����
public:
	void Initialize();

	void Update();

	void Draw();

	void Finalize();
//�擾�E�ݒ�
public:
	GemAbility GetAbility() const;
//��������
private:

};

