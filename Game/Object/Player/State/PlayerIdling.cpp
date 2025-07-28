#include "pch.h"
#include "Game/Object/Player/State/PlayerIdling.h"
#include "Game/Object/Player/Player.h"

// �R���X�g���N�^
PlayerIdling::PlayerIdling(Player* player)
	:
	m_player(player),
	m_graphics{},
	m_context{}
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
	// �R���e�L�X�g���擾����
	m_context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
}
// �f�X�g���N�^
PlayerIdling::~PlayerIdling()
{
}

// ����������
void PlayerIdling::Initialize()
{
	PreUpdate();
}

// ���O�X�V����
void PlayerIdling::PreUpdate()
{
}

// �X�V����
void PlayerIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();
	if (key->pressed.Left || key->pressed.Right || key->pressed.Up || key->pressed.Down) 
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::MOVING);
	}
	if (key->pressed.Space) 
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::JUMPING);
	}
	if (key->pressed.Z) 
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::ATTACK);
	}

	DirectX::SimpleMath::Vector3 v = m_player->GetVelocity();
	
	v.y += -0.8f * elapsedTime;

	m_player->SetVelocity(v);

	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());

}

// ����X�V����
void PlayerIdling::PostUpdate()
{
}

// �`�悷��
void PlayerIdling::Render()
{
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext*		 context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	Player::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(m_player->GetCurrentPosition(),m_player->GetCurrentQuaternion(),m_player->GetScale()).Transpose();
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_player->GetCBuffer(), 0, NULL, &cbuff, 0, 0);


	Shader* shader = Shader::GetInstance();

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
			
			Shader::GetInstance()->StartShader(Shader::Model,m_player->GetCBuffer());
			
			context->IASetInputLayout(m_player->GetInputLayout());

		});
	Shader::GetInstance()->EndShader();
#ifdef _DEBUG
#endif // DEBUG

}

// �㏈�����s��
void PlayerIdling::Finalize()
{
}
