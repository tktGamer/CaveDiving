/**
 * @file   BatMoving.cpp
 *
 * @brief  �R�E�����̈ړ���ԂɊւ���\�[�X�t�@�C��
 *
 * @author ����Җ� ���n�M��
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Bat/State/BatMoving.h"
#include "Game/Object/Enemy/Bat/Bat.h"

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] player �v���C���[�̃|�C���^
 */
BatMoving::BatMoving(Bat* bat)
	: m_bat(bat)
	, m_graphics{}
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
}
/**
 * @brief �f�X�g���N�^
 */
BatMoving::~BatMoving()
{
}

/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void BatMoving::Initialize()
{
	PreUpdate();
}

/**
 * @brief ���O����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void BatMoving::PreUpdate()
{
}

/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void BatMoving::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();
	DirectX::SimpleMath::Vector3 v = m_bat->GetVelocity();

	DirectX::SimpleMath::Quaternion q;

	if (key->GetLastState().Up) 
	{
		v.z -= 1.0f*elapsedTime;
	}
	if (key->GetLastState().Down)
	{
		v.z += 1.0f*elapsedTime;
	}
	if (key->GetLastState().Left)
	{
		v.x -= 1.0f*elapsedTime;
		q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(1.0f));
	}
	if (key->GetLastState().Right)
	{
		v.x += 1.0f*elapsedTime;
		q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-1.0f));
	}
	if (key->IsKeyPressed(DirectX::Keyboard::Z)) 
	{
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::ATTACK);
	}
	if (key->pressed.Space)
	{
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::JUMPING);
	}

	// �p���ɉ�]��������
	m_bat->SetQuaternion(m_bat->GetQuaternion() * q);

	if(v.Length()<=0.001f)
	{
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::IDLING);
	}
	v *= 0.96f;
	v.y += -0.8f * elapsedTime;

	m_bat->SetVelocity(v);

	m_bat->SetPosition(m_bat->GetPosition() + m_bat->GetVelocity());

}

/**
 * @brief ����X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void BatMoving::PostUpdate()
{
}

/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void BatMoving::Render()
{
	Shader* shader = Shader::GetInstance();

	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	Bat::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(m_bat->GetCurrentPosition(), m_bat->GetCurrentQuaternion(), m_bat->GetScale()).Transpose();
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(shader->GetCBuffer(Shader::Model), 0, NULL, &cbuff, 0, 0);



	m_bat->GetModel()->Draw(context, *states, world, view, proj, false, [&]()
		{
			//	���f���\�������邽�߂̎���V�F�[�_�Ɋ֘A����ݒ���s��


			//	�摜�p�T���v���[�̓o�^
			ID3D11SamplerState* sampler[1] = { states->PointWrap() };
			context->PSSetSamplers(0, 1, sampler);

			if (m_bat->GetTexture() != nullptr)
			{
				//	�ǂݍ��񂾉摜���s�N�Z���V�F�[�_�ɓ`����
				//	����VS��t0���g���Ă��邽�߁A
				//	t0�����C���Ŏg���Ă���Ə���ɑz��B
				context->PSSetShaderResources(0, 1, m_bat->GetTexture());
			}

			//	�������`��w��
			ID3D11BlendState* blendstate = states->NonPremultiplied();

			//	�������菈��
			context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

			//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			//	�J�����O�͂Ȃ�
			context->RSSetState(states->CullClockwise());

			Shader::GetInstance()->StartShader(Shader::Model,shader->GetCBuffer(Shader::Model));

			context->IASetInputLayout(shader->GetInputLayout(Shader::Model));

		});
	Shader::GetInstance()->EndShader();

#ifdef _DEBUG
#endif // DEBUG

}

/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void BatMoving::Finalize()
{
}
