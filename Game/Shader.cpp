/**
 * @file   Shader.cpp
 *
 * @brief  �w�w�w�w�Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Shader.h"
#include "Game/Common/ResourceManager.h"
#include"Game/Object/Light.h"
// �N���X�萔�̒�` ===========================================================

std::unique_ptr<Shader> Shader::s_shader = nullptr;

const std::vector<D3D11_INPUT_ELEMENT_DESC> Shader::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,								D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",	    0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
Shader::Shader()
	:m_graphics{Graphics::GetInstance()}
	,m_inputLayout{}				// ���̓��C�A�E�g

{
	CreateShader();
}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Shader::Initialize()
{
	
}



/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Shader::Update()
{

}

void Shader::StartShader(ShaderType type, ID3D11Buffer* cBuffer)
{
	switch (type)
	{
	case Shader::Model:
		SetModelShader(cBuffer);
		break;
	case Shader::UI:
		break;
	default:
		break;
	}
}



void Shader::EndShader()
{
	ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	// �V�F�[�_�[�𖳌���
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	// �R���X�^���g�o�b�t�@�𖳌���
	ID3D11Buffer* nullBuffer = nullptr;
	context->VSSetConstantBuffers(0, 1, &nullBuffer);
	context->PSSetConstantBuffers(0, 1, &nullBuffer);
	context->PSSetConstantBuffers(0, 1, &nullBuffer);
}

/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Shader::Draw()
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
void Shader::Finalize()
{

}


/**
 * @brief �N���X�̃C���X�^���X���擾����
 *
 * @param[in] �Ȃ�
 *
 * @return �N���X�̃C���X�^���X�ւ̃|�C���^
 */
Shader* const Shader::GetInstance()
{
	if (!s_shader)
	{
		s_shader.reset(new Shader());
	}
	return s_shader.get();
}


/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
ID3D11InputLayout* Shader::GetInputLayout()
{
	return m_inputLayout.Get();
}


/**
 * @brief ���f���̒��_�V�F�[�_�[���擾����
 *
 * @param[in] �Ȃ�
 *
 * @return ���f���̒��_�V�F�[�_�[�ւ̃|�C���^
 */
ID3D11VertexShader* Shader::GetModelVS()
{
	return m_modelVS.Get();
}


/**
 * @brief ���f���̃s�N�Z���V�F�[�_�[���擾����
 *
 * @param[in] �Ȃ�
 *
 * @return ���f���̃s�N�Z���V�F�[�_�[�ւ̃|�C���^
 */
ID3D11PixelShader* Shader::GetModelPS()
{
	return m_modelPS.Get();
}


/**
 * @brief ���f���̃W�I���g���V�F�[�_�[���擾����
 *
 * @param[in] �Ȃ�
 *
 * @return ���f���̃W�I���g���V�F�[�_�[�ւ̃|�C���^
 */
ID3D11GeometryShader* Shader::GetModelGS()
{
	return m_modelGS.Get();
}

void Shader::RegisterLight(Light* light)
{
	m_lights.push_back(light);
}

void Shader::UnRegisterLight()
{
	for (auto& light : m_lights)
	{
		if (light)
		{
			light->Finalize();
		}
	}
	m_lights.clear();
}

void Shader::CreateShader()
{
	// �V�F�[�_�[�̃o�C�i���f�[�^��ǂݍ���
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	BinaryFile vertexShader = resourceManager->RequestBinaryFile(L"Resources/Shaders/ModelShader/ModelVS.cso");
	BinaryFile pixelShader = resourceManager->RequestBinaryFile(L"Resources/Shaders/ModelShader/ModelPS.cso");
	BinaryFile geometryShader = resourceManager->RequestBinaryFile(L"Resources/Shaders/ModelShader/ModelGS.cso");
	// �V�F�[�_�[���쐬����
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
		vertexShader.GetData(), vertexShader.GetSize(), nullptr, m_modelVS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
		pixelShader.GetData(), pixelShader.GetSize(), nullptr, m_modelPS.ReleaseAndGetAddressOf());
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
		geometryShader.GetData(), geometryShader.GetSize(), nullptr, m_modelGS.ReleaseAndGetAddressOf());


	//	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd2;
	ZeroMemory(&bd2, sizeof(bd2));
	bd2.Usage = D3D11_USAGE_DEFAULT;
	bd2.ByteWidth = sizeof(LightBuffer);
	bd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd2.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd2, nullptr, &m_lBuffer);

}

void Shader::SetModelShader(ID3D11Buffer* cBuffer)
{
	ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();

	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { cBuffer };

	LightBuffer lbuff;
	lbuff.LightPosition = DirectX::SimpleMath::Vector3(0.0f, 2.0f, 0.0f);
	lbuff.LightInvSqrRadius = 1.0f / (100.0f * 100.0f); //���C�g���͂������i�Q��̋t���j
	lbuff.LightColor = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	lbuff.LightIntensity = 3.0f;
	lbuff.Attenuation = DirectX::SimpleMath::Vector4(1.0f, 0.0f, 0.005f, 0.0f); // �f�t�H���g�̌���

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_lBuffer.Get(), 0, NULL, &lbuff, 0, 0);

	ID3D11Buffer* lb[1] = { m_lights[0]->GetLightBuffer()};

	context->PSSetConstantBuffers(1, 1, lb);


	// �R���X�^���g�o�b�t�@��ݒ�
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	// �V�F�[�_�[��ݒ�
	context->VSSetShader(m_modelVS.Get(), nullptr, 0);
	context->PSSetShader(m_modelPS.Get(), nullptr, 0);
	context->GSSetShader(m_modelGS.Get(), nullptr, 0);

}
