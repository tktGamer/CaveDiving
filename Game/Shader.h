/**
 * @file   Shader.h
 *
 * @brief  Shader�Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"Game/Common/Graphics.h"

class Light;
// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief Shader
  */
class Shader
{
// �N���X�萔�̐錾 -------------------------------------------------
public:
	//	�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Light;

	};

	//	�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct LightBuffer
	{
		DirectX::SimpleMath::Vector3 LightPosition;      // ���C�g�ʒu
		float LightInvSqrRadius;  // ���C�g�̓͂�����
		DirectX::SimpleMath::Vector3 LightColor;         // ���C�g�J���[
		float LightIntensity;    // ���C�g���x
		DirectX::SimpleMath::Vector4	Attenuation;

	};

	enum ShaderType 
	{
		Model, //���f���V�F�[�_�[
		UI,   //UI�V�F�[�_�[
	};

// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// Shader�N���X�̃C���X�^���X�ւ̃��j�[�N�|�C���^�u�V���O���g��������v
	static std::unique_ptr<Shader> s_shader;

	Graphics* m_graphics;	// �O���t�B�b�N�X�N���X�̃|�C���^
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//	���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_modelVS;
	//	�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_modelPS;
	//�W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_modelGS;

	//���C�g�z��
	std::vector<Light*> m_lights;
	//	�֐�
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_lBuffer;

// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Shader();
	// �C���X�^���X���R�s�[���邱�Ƃ��֎~����
	void operator=(const Shader&) = delete;
	// �C���X�^���X�����[�u���邱�Ƃ��֎~����
	Shader& operator= (Shader&&) = delete;
	// �R�s�[�R���X�g���N�^�͋֎~����
	Shader(const Shader&) = delete;
	// ���[�u�R���X�g���N�^�͋֎~����
	Shader(Shader&&) = delete;

	// �f�X�g���N�^
	~Shader()=default;


// ����
public:

	void Initialize();

	void Update();

	//�V�F�[�_�[�J�n
	void StartShader(ShaderType type,ID3D11Buffer* cBuffer);

	//�V�F�[�_�[�I��
	void EndShader();

	void Draw();

	void Finalize();

//�@�擾�E�ݒ�
public:
	static  Shader* const GetInstance();

	ID3D11InputLayout* GetInputLayout();
	//�V�F�[�_�[�̎擾
	//���f���̒��_�V�F�[�_
	ID3D11VertexShader*   GetModelVS();
	ID3D11PixelShader*    GetModelPS();
	ID3D11GeometryShader* GetModelGS();

	//���C�g�o�^
	void RegisterLight(Light* light);
//�@��������
private:
	//�V�F�[�_�쐬
	void CreateShader();

	//���f���V�F�[�_�[�ݒ�
	void SetModelShader(ID3D11Buffer* cBuffer);
};

