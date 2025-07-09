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
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void GemManager::Initialize()
{
	LoadGemData();
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
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void GemManager::Draw()
{
	ID3D11DeviceContext*		 context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = m_graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = m_graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = m_graphics->GetProjectionMatrix();
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

		std::getline(ifs, gemData.description, '\n'); //��������ǂݍ���

		//��΃f�[�^���쐬
		m_gemList.emplace_back(std::make_unique<Gem>(DecisinType(gemData.item), gemData.effect, gemData.description));
	}
	ifs.close();
	return;


}
