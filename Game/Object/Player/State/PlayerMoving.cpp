#include "pch.h"
#include "Game/Object/Player/State/PlayerMoving.h"
#include "Game/Object/Player/Player.h"

// �R���X�g���N�^
PlayerMoving::PlayerMoving(Player* player)
	: m_player(player)
	, m_graphics{}
{
	// �O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
}
// �f�X�g���N�^
PlayerMoving::~PlayerMoving()
{
}

// ����������
void PlayerMoving::Initialize()
{
	PreUpdate();
}

// ���O�X�V����
void PlayerMoving::PreUpdate()
{
}

// �X�V����
void PlayerMoving::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();
	DirectX::SimpleMath::Vector3 v = m_player->GetVelocity();

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
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::IDLING);
	}
	
	// �p���ɉ�]��������
	m_player->SetQuaternion(m_player->GetQuaternion() * q);

	if(v.Length()<=0.001f)
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::IDLING);
	}
	v *= 0.96f;
	v.y += -0.8f * elapsedTime;

	m_player->SetVelocity(v);

	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());

}

// ����X�V����
void PlayerMoving::PostUpdate()
{
}

// �`�悷��
void PlayerMoving::Render()
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

			Shader::GetInstance()->StartShader(Shader::Model, m_player->GetCBuffer());

			context->IASetInputLayout(m_player->GetInputLayout());

		});
	Shader::GetInstance()->EndShader();

#ifdef _DEBUG
#endif // DEBUG

}

// �㏈�����s��
void PlayerMoving::Finalize()
{
}
