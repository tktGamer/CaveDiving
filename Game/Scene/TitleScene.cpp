/**
 * @file   TitleScene.cpp
 *
 * @brief  タイトルシーンに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/28
 */
// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "TitleScene.h"
#include "Game/Common/ResourceManager.h"
#include"Game/Common/Sound.h"
#include"Game/UI/UIManager.h"
#include"../Scene/PlayScene.h"
#include "../Scene/LoadScene.h"
#include"../Scene/LogoScene.h"
#include"../Factory/UIFactory.h"
#include"../Factory/GameObjectFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
TitleScene::TitleScene()
	: 
	m_caveModelParams{},
	m_demoPlayer{},
	m_angle{},
	m_length{},
	m_isLoadPlayerHoldGem{false},
	m_skyModel{}
{
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
	UIManager::GetInstance()->ClearUI();
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	//音生成
	m_titleBGM = std::make_unique<Sound>(resourceManager->RequestSound(ResourcePath::SOUND::TITLE_BGM));
	m_titleBGM->Play(true);
	m_gemLoadSound = std::make_unique<Sound>(resourceManager->RequestSound(ResourcePath::SOUND::TITLE_GEM_LOAD));
	m_gameStartSound = std::make_unique<Sound>(resourceManager->RequestSound(ResourcePath::SOUND::GAME_START));


	//m_demoPlayer = GameObjectFactory::CreatePlayer(nullptr);
	//m_demoPlayer->SetPosition({ 0.0f,2.0f,7.0f });
	//m_demoPlayer->SetScale({ 0.5f,0.5f,0.5f });
	//m_demoPlayer->Update(DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
	//プレイヤー配置
	m_demoPlayerModelParams.SetModelParams(resourceManager->RequestModel(ResourcePath::MODEL::PLAYER));
	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3{ 0.0f,1.5f,6.5f };
	DirectX::SimpleMath::Vector3 rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f);
	m_demoPlayerModelParams.SetModelParams(position, rotation, scale);
	//洞窟配置
	m_caveModelParams.SetModelParams(resourceManager->RequestModel(ResourcePath::MODEL::TITLE_CAVE));
	 position = DirectX::SimpleMath::Vector3::Zero;
	 rotation = DirectX::SimpleMath::Vector3::Zero;
	 scale = DirectX::SimpleMath::Vector3::One;
	m_caveModelParams.SetModelParams(position, rotation, scale);

	m_length = 20.0f;
	m_angle = 20.0f;
	m_camera = std::make_unique<Camera>(CAMERA_INIT_POS);
	m_camera->Initialize();
	m_camera->SetTarget(m_caveModelParams.GetPosition(), m_caveModelParams.GetQuaternion());
	//スカイドームモデル生成
	m_skyModel = ResourceManager::GetInstance()->RequestModel(ResourcePath::MODEL::SKY_DOME);

	//UI生成
	UIManager* uiManager = UIManager::GetInstance();
	m_loadCheckUI = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::LOAD_GEM_CHECK,
		LOAD_CHECK_UI_POS, LOAD_CHECK_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER);
	m_checkUI     = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::CHECK,
		CHECK_MARK_UI_POS, CHECK_MARK_UI_SCALE,UserInterface::ANCHOR::MIDDLE_CENTER);
	uiManager->RequestAddUI( UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::TITLE,
		TITLE_UI_POS, TITLE_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));
	uiManager->RequestAddUI( UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::PRESS_SPACE,
		PRESS_SPACE_UI_POS, PRESS_SPACE_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));

	//プレイヤーのデータを初期化
	GetGameData()->SetPlayerData(GameData::PlayerData{});

	PreUpdate();
	m_time = 0.0f;
}

/**
 * @brief 事前更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
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
		ChangeScene<PlayScene,LoadScene>();
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

	m_camera->Update(elapsedTime);

	m_time += elapsedTime;

	//一定時間経過でロゴシーンへ
	if (m_time > 15.0f) 
	{
		ChangeScene<LogoScene>();
	}
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
	//天球
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
	m_skyModel->Draw(context, *states,world, view, proj);

	
	//UI描画	
	m_loadCheckUI->Draw();
	if (m_isLoadPlayerHoldGem) 
	{
		m_checkUI->Draw();
	}
	UIManager::GetInstance()->Render();
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
