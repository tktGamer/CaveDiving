/**
 * @file   Pikel.cpp
 *
 * @brief  ��͂��i�v���C���[�̕���j�Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Pikel.h"
#include"../CaveDiving/Game/Object/Player/Player.h"
#include"Game/Common/Collision/CollisionManager.h"
// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
Pikel::Pikel(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:m_graphics{Graphics::GetInstance()}
	, GameObject(Tag::ObjectType::Pikel,parent,initialPosition,initialAngle)
	, m_objectNumber{ CountUpNumber() }
	, m_messageID{}
	, m_sphere{ GetPosition(), 1.5f}
	,m_display{ Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()}
{
	SetTexture(ResourceManager::GetInstance()->RequestTexture(L"pikel.png"));
	SetModel(ResourceManager::GetInstance()->RequestModel(L"pikel.sdkmesh"));

	m_sphere.SetEnabled(false);
	Messenger::GetInstance()->Register(m_objectNumber, this);

	CollisionManager::GetInstance()->Register(this);
}




/**
 * @brief �f�X�g���N�^
 */
Pikel::~Pikel()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Pikel::Initialize()
{
}




/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Pikel::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	m_currentAngle = GetQuaternion() * currentAngle;
	m_currentPosition = m_initialPosition + currentPosition + GetPosition();

	m_sphere.SetCenter(m_currentPosition +DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f,1.0f,0.0f),m_currentAngle));
	SetShape(&m_sphere);
}




/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Pikel::Draw()
{
	Shader* shader = Shader::GetInstance();
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = TKTLib::GetWorldMatrix(m_currentPosition,m_currentAngle, GetScale());
	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	Player::ConstBuffer cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();

	//GetModel()->Draw(context, *states, world, view, proj);

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(shader->GetCBuffer(Shader::Model), 0, NULL, &cbuff, 0, 0);

	GetModel()->Draw(context, *states, world, view, proj, false, [&]()
		{
			//	���f���\�������邽�߂̎���V�F�[�_�Ɋ֘A����ݒ���s��


			//	�摜�p�T���v���[�̓o�^
			ID3D11SamplerState* sampler[1] = { states->PointWrap() };
			context->PSSetSamplers(0, 1, sampler);

			if (GetTexture() != nullptr)
			{
				//	�ǂݍ��񂾉摜���s�N�Z���V�F�[�_�ɓ`����
				//	����VS��t0���g���Ă��邽�߁A
				//	t0�����C���Ŏg���Ă���Ə���ɑz��B
				context->PSSetShaderResources(0, 1, GetTexture());
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
	
	//m_sphere.AddDisplayCollision(&m_display);
	m_display.DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates()
		, Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());

}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Pikel::Finalize()
{

}

void Pikel::OnMessegeAccepted(Message::MessageID messageID)
{
	switch (messageID)
	{
	case Message::COLLISIONVALID:
		m_sphere.SetEnabled(true);
		break;
	case Message::COLLISIONINVALID:
		m_sphere.SetEnabled(false);
		break;
	}
}

int Pikel::GetObjectNumber()
{
	return 0;
}
