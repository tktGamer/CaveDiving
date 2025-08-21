/**
 * @file   PlayerAttack.cpp
 *
 * @brief  �v���C���[�̍U����ԂɊւ���\�[�X�t�@�C��
 *
 * @author ����Җ� ���n�M��
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerAttack.h"
#include "Game/Object/Player/Player.h"
// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] player �v���C���[�̃|�C���^
 */
PlayerAttack::PlayerAttack(Player* player, Hand* hand)
	:m_player(player)
	,m_graphics{}
	,m_pHand{hand}
	,m_motionLerp{}
	, m_attackMotion{ m_pHand,nullptr }
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
}
/**
 * @brief �f�X�g���N�^
 */
PlayerAttack::~PlayerAttack()
{
}

/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void PlayerAttack::Initialize()
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
void PlayerAttack::PreUpdate()
{
	m_pHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(-90.0f)));
	m_motionLerp = 0.0f;

	
	//�s�b�P���̓����蔻���L���ɂ���
	Messenger::GetInstance()->Notify(m_player->GetObjectNumber() + 3, Message::COLLISIONVALID);

}

/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void PlayerAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();

	if (key->pressed.Z)
	{
		m_attackMotion.SetIsNextAttack(true);
	}


	m_player->SetVelocity(m_player->GetVelocity()*0.8f);

	if(m_attackMotion.Update())
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::IDLING);
	}


	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());

}

/**
 * @brief ����X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void PlayerAttack::PostUpdate()
{
	m_pHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(-50.0f)));
	m_pHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	//�s�b�P���̓����蔻��𖳌��ɂ���
	Messenger::GetInstance()->Notify(m_player->GetObjectNumber() + 3, Message::COLLISIONINVALID);

	m_attackMotion.Reset();

}

/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void PlayerAttack::Render()
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
void PlayerAttack::Finalize()
{
}

bool PlayerAttack::Motion()
{
	DirectX::SimpleMath::Quaternion start = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	DirectX::SimpleMath::Quaternion end = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(170.0f));
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;
	//	//* DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(45.0f))
	//	//* DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(45.0f))
	//	DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(-90.0f));

	//q = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	//q = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(145.0f));

	DirectX::SimpleMath::Quaternion::Lerp(start, end, m_motionLerp, q);
	m_motionLerp += 6.0f * Messenger::GetInstance()->GetElapsedTime();
	//m_pHand->SetQuaternion()
	m_pHand->SetMotionAngle(q);


	if (m_motionLerp >= 1.0f) 
	{
		return true;
	}
	return false;
}

bool PlayerAttack::Motion2()
{
	DirectX::SimpleMath::Quaternion start = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(170.0f));
	DirectX::SimpleMath::Quaternion end = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;

	DirectX::SimpleMath::Quaternion::Lerp(start, end, m_motionLerp, q);
	m_motionLerp += 4.0f * Messenger::GetInstance()->GetElapsedTime();

	m_pHand->SetMotionAngle(q);


	if (m_motionLerp >= 1.0f)
	{
		return true;
	}
	return false;
}

bool PlayerAttack::Motion3()
{
	
	DirectX::SimpleMath::Quaternion start = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	DirectX::SimpleMath::Quaternion end = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(170.0f));
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(TKTLib::Lerp(0.0f, 360.0f, m_motionLerp)));

	//DirectX::SimpleMath::Quaternion::Lerp(start, end, m_motionLerp, q);
	m_motionLerp += 4.0f * Messenger::GetInstance()->GetElapsedTime();

	m_pHand->SetMotionAngle(q);


	if (m_motionLerp >= 1.0f)
	{
		return true;
	}
	return false;
}
