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

#include"../Fuctory/UIFactory.h"
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
	,m_isLoadPlayerHoldGem{false}
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
	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3{ 0.0f,1.5f,6.5f };
	DirectX::SimpleMath::Vector3 rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f);
	m_demoPlayerModelParams.SetModelParams(position, rotation, scale);
	m_caveModelParams.SetModelParams(m_pResourceManager->RequestModel("cave.sdkmesh"));
	position = DirectX::SimpleMath::Vector3::Zero;
	rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	m_caveModelParams.SetModelParams(position, rotation, scale);

	m_length = 25.0f;
	m_angle = 0.0f;
	m_camera->Initialize({ 0,11.0f,10.0f });
	m_camera->SetTartet(m_caveModelParams.GetPosition(), m_caveModelParams.GetQuaternion());

	m_skyModel = ResourceManager::GetInstance()->RequestModel("skydome.sdkmesh");

	m_loadCheckUI = UIFactory::CreateUserInterface(L"UI/loadgemcheck.png", { 200,400 }, { 0.8f,0.8f },UserInterface::ANCHOR::MIDDLE_CENTER);
	m_checkUI = UIFactory::CreateUserInterface(L"UI/check.png", { 200,400 }, { 0.8f,0.8f },UserInterface::ANCHOR::MIDDLE_CENTER);
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();


	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	m_light.SetWindowSize(w, h);
	m_light.Create(L"illustkun-04373-flashlight.png", { 1050.0f,500.0f }, { 0.9f,0.9f }, UserInterface::MIDDLE_CENTER);

	//プレイヤーの所持している宝石を空にする
	GemManager::GetInstance()->EmptyPlayerHoldGem();
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void TitleScene::Update(float elapsedTime)
{
	auto traker = Graphics::GetInstance()->GetKeyboardTracker();
	float r = m_angle * 3.14f / 180.0f;
	
	if (traker->pressed.Space)
	{
		if (m_isLoadPlayerHoldGem) 
		{
			GemManager::GetInstance()->LoadPlayerHoldGem();
		}

		GetGameData()->SetNextStage(UserResources::Stage::BOSS);
		ChangeScene<GameScene,LoadScene>();
	}

	if (traker->pressed.Z) 
	{
		//保存されている宝石の読み込みON・OFF
		m_isLoadPlayerHoldGem = !m_isLoadPlayerHoldGem;

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

	DirectX::SimpleMath::Vector3 cameraPos = m_camera->GetEyePos();
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(cameraPos);
	DirectX::SimpleMath::Matrix  scale = DirectX::SimpleMath::Matrix::CreateScale(20.0f);
	world = scale * DirectX::SimpleMath::Matrix::CreateTranslation(m_caveModelParams.GetPosition());
	m_skyModel->UpdateEffects([](DirectX::IEffect* effect)
		{
			auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);

			if (lights)
			{
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}


			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				//自己発行色
				basicEffect->SetEmissiveColor(DirectX::Colors::White);
			}
		}
	);

	//world = scale * trans;
	m_skyModel->Draw(context, *states,world, view, proj);
	world = scale *DirectX::SimpleMath::Matrix::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX,DirectX::XMConvertToRadians(180.0f)) 
		*trans;
	//m_skyModel->Draw(context, *states,world, view, proj);

	trans = DirectX::SimpleMath::Matrix::CreateTranslation({0.0f,-1.0f,0.0f});

	scale = DirectX::SimpleMath::Matrix::CreateScale({40.0f,1.0f,40.0f});
	world = scale * trans;

	//m_groundModel->Draw(context, *states, world, view, proj);
	
	//m_light.Draw();
	
	DirectX::SpriteBatch* spriteBatch = graphics->GetSpriteBatch();

	m_loadCheckUI->Draw();
	if (m_isLoadPlayerHoldGem) 
	{
		m_checkUI->Draw();
	}
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
