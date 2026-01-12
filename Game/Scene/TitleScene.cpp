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
#include"Game/Common/Sound.h"
#include"../Scene/GameScene.h"
#include "../Scene/LoadScene.h"

#include"../Factory/UIFactory.h"
#include"../Factory/GameObjectFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
TitleScene::TitleScene()
	: m_pResourceManager{}
	, m_caveModelParams{}
	, m_demoPlayer{}
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
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	m_titleBGM = std::make_unique<Sound>(m_pResourceManager->RequestSound("titlebgm.wav"));
	m_titleBGM->Play(true);
	m_gemLoadSound = std::make_unique<Sound>(m_pResourceManager->RequestSound("titlegemload.wav"));
	m_gameStartSound = std::make_unique<Sound>(m_pResourceManager->RequestSound("gamestart.wav"));


	//m_demoPlayer = GameObjectFactory::CreatePlayer(nullptr);
	//m_demoPlayer->SetPosition({ 0.0f,2.0f,7.0f });
	//m_demoPlayer->SetScale({ 0.5f,0.5f,0.5f });
	//m_demoPlayer->Update(DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);

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

	m_length = 20.0f;
	m_angle = 20.0f;
	m_camera->Initialize({ 0,17.0f,10.0f });
	m_camera->SetTartet(m_caveModelParams.GetPosition(), m_caveModelParams.GetQuaternion());

	m_skyModel = ResourceManager::GetInstance()->RequestModel("skydome.sdkmesh");

	m_loadCheckUI = UIFactory::CreateUserInterface(L"UI/loadgemcheck.png", { 200,400 }, { 0.8f,0.8f },UserInterface::ANCHOR::MIDDLE_CENTER);
	m_checkUI = UIFactory::CreateUserInterface(L"UI/check.png", { 200,400 }, { 0.8f,0.8f },UserInterface::ANCHOR::MIDDLE_CENTER);
	m_title = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::TITLE, {640.0f,180.0f}, {1.0f,1.0f}, UserInterface::ANCHOR::MIDDLE_CENTER);
	m_pressSpace = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::PRESS_SPACE, { 640.0f,600.0f }, { 1.0f,1.0f }, UserInterface::ANCHOR::MIDDLE_CENTER);
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	//プレイヤーのデータを初期化
	GetGameData()->SetPlayerData(GameData::PlayerData{});

	PreUpdate();
}

void TitleScene::PreUpdate()
{
	float radian =DirectX::XMConvertToRadians(m_angle);

	m_camera->SetEyePos(DirectX::SimpleMath::Vector3{ m_length * std::cos(radian), 15.0f, m_length * std::sin(radian) });
	m_angle += 10.0f * Messenger::GetInstance()->GetElapsedTime();

	m_camera->Update(Messenger::GetInstance()->GetElapsedTime());
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
		GameData* gameData = GetGameData();
		GameData::PlayerData playerData;
		if (m_isLoadPlayerHoldGem) 
		{
			//保存されたプレイヤーの所持宝石のIDを入手
			GemManager::GetInstance()->LoadHoldGem(ResourcePath::DATA::HOLDER_GEM::PLAYER_GEM,playerData.gemID);
		}
		//HP設定
		playerData.currentHP = Player::PLAYER_BASE_HP;
		playerData.maxHP = Player::PLAYER_BASE_HP;
		//プレイヤーの情報を設定
		gameData->SetPlayerData(playerData);
		//スタート音再生
		m_gameStartSound->Play(false);
		GetGameData()->SetNextStage(GameData::Stage::FIRST);
		GetGameData()->SetIsGameClear(false);
		ChangeScene<GameScene,LoadScene>();
	}

	if (traker->pressed.Z) 
	{
		//保存されている宝石の読み込みON・OFF
		m_isLoadPlayerHoldGem = !m_isLoadPlayerHoldGem;
		m_gemLoadSound->Play(false);
	}

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
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetView());

	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix proj = graphics->GetProjectionMatrix();

	//m_testPlayer.Draw(*context, *states, view, proj);
	DirectX::SimpleMath::Matrix world;
	m_demoPlayerModelParams.GetModel()->Draw(context, *states, m_demoPlayerModelParams.GetWorldMatrix(), view, proj);
	m_caveModelParams.GetModel()->Draw(context, *states, m_caveModelParams.GetWorldMatrix(), view, proj);
	//m_demoPlayer->Draw();

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
	
	

	m_loadCheckUI->Render();
	if (m_isLoadPlayerHoldGem) 
	{
		m_checkUI->Render();
	}
	m_title->Render();
	m_pressSpace->Render();

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
	m_titleBGM->Stop();
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
