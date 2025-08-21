/**
 * @file   TitleScene.cpp
 *
 * @brief  ロゴシーンに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "TitleScene.h"

#include "Game/Common/ResourceManager.h"

#include"../Scene/GameScene.h"
#include "../Scene/LoadScene.h"


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
TitleScene::TitleScene()
	: m_pResourceManager{}
	, m_caveModelParams{}
	, m_demoPlayerModelParams{}
	, m_angle{}
	, m_length{}
{
	m_camera = std::make_unique<Camera>();
	m_pResourceManager = ResourceManager::GetInstance();


}



/**
 * @brief デストラクタ
 */
TitleScene::~TitleScene()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void TitleScene::Initialize()
{

	m_titleTexture = *m_pResourceManager->RequestTexture("title.png");
	m_pressSpaceTexture = *m_pResourceManager->RequestTexture("pressspace.png");
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
	m_camera->SetTartet(m_caveModelParams.GetPosition(), m_caveModelParams.GetQuaternion());
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();


}



/**
 * @brief 更新処理
 *
 * @param[in] inputDevice 入力デバイス
 *
 * @return なし
 */
void TitleScene::Update(float elapsedTime)
{
	auto traker = Graphics::GetInstance()->GetKeyboardTracker();
	float r = m_angle * 3.14f / 180.0f;
	
	if (traker->pressed.Space)
	{
		ChangeScene<GameScene,LoadScene>();
	}
	/*m_camera->SetEyePosX(m_length * std::cos(r));
	m_camera->SetEyePosZ(m_length * std::sin(r));*/
	m_camera->SetDistance(DirectX::SimpleMath::Vector3{ m_length * std::cos(r), 17.0f, m_length * std::sin(r) });
	m_angle += 10.0f*elapsedTime;
	if (m_angle >= 360.0f)
	{
		m_angle = 0.0f;
	}

	//m_gem->Update();
	m_camera->Update(elapsedTime);
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void TitleScene::Render()
{
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix proj = graphics->GetProjectionMatrix();

	auto view=m_camera->GetView();
	//m_testPlayer.Draw(*context, *states, view, proj);
	DirectX::SimpleMath::Matrix world;
	m_demoPlayerModelParams.GetModel()->Draw(context, *states, m_demoPlayerModelParams.GetWorldMatrix(), view, proj);
	m_caveModelParams.GetModel()->Draw(context, *states, m_caveModelParams.GetWorldMatrix(), view, proj);

	DirectX::SpriteBatch* spriteBatch = graphics->GetSpriteBatch();

	spriteBatch->Begin();
	spriteBatch->Draw(m_titleTexture, DirectX::SimpleMath::Vector2(400, 100));
	spriteBatch->Draw(m_pressSpaceTexture, DirectX::SimpleMath::Vector2(400, 550));

	
	spriteBatch->End();

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void TitleScene::Finalize()
{
	
}

void TitleScene::CreateDeviceDependentResources()
{
}

void TitleScene::CreateWindowSizeDependentResources()
{
}

void TitleScene::OnDeviceLost()
{
}
