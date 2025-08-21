/**
 * @file   UserInterface.cpp
 *
 * @brief  ���[�U�[�C���^�[�t�F�C�X�Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "UserInterface.h"
#include"../Common/ResourceManager.h"
// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
UserInterface::UserInterface()
	:m_graphics{Graphics::GetInstance()}
	, m_pDR(nullptr)
	, m_windowHeight(0)
	, m_windowWidth(0)
	, m_textureHeight(0)
	, m_textureWidth(0)
	, m_texture(nullptr)
	, m_res(nullptr)
	, m_scale(DirectX::SimpleMath::Vector2::One)
	, m_position(DirectX::SimpleMath::Vector2::Zero)
	, m_anchor(ANCHOR::TOP_LEFT)
	, m_renderRatio(1.0f)
	, m_renderRatioOffset(0.0f)

{

}



/**
 * @brief �f�X�g���N�^
 */
UserInterface::~UserInterface()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void UserInterface::Initialize()
{

}



/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void UserInterface::Update()
{

}



/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void UserInterface::Draw()
{
	Shader* shader = Shader::GetInstance();

	ID3D11DeviceContext1* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	//	���_���
	//	Position.xy	:�g�k�p�X�P�[��
	//	Position.z	:�A���J�[�^�C�v(0�`8)�̐����Ŏw��
	//	Color.xy�@	:�A���J�[���W(�s�N�Z���w��:1280 �~720)
	//	Color.zw	:�摜�T�C�Y
	//	Tex.xy		:x = 0, y = 0
	DirectX::VertexPositionColorTexture vertex[1] = {
		DirectX::VertexPositionColorTexture(
			 DirectX::SimpleMath::Vector3(m_scale.x, m_scale.y, static_cast<float>(m_anchor))
			,DirectX::SimpleMath::Vector4(m_position.x, m_position.y, static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight))
			,DirectX::SimpleMath::Vector2(0,0))
	};

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	//	�E�B���h�E�T�C�Y
	cbuff.windowSize = DirectX::SimpleMath::Vector2(static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight));
	cbuff.AlphaData = m_renderRatio - m_renderRatioOffset; 
	cbuff.dammy = 0.0f; //	���g�p


	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	//context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);
	context->UpdateSubresource(shader->GetCBuffer(Shader::ShaderType::UI), 0, NULL, &cbuff, 0, 0);
	shader->StartShader(Shader::ShaderType::UI, shader->GetCBuffer(Shader::ShaderType::UI));

	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	//ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	//context->VSSetConstantBuffers(0, 1, cb);
	//context->GSSetConstantBuffers(0, 1, cb);
	//context->PSSetConstantBuffers(0, 1, cb);

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	�������`��w��
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	�������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//	�J�����O�͍�����
	context->RSSetState(m_states->CullNone());

	//	�V�F�[�_���Z�b�g����
	//context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	//context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	//context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_texture);

	//	�C���v�b�g���C�A�E�g�̓o�^
	//context->IASetInputLayout(m_inputLayout.Get());
	context->IASetInputLayout(shader->GetInputLayout(Shader::UI));

	//	�|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	//context->VSSetShader(nullptr, nullptr, 0);
	//context->GSSetShader(nullptr, nullptr, 0);
	//context->PSSetShader(nullptr, nullptr, 0);
	shader->EndShader();
}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void UserInterface::Finalize()
{

}

void UserInterface::Create(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor)
{
	m_pDR = m_graphics->GetDeviceResources();
	ID3D11Device1* device = m_graphics->GetDeviceResources()->GetD3DDevice();
	m_position = position;
	m_baseScale = m_scale = scale;
	m_anchor = anchor;

	//	�V�F�[�_�[�̍쐬
	//CreateShader(shader);

	//	�摜�̓ǂݍ���
	//LoadTexture(path);
	m_texture = ResourceManager::GetInstance()->RequestTexture(path);
	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(m_graphics->GetDeviceResources()->GetD3DDeviceContext());

	m_states = m_graphics->GetCommonStates();

	//�摜�T�C�Y���擾
	ResourceManager::GetInstance()->GetTextureSize(path, m_textureWidth, m_textureHeight);
	
}

void UserInterface::SetWindowSize(const int& width, const int& height)
{
	m_windowWidth = width;
	m_windowHeight = height;

}

void UserInterface::SetScale(DirectX::SimpleMath::Vector2 scale)
{
	m_scale = scale;
}
void UserInterface::SetPosition(DirectX::SimpleMath::Vector2 position)
{
	m_position = position;
}
void UserInterface::SetAnchor(ANCHOR anchor)
{
	m_anchor = anchor;
}
void UserInterface::SetRenderRatio(float ratio)
{
	m_renderRatio = ratio;
}
void UserInterface::SetRenderRatioOffset(float offset)
{
	m_renderRatioOffset = offset;
}
