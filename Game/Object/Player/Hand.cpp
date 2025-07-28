/**
 * @file   Hand.cpp
 *
 * @brief  �v���C���[�̎�Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Hand.h"
#include"../CaveDiving/Game/Object/Player/Player.h"
// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
Hand::Hand(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:m_graphics{Graphics::GetInstance()}
	, GameObject(Tag::ObjectType::Player,parent,initialPosition,initialAngle)
{
	SetTexture(ResourceManager::GetInstance()->RequestTexture(L"hand.png"));
	SetModel(ResourceManager::GetInstance()->RequestModel(L"hand.sdkmesh"));

}



/**
 * @brief �f�X�g���N�^
 */
Hand::~Hand()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Hand::Initialize()
{
	m_pikel = std::make_unique<Pikel>(this, DirectX::SimpleMath::Vector3(0.0f,0.0f,0.0f), DirectX::XMConvertToRadians(0.0f));

}




/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Hand::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	SetQuaternion(GetQuaternion() * DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(1.0f)));
	m_currentAngle = GetQuaternion() * currentAngle;
	m_currentPosition =DirectX::SimpleMath::Vector3::Transform(m_initialPosition, m_currentAngle)+ currentPosition + GetPosition();
	
	if(m_pikel)
	m_pikel->Update(elapsedTime, m_currentPosition, m_currentAngle);
}




/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Hand::Draw()
{
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

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	//context->UpdateSubresource(GetCBuffer(), 0, NULL, &cbuff, 0, 0);


	Shader* shader = Shader::GetInstance();

	GetModel()->Draw(context, *states, world, view, proj);
	//GetModel()->Draw(context, *states, world, view, proj, false, [&]()
	//	{
	//		//	���f���\�������邽�߂̎���V�F�[�_�Ɋ֘A����ݒ���s��


	//		//	�摜�p�T���v���[�̓o�^
	//		ID3D11SamplerState* sampler[1] = { states->PointWrap() };
	//		context->PSSetSamplers(0, 1, sampler);

	//		if (GetTexture() != nullptr)
	//		{
	//			//	�ǂݍ��񂾉摜���s�N�Z���V�F�[�_�ɓ`����
	//			//	����VS��t0���g���Ă��邽�߁A
	//			//	t0�����C���Ŏg���Ă���Ə���ɑz��B
	//			context->PSSetShaderResources(0, 1, GetTexture());
	//		}

	//		//	�������`��w��
	//		ID3D11BlendState* blendstate = states->NonPremultiplied();

	//		//	�������菈��
	//		context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//		//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	//		context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//		//	�J�����O�͂Ȃ�
	//		context->RSSetState(states->CullClockwise());

	//		Shader::GetInstance()->StartShader(Shader::Model, GetCBuffer());

	//		context->IASetInputLayout();

	//	});
	//Shader::GetInstance()->EndShader();
	if (m_pikel)
	m_pikel->Draw();
}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Hand::Finalize()
{

}

void Hand::OnMessegeAccepted(Message::MessageID messageID)
{
}

int Hand::GetObjectNumber()
{
	return 0;
}
