/**
 * @file   GameScene.cpp
 *
 * @brief  X�V�[���Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "GameScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"


#include"Game/Common/Collision/Sphere.h"

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] sceneManager    �V�[�����Ǘ����Ă���}�l�[�W��
 * @param[in] resourceManager ���\�[�X���Ǘ����Ă���}�l�[�W��
 */
GameScene::GameScene(SceneManager* pSceneManager)
	: Scene{ pSceneManager }
	, m_pResourceManager{}
{
	TKTLib::ModelParams modelParams;

	m_pResourceManager = ResourceManager::GetInstance();

	m_displayCollision = std::make_unique<Ito::DisplayCollision>(
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());

	m_cM = CollisionManager::GetInstance();
}



/**
 * @brief �f�X�g���N�^
 */
GameScene::~GameScene()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void GameScene::Initialize()
{
	m_camera = std::make_unique<Camera>();
	m_player = std::make_unique<Player>(nullptr,DirectX::SimpleMath::Vector3{0.0f,1.0f,0.0f},DirectX::XMConvertToRadians(0.0f));
	m_stage = std::make_unique<Stage>(nullptr, DirectX::SimpleMath::Vector3{ 0.0f,-2.0f,0.0f }, DirectX::XMConvertToRadians(0.0f));
	m_enemyManager = std::make_unique<EnemyManager>();
	m_enemyManager->Spawn();
	m_camera->Initialize({ 0,1.0f,25.0f });
	m_camera->SetDistance(DirectX::SimpleMath::Vector3{ 0.0f, 7.0f, 25.0f });
	m_player->Initialize();
	m_stage->Initialize();

	m_camera->SetTartet(m_player->GetPosition(), m_player->GetQuaternion());

}



/**
 * @brief �X�V����
 *
 * @param[in] elapsedTime �O�t���[������̌o�ߎ���
 *
 * @return �Ȃ�
 */
void GameScene::Update(float elapsedTime)
{


	DirectX::Keyboard::KeyboardStateTracker* traker = Graphics::GetInstance()->GetKeyboardTracker();
	if (traker->pressed.Enter)
	{
		ChangeScene("Title", false);
	}
	m_player->Update(elapsedTime,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
	m_stage->Update(elapsedTime, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
	//m_camera->SetEyePos(m_player->GetModelParams().GetPosition() + DirectX::SimpleMath::Vector3(0.0f, 1.0f, 5.0f));
	m_enemyManager->Update();
	m_camera->Update(elapsedTime);


	if (m_stage->GetShape()->Intersects(m_player->GetShape()))
	{
		//�����o������
		m_player->SetPosition(m_cM->PushOut(dynamic_cast<Box*>(m_stage->GetShape()),dynamic_cast<Sphere*>( m_player->GetShape())));
		DirectX::SimpleMath::Vector3 v = m_player->GetVelocity();
		v.y = 0.0f;
		m_player->SetVelocity(v);
		auto debugFont = Graphics::GetInstance()->GetDebugFont();

		debugFont->AddString(TKTLib::StringToWchar(std::to_string(m_player->GetPosition().y)), DirectX::SimpleMath::Vector2(0.0f, 30.0f));

	}
}



/**
 * @brief �`�揈��
 *
 * @param[in] context
 * @param[in] states
 * @param[in] proj
 *
 * @return �Ȃ�
 */
void GameScene::Render()
{
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetView());
	//Graphics::GetInstance()->DrawPrimitiveBegin(m_camera->GetView(), Graphics::GetInstance()->GetProjectionMatrix());

	m_player->Draw();

	//m_player->GetShape()->AddDisplayCollision(m_displayCollision.get());
	m_enemyManager->Draw();
	m_stage->Draw();
	//m_stage->GetShape()->AddDisplayCollision(m_displayCollision.get());

	m_displayCollision->DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates(), Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());

	if (m_stage->GetShape()->Intersects(m_player->GetShape())) 
	{
		auto debugFont = Graphics::GetInstance()->GetDebugFont();

		debugFont->AddString(L"Hit", DirectX::SimpleMath::Vector2(0.0f, 20.0f));
	}

}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void GameScene::Finalize()
{
	m_player->Finalize();
	m_stage->Finalize();
	m_camera->Finalize();
	m_enemyManager->Finalize();

	Shader::GetInstance()->UnRegisterLight();
}

