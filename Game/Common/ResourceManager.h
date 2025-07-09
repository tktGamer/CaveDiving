#pragma once
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include<unordered_map>
#include<string>
#include"Game/Common/Graphics.h"
#include"Game/Common/BinaryFile.h"
// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief ���\�[�X�̊Ǘ�
  */
class ResourceManager
{
//�G�C���A�X�錾
private:                                        //�t�@�C�����@�n���h��
	using TextureResource    = std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>;
	using SoundResouce		 = std::unordered_map<std::string, std::unique_ptr<DirectX::SoundEffect>>;
	using ModelResouce		 = std::unordered_map<std::string, std::unique_ptr<DirectX::Model>>;
	using BinaryResouce		 = std::unordered_map<std::string, std::unique_ptr<BinaryFile>>;
// �N���X�萔�̐錾 -------------------------------------------------
public:
	static constexpr  char const* DEFAULT_TEXTURE_DIRECTORY		= "Resources/Textures/";
	static constexpr  char const* DEFAULT_SOUND_DIRECTORY		= "Resources/Sounds/";
	static constexpr  char const* DEFAULT_MODELS_DIRECTORY		= "Resources/Models/";


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// ResourceManager�N���X�̃C���X�^���X�ւ̃��j�[�N�|�C���^�u�V���O���g��������v
	static std::unique_ptr<ResourceManager> s_resourceManager;

	DirectX::AudioEngine* m_audioEngine;

	//�摜�f�[�^�Q
	TextureResource m_texture;
	//���f�[�^�Q
	SoundResouce m_sounds;
	//���f���f�[�^�Q
	ModelResouce m_models;

	// �o�C�i���t�@�C��
	BinaryResouce m_binaryFile; 
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	ResourceManager();
	// �C���X�^���X���R�s�[���邱�Ƃ��֎~����
	void operator=(const ResourceManager&) = delete;
	// �C���X�^���X�����[�u���邱�Ƃ��֎~����
	ResourceManager& operator= (ResourceManager&&) = delete;
	// �R�s�[�R���X�g���N�^�͋֎~����
	ResourceManager(const ResourceManager&) = delete;
	// ���[�u�R���X�g���N�^�͋֎~����
	ResourceManager(ResourceManager&&) = delete;

	// �f�X�g���N�^
	~ResourceManager();


// ����
public:
	// ResourceManager�N���X�̃C���X�^���X���擾����
	static ResourceManager* const GetInstance();

	//�摜�f�[�^�v��
	ID3D11ShaderResourceView** RequestTexture(wchar_t const*     filename);
	ID3D11ShaderResourceView** RequestTexture(const std::string& filename);

	//���f�[�^�v��
	DirectX::SoundEffect* RequestSound(wchar_t const*     filename);
	DirectX::SoundEffect* RequestSound(const std::string& filename);

	//sdkmesh���f���f�[�^�v��
	DirectX::Model* RequestModel(wchar_t const*     filename);
	DirectX::Model* RequestModel(const std::string& filename);

	//�o�C�i���t�@�C���v��
	BinaryFile* RequestBinaryFile(wchar_t const* filename);
	//�S���\�[�X�폜
	void Clear();

//��������
private:
	//skdmesh���f���f�[�^�ǂݍ���
	void LoadModel(const std::string& filename);
	//wav���f�[�^�ǂݍ���
	void LoadSound(const std::string& filename);
	//�摜�f�[�^�ǂݍ���
	void LoadTexture(const std::string& filename);

	//�S���\�[�X�̓ǂݍ���
	void LoadResources();
	//�擾�E�ݒ�
public:
	void SetAudioEngine(DirectX::AudioEngine* audioEngine) { m_audioEngine = audioEngine; }
};
