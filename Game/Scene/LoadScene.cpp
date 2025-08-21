/**
 * @file   LoadScene.cpp
 *
 * @brief  ���[�h�V�[���Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "LoadScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"




// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
LoadScene::LoadScene()
	: m_pResourceManager{}
	,m_nowloadingRect{0,0,590,250}
	, m_nowloadingTexture{}
	, m_backTexture{}
	, m_time{}
{
	m_camera = std::make_unique<Camera>();
	m_pResourceManager = ResourceManager::GetInstance();
}



/**
 * @brief �f�X�g���N�^
 */
LoadScene::~LoadScene()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void LoadScene::Initialize()
{
	m_nowloadingTexture = *m_pResourceManager->RequestTexture("loading.png");
	m_backTexture = *m_pResourceManager->RequestTexture("loadback.jpg");
	//m_camera->Initialize({ 0,11.0f,10.0f });

	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}



/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void LoadScene::Update(float elapsedTime)
{
	DirectX::Keyboard::KeyboardStateTracker* traker = Graphics::GetInstance()->GetKeyboardTracker();
	
	/*m_camera->SetEyePosX(m_length * std::cos(r));
	m_camera->SetEyePosZ(m_length * std::sin(r));*/

	m_time += elapsedTime;
	if (m_time >= 0.8f) 
	{
		m_time = 0.0f;
		m_nowloadingRect.right += 35;
	}

	//m_camera->Update(elapsedTime);
}



/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void LoadScene::Render()
{
	Graphics* graphics = Graphics::GetInstance();

	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix proj = graphics->GetProjectionMatrix();

	//auto view=m_camera->GetView();
	//m_testPlayer.Draw(*context, *states, view, proj);
	DirectX::SimpleMath::Matrix world;

	DirectX::SpriteBatch* spriteBatch = graphics->GetSpriteBatch();
	RECT rc = { 0, 0, 695, 250 };
	RECT rc2 = { 0, 0, 1920,1080 };
	spriteBatch->Begin();
	spriteBatch->Draw(m_backTexture,
					  DirectX::SimpleMath::Vector2(0, 0),
					  &rc2,
					  DirectX::Colors::White,
					  0.0f,
					  DirectX::SimpleMath::Vector2(0, 0),
					  0.7f);
	spriteBatch->Draw(m_nowloadingTexture, DirectX::SimpleMath::Vector2(540, 500),&m_nowloadingRect);
	spriteBatch->End();

	auto debugFont = Graphics::GetInstance()->GetDebugFont();

	debugFont->AddString(TKTLib::StringToWchar(std::to_string(m_time)), DirectX::SimpleMath::Vector2(0.0f, 25.0f));

}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void LoadScene::Finalize()
{
	
}

void LoadScene::CreateDeviceDependentResources()
{
}

void LoadScene::CreateWindowSizeDependentResources()
{
}

void LoadScene::OnDeviceLost()
{
}
