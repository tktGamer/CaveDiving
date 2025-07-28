// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "ResourceManager.h"

using namespace DirectX;

// �N���X�̐ÓI�����o�ϐ��̏�����
std::unique_ptr<ResourceManager> ResourceManager::s_resourceManager = nullptr;

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
ResourceManager::ResourceManager()
	:m_texture{}
	,m_sounds{}
	,m_models{}
	, m_audioEngine{ nullptr }
{
}


/**
 * @brief �f�X�g���N�^
 */
ResourceManager::~ResourceManager()
{
	//�S���\�[�X�̍폜
	Clear();
}



/**
 * @brief �C���X�^���X�̎擾
 *
 * @param[in] �Ȃ�
 *
 * @return �@���\�[�X�}�l�[�W���[�̃|�C���^
 */
ResourceManager* const ResourceManager::GetInstance()
{
	
	if (s_resourceManager == nullptr)
	{
		//ResourceManager�I�u�W�F�N�g�𐶐����A���̃|�C���^��s_resourceManager�Ɋi�[����
		s_resourceManager.reset(new ResourceManager());
	}
	return s_resourceManager.get();
}

/**
 * @brief �摜�f�[�^�̗v��
 *
 * @param[in] filename �摜�t�@�C����
 *
 * @return �@�摜�f�[�^�̃n���h��
 */
ID3D11ShaderResourceView** ResourceManager::RequestTexture(wchar_t const* filename)
{
	std::string stringFilename = TKTLib::WcharToString(filename);
	//���o�^�̏ꍇ
	if (m_texture.count(stringFilename) == 0)
	{
		LoadTexture(stringFilename);

	}

	//�o�^���Ă���摜�f�[�^�̃n���h����ԋp
	return m_texture[stringFilename].GetAddressOf();
}
ID3D11ShaderResourceView** ResourceManager::RequestTexture(const std::string& filename)
{
	//���o�^�̏ꍇ
	if (m_texture.count(filename) == 0)
	{
		LoadTexture(filename);

	}

	////�o�^���Ă���摜�f�[�^�̃n���h����ԋp
	return m_texture[filename].GetAddressOf();

}

/**
 * @brief ���f�[�^�̗v��
 *
 * @param[in] filename ���t�@�C����
 *
 * @return ���f�[�^�̃|�C���^
 */
DirectX::SoundEffect* ResourceManager::RequestSound(wchar_t const* filename)
{
	std::string stringFilename = TKTLib::WcharToString(filename);
	//���o�^�̏ꍇ
	if (m_sounds.count(stringFilename) == 0)
	{
		//wav���t�@�C���̓ǂݍ���
		LoadSound(stringFilename);
	}

	//�o�^���Ă���摜�f�[�^�̃n���h����ԋp
	return m_sounds[stringFilename].get();
}
DirectX::SoundEffect* ResourceManager::RequestSound(const std::string& filename)
{
	//���o�^�̏ꍇ
	if (m_sounds.count(filename) == 0)
	{
		//wav���t�@�C���̓ǂݍ���
		LoadSound(filename);
	}

	//�o�^���Ă���摜�f�[�^�̃n���h����ԋp
	return m_sounds[filename].get();
}

/**
 * @brief ���f���f�[�^�̗v��
 *
 * @param[in] filename ���f���f�[�^�t�@�C����
 *
 * @return  ���f���f�[�^�̃|�C���^
 */
DirectX::Model* ResourceManager::RequestModel(wchar_t const* filename)
{
	std::string stringFilename = TKTLib::WcharToString(filename);

	//���o�^�̏ꍇ
	if (m_models.count(stringFilename) == 0) 
	{
		//sdkmesh���f���f�[�^�̓ǂݍ���
		LoadModel(stringFilename);
	}

	return m_models[stringFilename].get();
}

DirectX::Model* ResourceManager::RequestModel(const std::string& filename)
{
   // ���o�^�̏ꍇ
   if (m_models.count(filename) == 0) 
   {
	   //sdkmesh���f���f�[�^�̓ǂݍ���
	   LoadModel(filename);
   }

   return m_models[filename].get();
}


