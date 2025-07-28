/**
 * @file   Stage.cpp
 *
 * @brief  �X�e�[�W�Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Stage.h"

//���_���
const std::vector<D3D11_INPUT_ELEMENT_DESC> Stage::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,								D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",	    0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] parent �e�I�u�W�F�N�g�̃|�C���^(�Ȃ�)
 * @param[in] initialPosition �����ʒu
 * @param[in] initialAngle    �����p�x
 */
Stage::Stage(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	: GameObject(Tag::ObjectType::Stage,parent,initialPosition,initialAngle)
	, m_objectNumber{ CountUpNumber() }
	, m_messageID{  }
	, m_graphics{ Graphics::GetInstance() }
	, m_box{ GetPosition(),DirectX::SimpleMath::Vector3(50.01f,1.01f,50.01f)} // �����ʒu�ƃT�C�Y��ݒ�
{

}



/**
 * @brief �f�X�g���N�^
 */
Stage::~Stage()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Stage::Initialize()
{
	SetModel(ResourceManager::GetInstance()->RequestModel(L"block.sdkmesh"));
	SetPosition(DirectX::SimpleMath::Vector3(0.0f, -2.0f, 0.0f));
	SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	SetScale(DirectX::SimpleMath::Vector3(50.0f, 1.0f, 50.0f));
	SetTexture(ResourceManager::GetInstance()->RequestTexture("block.png"));
	
	SetShape(&m_box);


}




/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Stage::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	m_box.SetCenter(currentPosition + GetPosition());
}



/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Stage::Draw()
{
	Shader* shader = Shader::GetInstance();	
	ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = m_graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = m_graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = m_graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	Stage::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(GetPosition(), GetQuaternion(), GetScale()).Transpose();
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();

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

}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Stage::Finalize()
{

}

void Stage::OnMessegeAccepted(Message::MessageID messageID)
{

}


int Stage::GetObjectNumber()
{
	return m_objectNumber;
}
