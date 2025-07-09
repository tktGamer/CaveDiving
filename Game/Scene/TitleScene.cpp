/**
 * @file   TitleScene.cpp
 *
 * @brief  ���S�V�[���Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "TitleScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"




// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] sceneManager    �V�[�����Ǘ����Ă���}�l�[�W��
 * @param[in] resourceManager ���\�[�X���Ǘ����Ă���}�l�[�W��
 */
TitleScene::TitleScene(SceneManager* pSceneManager)
	: Scene{ pSceneManager }
	, m_pResourceManager{}
	, m_caveModelParams{}
	, m_demoPlayerModelParams{}
{
	m_camera = std::make_unique<Camera>();
	m_pResourceManager = ResourceManager::GetInstance();
}



/**
 * @brief �f�X�g���N�^
 */
TitleScene::~TitleScene()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void TitleScene::Initialize()
{
	m_titleTexture = *m_pResourceManager->RequestTexture("title.png");
	m_demoPlayerModelParams.SetModelParams(m_pResourceManager->RequestModel("player.sdkmesh"));
	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3{ 0.0f,0.5f,6.5f };
	DirectX::SimpleMath::Vector3 rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f);
	m_demoPlayerModelParams.SetModelParams(position, rotation, scale);
	m_caveModelParams.SetModelParams(m_pResourceManager->RequestModel("cave.sdkmesh"));
	position = DirectX::SimpleMath::Vector3::Zero;
	rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	m_caveModelParams.SetModelParams(position, rotation, scale);

	m_length = 25.0f;
	m_angle = 85.0f;
	m_camera->Initialize({ 0,11.0f,10.0f });
	m_camera->SetTartet(m_demoPlayerModelParams.GetPosition(), m_demoPlayerModelParams.GetQuaternion());
	m_camera->SetTargetPos(m_demoPlayerModelParams.GetPosition());
}



/**
 * @brief �X�V����
 *
 * @param[in] inputDevice ���̓f�o�C�X
 *
 * @return �Ȃ�
 */
void TitleScene::Update(float elapsedTime)
{
	DirectX::Keyboard::KeyboardStateTracker* traker = Graphics::GetInstance()->GetKeyboardTracker();

	float r = m_angle * 3.14f / 180.0f;
	
	if (traker->pressed.Space)
	{
		ChangeScene("Game");
	}
	/*m_camera->SetEyePosX(m_length * std::cos(r));
	m_camera->SetEyePosZ(m_length * std::sin(r));*/
	m_camera->SetDistance(DirectX::SimpleMath::Vector3{ m_length * std::cos(r), 17.0f, m_length * std::sin(r) });
	m_angle += 10.0f*elapsedTime;
	if (m_angle >= 360.0f)
	{
		m_angle = 0.0f;
	}

	m_camera->Update(elapsedTime);
}



/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void TitleScene::Render()
{
	ID3D11DeviceContext* context = GetGraphics()->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = GetGraphics()->GetCommonStates();
	DirectX::SimpleMath::Matrix proj = GetGraphics()->GetProjectionMatrix();

	auto view=m_camera->GetView();
	//m_testPlayer.Draw(*context, *states, view, proj);
	DirectX::SimpleMath::Matrix world;
	m_demoPlayerModelParams.GetModel()->Draw(context, *states, m_demoPlayerModelParams.GetWorldMatrix(), view, proj);
	m_caveModelParams.GetModel()->Draw(context, *states, m_caveModelParams.GetWorldMatrix(), view, proj);

	DirectX::SpriteBatch* spriteBatch = GetGraphics()->GetSpriteBatch();

	spriteBatch->Begin();
	spriteBatch->Draw(m_titleTexture, DirectX::SimpleMath::Vector2(400, 100));
	spriteBatch->End();
}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void TitleScene::Finalize()
{
	
}
