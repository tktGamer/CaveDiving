/**
 * @file   PlayerJumping.cpp
 *
 * @brief  �v���C���[�̃W�����v��ԂɊւ���\�[�X�t�@�C��
 *
 * @author ����Җ� ���n�M��
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerJumping.h"
#include "Game/Object/Player/Player.h"

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] player �v���C���[�̃|�C���^
 */
PlayerJumping::PlayerJumping(Player* player)
	: m_player(player)
	, m_graphics{}
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
}
/**
 * @brief �f�X�g���N�^
 */
PlayerJumping::~PlayerJumping()
{
}

/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void PlayerJumping::Initialize()
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
void PlayerJumping::PreUpdate()
{
	DirectX::SimpleMath::Vector3 v = m_player->GetVelocity();
	//�W�����v�̑��x��ݒ�
	v.y = 0.5f;
	m_player->SetVelocity(v);

}

/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void PlayerJumping::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();
	DirectX::SimpleMath::Vector3 v = m_player->GetVelocity();

	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;

	if (key->GetLastState().Up)
	{
		v -= DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f) * elapsedTime, m_player->GetQuaternion());
	}
	if (key->GetLastState().Down)
	{
		v += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f) * elapsedTime, m_player->GetQuaternion());

	}
	if (key->GetLastState().Left)
	{
		v -= DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f) * elapsedTime, m_player->GetQuaternion());

		q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(3.0f));
	}
	if (key->GetLastState().Right)
	{
		v += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f) * elapsedTime, m_player->GetQuaternion());

		q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-3.0f));
	}
	if (key->IsKeyPressed(DirectX::Keyboard::Z))
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::ATTACK);
	}

	// �p���ɉ�]��������
	m_player->SetQuaternion(m_player->GetQuaternion() * q);

	if (v.Length() <= 0.001f)
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::IDLING);
	}
	v *= 0.96f;
	v.y += -0.8f * elapsedTime;

	m_player->SetVelocity(v);

	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());

}

/**
 * @brief ����X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void PlayerJumping::PostUpdate()
{
}

/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void PlayerJumping::Render()
{
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	Player::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(m_player->GetCurrentPosition(), m_player->GetCurrentQuaternion(), m_player->GetScale()).Transpose();
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();

	Shader* shader = Shader::GetInstance();
	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(shader->GetCBuffer(Shader::Model), 0, NULL, &cbuff, 0, 0);



	m_player->GetModel()->Draw(context, *states, world, view, proj, false, [&]()
		{
			//	���f���\�������邽�߂̎���V�F�[�_�Ɋ֘A����ݒ���s��


			//	�摜�p�T���v���[�̓o�^
			ID3D11SamplerState* sampler[1] = { states->PointWrap() };
			context->PSSetSamplers(0, 1, sampler);

			if (m_player->GetTexture() != nullptr)
			{
				//	�ǂݍ��񂾉摜���s�N�Z���V�F�[�_�ɓ`����
				//	����VS��t0���g���Ă��邽�߁A
				//	t0�����C���Ŏg���Ă���Ə���ɑz��B
				context->PSSetShaderResources(0, 1, m_player->GetTexture());
			}

			//	�������`��w��
			ID3D11BlendState* blendstate = states->NonPremultiplied();

			//	�������菈��
			context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

			//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			//	�J�����O�͂Ȃ�
			context->RSSetState(states->CullClockwise());

			Shader::GetInstance()->StartShader(Shader::Model, shader->GetCBuffer(Shader::Model));

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
void PlayerJumping::Finalize()
{
}
