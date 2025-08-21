/**
 * @file   GemManager.cpp
 *
 * @brief  �w�w�w�w�Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "GemManager.h"


// �N���X�̐ÓI�����o�ϐ��̏�����
std::unique_ptr<GemManager> GemManager::s_gemManager = nullptr;

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
GemManager::GemManager()
	:m_graphics{Graphics::GetInstance()}
{

}



/**
 * @brief �f�X�g���N�^
 */
GemManager::~GemManager()
{

}

/**
 * @brief �C���X�^���X�̎擾
 *
 * @param[in] �Ȃ�
 *
 * @return �@��΃}�l�[�W���[�̃|�C���^
 */
GemManager* const GemManager::GetInstance()
{

	if (s_gemManager == nullptr)
	{
		//GemManager�I�u�W�F�N�g�𐶐����A���̃|�C���^��s_gemManager�Ɋi�[����
		s_gemManager.reset(new GemManager());
	}
	return s_gemManager.get();
}




/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void GemManager::Update()
{

}






/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void GemManager::Finalize()
{

}

Gem* GemManager::RandomSelection()
{
	if (m_gemList.empty()) 
	{
		return nullptr;
	}
	//�����_���ɕ�΂�I��
	//�v�f�̍ő吔
	int maxIndex = m_gemList.size() - 1;
	//�����_���ȗv�f
	int randomIndex = TKTLib::GetRand(0, maxIndex);

	return m_gemList[randomIndex].get();
}

/**
 * @brief ��΂̎�ނ����肷��
 *
 * @param[in] type ��΂̎��
 *
 * @return ��΂̎��
 */
Gem::Type GemManager::DecisinType(const std::string& type)
{
	if (type == "�̗�")
	{
		return Gem::Type::HP;
	}
	else if (type == "�U����")
	{
		return Gem::Type::STR;
	}
	else if (type == "�h���")
	{
		return Gem::Type::DEF;
	}
	return  Gem::Type::UNIQUE;
}

/**
 * @brief ��΃f�[�^�̓ǂݍ���
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void GemManager::LoadGemData()
{
	//�p�X�̐���
	std::string path = "Resources/Data/GemData.csv";
	//�t�@�C���̃I�[�v��
	std::ifstream ifs{ path };
	if (!ifs.is_open())
	{
		//�ǂݍ��ݎ��s
		return;
	}

	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	while (true)
	{
		GemData gemData;
		std::string line;

		ifs >> gemData.id; //ID
		ifs.ignore(); //�J���}��ǂݔ�΂�
		if (gemData.id <= 0)
		{
			//ID���s���ȏꍇ�͓ǂݔ�΂�
			ifs.close();
			return;
		}
		//��΂̎�ނ�ǂݍ���
		std::getline(ifs, line, ',');
		gemData.type = line;
		//�������ڂ�ǂݍ���
		std::getline(ifs, line, ',');
		gemData.item = line;
		//���ʂ�ǂݍ���
		ifs >> gemData.effect;
		ifs.ignore();

		//��������ǂݍ���
		std::getline(ifs, gemData.description, ','); 
		//�摜�p�X��ǂݍ���
		std::getline(ifs, gemData.gem, '\n'); 

		Gem::GemAbility ability = { DecisinType(gemData.item), gemData.effect, gemData.description };
		const wchar_t* gemPath = TKTLib::StringToWchar(gemData.gem);
		Gem::GemImagePath imagePath = { gemPath};
		//��΃f�[�^���쐬
		m_gemList.emplace_back(std::make_unique<Gem>(ability,imagePath));
	}
	ifs.close();
	return;


}