BinaryFile* ResourceManager::RequestBinaryFile(wchar_t const* filename)
{
	std::string stringFilename = TKTLib::WcharToString(filename);
	//���o�^�̏ꍇ
	if (m_binaryFile.count(stringFilename) == 0)
	{
		//�o�C�i���t�@�C���̓ǂݍ���
		std::unique_ptr<BinaryFile> binaryFile = std::make_unique<BinaryFile>();
		
		m_binaryFile.insert(std::make_pair(stringFilename, binaryFile->LoadFile(filename)));
	}
	return m_binaryFile[stringFilename].get();
}

/**
 * @brief �f�[�^�폜
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void ResourceManager::Clear()
{
	m_models.clear();
	m_sounds.clear();
	m_texture.clear();
}

/**
 * @brief sdkmesh���f���f�[�^�̓ǂݍ���
 *
 * @param[in] filename ���f���f�[�^�t�@�C����
 *
 * @return  �Ȃ�
 */
void ResourceManager::LoadModel(const std::string& filename)
{
	std::string fullPath = DEFAULT_MODELS_DIRECTORY + filename;
	// ��O�����Ή�
	try
	{
		ID3D11Device* device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
		DirectX::DX11::EffectFactory* fx = Graphics::GetInstance()->GetFX();
		fx->SetDirectory(L"Resources/Models");
		std::unique_ptr<Model> model = Model::CreateFromSDKMESH(device,TKTLib::StringToWchar(fullPath), *fx);
		m_models.insert(std::make_pair(filename, std::move(model)));
	}
	catch (const std::exception& e)
	{
		e;
		//�G���[���b�Z�[�W�̕\��
		TKTLib::ShowErrorMessage(filename, fullPath,TKTLib::ErrorType::FileNotFound);
	}
	catch (...)
	{

		MessageBox(nullptr, L"�\�����ʃG���[���������܂���", L"�G���[", MB_OK);
		PostQuitMessage(0);
	}

}

/**
 * @brief wav���f�[�^�̓ǂݍ���
 *
 * @param[in] filename ���f�[�^�t�@�C����
 *
 * @return  �Ȃ�
 */
void ResourceManager::LoadSound(const std::string& filename)
{
	std::string fullPath = DEFAULT_SOUND_DIRECTORY + filename;
	
	// ��O�����Ή�
	try
	{		
		std::unique_ptr<SoundEffect> soundEffect=std::make_unique<SoundEffect>(m_audioEngine,TKTLib::StringToWchar(fullPath));
		
		//�摜�f�[�^�̃n���h����o�^
		m_sounds.insert(std::make_pair(filename, std::move(soundEffect)));
	}
	catch (const std::exception& e)
	{
		//�G���[���b�Z�[�W�̕\��
		TKTLib::ShowErrorMessage(filename, fullPath, TKTLib::ErrorType::FileNotFound);
	}
	catch (...)
	{

		MessageBox(nullptr, L"�\�����ʃG���[���������܂���", L"�G���[", MB_OK);
		PostQuitMessage(0);
	}

}

/**
 * @brief �摜�f�[�^�̓ǂݍ���
 *
 * @param[in] filename �摜�f�[�^�t�@�C����
 *
 * @return  �Ȃ�
 */
void ResourceManager::LoadTexture(const std::string& filename)
{
	std::string fullPath = DEFAULT_TEXTURE_DIRECTORY + filename;
	// ��O�����Ή�
	try
	{
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureHandle;
		ID3D11Device* device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
		ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
		//�摜�f�[�^�ǂݍ���
		CreateWICTextureFromFile(
			device,
			context,
			TKTLib::StringToWchar(fullPath),
			nullptr,
			textureHandle.ReleaseAndGetAddressOf());
		
		if (!textureHandle)
		{
			throw std::runtime_error("�t�@�C����������Ȃ�����");
		}
		//�摜�f�[�^�̃n���h����o�^
		m_texture.insert(std::make_pair(filename, std::move(textureHandle)));
	}
	catch (const std::exception& e)
	{
		//�G���[���b�Z�[�W�̕\��
		TKTLib::ShowErrorMessage(filename, fullPath, TKTLib::ErrorType::FileNotFound);
	}
	catch (...)
	{
		MessageBox(nullptr, L"�\�����ʃG���[���������܂���", L"�G���[", MB_OK);
		PostQuitMessage(0);
	}
}

void ResourceManager::LoadResources()
{
}
