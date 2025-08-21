/**
 * @file   Graphics.cpp
 *
 * @brief  �O���t�B�b�N�Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Game/Common/Graphics.h"



// �����o�֐��̒�` ===========================================================
std::unique_ptr<Graphics> Graphics::s_graphics = nullptr;
/**
 * @brief Graphics�N���X�̃C���X�^���X���擾����
 *
 * @param[in] �Ȃ�
 *
 * @return Graphics�N���X�̃C���X�^���X
 */
Graphics* const Graphics::GetInstance()
{
	if (s_graphics == nullptr)
	{
		//Graphics�I�u�W�F�N�g�𐶐����A���̃|�C���^��s_graphics�Ɋi�[����
		s_graphics.reset(new Graphics());
	}
	return s_graphics.get();
}
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
Graphics::Graphics()
	:
	m_deviceResources{},			// �f�o�C�X���\�[�X
	m_commonStates{},				// �R�����X�e�[�g
	m_spriteBatch{},				// �X�v���C�g�o�b�`
	m_spriteFont{},					// �X�v���C�g�t�H���g
	m_basicEffect{},				// �x�[�V�b�N�G�t�F�N�g
	m_primitiveBatch{},				// �v���~�e�B�u�o�b�`
	m_effectFactory{},				// �G�t�F�N�g�t�@�N�g���[
	m_rasterrizerState{},			// ���X�^���C�U�[�X�e�[�g
	m_inputLayout{},				// ���̓��C�A�E�g
	m_screenW{},					// �X�N���[���T�C�Y
	m_screenH{},					// �X�N���[���T�C�Y
	m_view{},						// �r���[�s��
	m_projection{},					// �ˉe�s��
	m_device{},						// �f�o�C�X
	m_context{}						// �f�o�C�X�R���e�L�X�g
{
	// DeviceResources�N���X�̃C���X�^���X�𐶐�����
	m_deviceResources = std::make_unique<DX::DeviceResources>();
}

/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Graphics::Initialize()
{
	// �f�o�C�X���擾����
	m_device = m_deviceResources->GetD3DDevice();
	// �f�o�C�X�R���e�L�X�g���擾����
	m_context = m_deviceResources->GetD3DDeviceContext();

	// �R�����X�e�[�g�𐶐�����
	m_commonStates = std::make_unique<DirectX::CommonStates>(m_device);
	// �X�v���C�g�o�b�`�𐶐�����
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_context);
	// �x�[�V�b�N�G�t�F�N�g�𐶐�����
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(m_device);
	// �X�v���C�g�t�H���g�𐶐�����
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_device, L"resources\\font\\SegoeUI_18.spritefont");
	// �v���~�e�B�u�o�b�`�𐶐�����
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(m_context);
	// ���̓��C�A�E�g�𐶐�����
	m_basicEffect->SetVertexColorEnabled(true);
	// �e�N�X�`���𖳌��ɂ���
	m_basicEffect->SetTextureEnabled(false);
	//�g���b�J�[�𐶐�����
	m_traker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	void const* shaderByteCode;
	size_t byteCodeLength;
	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	// ���̓��C�A�E�g�𐶐�����
	m_device->CreateInputLayout(
		DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.ReleaseAndGetAddressOf()
	);
	// ���X�^���C�U�[�f�B�X�N���v�V����
	CD3D11_RASTERIZER_DESC rasterizerStateDesc(
		D3D11_FILL_SOLID, D3D11_CULL_NONE, FALSE,
		D3D11_DEFAULT_DEPTH_BIAS, D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
		D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS, TRUE, FALSE, FALSE, TRUE
	);
	// ���X�^���C�Y�X�e�[�g�𐶐�����
	m_device->CreateRasterizerState(&rasterizerStateDesc, m_rasterrizerState.ReleaseAndGetAddressOf());
	// �G�t�F�N�g�t�@�N�g���𐶐�����
	m_effectFactory = std::make_unique<DirectX::EffectFactory>(m_device);
}

/**
 * @brief �`��v���~�e�B�u���J�n����
 *
 * @param[in] view�@	  �r���[�s��
 * @param[in] projection�@�ˉe�s��
 *
 * @return �Ȃ�
 */
void Graphics::DrawPrimitiveBegin(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	m_context->OMSetBlendState(m_commonStates->Opaque(), nullptr, 0xFFFFFFFF);
	m_context->OMSetDepthStencilState(m_commonStates->DepthNone(), 0);
	m_context->RSSetState(m_commonStates->CullNone());
	//m_context->RSSetState(m_rasterrizeState.Get());

	// �r���[�s���ݒ肷��
	m_basicEffect->SetView(view);
	// �v���W�F�N�V�����s���ݒ肷��
	m_basicEffect->SetProjection(projection);
	// ���[���h�s���ݒ肷��
	m_basicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);

	// ���_�J���[��L���ɂ���
	m_basicEffect->SetVertexColorEnabled(true);
	// �e�N�X�`����L���ɂ���
	m_basicEffect->SetTextureEnabled(false);
	// ���̓��C�A�E�g��ݒ肷��
	m_basicEffect->Apply(m_context);
	// ���̓��C�A�E�g��ݒ肷��
	m_context->IASetInputLayout(m_inputLayout.Get());
	// �v���~�e�B�u�o�b�`���J�n����
	m_primitiveBatch->Begin();
}

/**
 * @brief �`��v���~�e�B�u���I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Graphics::DrawPrimitiveEnd()
{
	// �v���~�e�B�u�o�b�`���I������
	m_primitiveBatch->End();
}
