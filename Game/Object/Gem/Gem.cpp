/**
 * @file   Gem.cpp
 *
 * @brief  ��΂Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Gem.h"

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 */
Gem::Gem()
{
}
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] type  ��΂̎��
 * @param[in] value ��΂̌��ʒl
 * @param[in] discription ��΂̌��ʐ���
 */
Gem::Gem(Type type, int value, std::string discription)
	:m_ability{ type, value, discription }
{
}

Gem::Gem(GemAbility ability, GemImagePath image)
	:m_ability{ ability }
	, m_gemImage{ image }
{
}




/**
 * @brief �f�X�g���N�^
 */
Gem::~Gem()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Gem::Initialize()
{

}



/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Gem::Update()
{

}



/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Gem::Draw()
{

}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Gem::Finalize()
{

}


/**
 * @brief ��΂̐��\���擾
 *
 * @param[in] �Ȃ�
 *
 * @return ��΂̐��\
 */
Gem::GemAbility Gem::GetAbility() const
{
	return m_ability;
}

Gem::GemImagePath Gem::GetImagePath() const
{
	return m_gemImage;
}
