/**
 * @file   GameScene.cpp
 *
 * @brief  ゲームシーンに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/03
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GameScene.h"
#include"../Scene/TitleScene.h"
#include"../Scene/GemSelectScene.h"
#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"
#include"Game/Scene/ResultScene.h"

#include"Game/Common/Collision/Sphere.h"
#include"../Fuctory/UIFactory.h"
#include"../Fuctory/GameObjectFactory.h"
#include"Game/Particle/ParticleManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
GameScene::GameScene()
	:  m_pResourceManager{}
{
	TKTLib::ModelParams modelParams;

	m_pResourceManager = ResourceManager::GetInstance();

	m_displayCollision = std::make_unique<Ito::DisplayCollision>(
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());

	m_cM = CollisionManager::GetInstance();
}



/**
 * @brief デストラクタ
 */
GameScene::~GameScene()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameScene::Initialize()
{
	Messenger::GetInstance()->DestroyInstance();

	UserResources* gameData = GetGameData();

	m_gameBGM = std::make_unique<Sound>(m_pResourceManager->RequestSound("gamebgm.wav"));
	m_gameBGM->Play(true);


	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);


	m_buffUI = std::make_unique<BuffUIControl>(w, h);
	m_buffUI->Initialize();



	m_camera = std::make_unique<Camera>();
	m_player = GameObjectFactory::CreatePlayer(m_buffUI.get(), nullptr, DirectX::SimpleMath::Vector3{0.0f,1.0f,0.0f});
	
	m_stage =GameObjectFactory::CreateStage(nullptr, DirectX::SimpleMath::Vector3{ 0.0f,-2.0f,0.0f },DirectX::SimpleMath::Quaternion::Identity
											,GetGameData()->GetIsOnLights(),10);

	if (gameData->GetNextStage() == UserResources::Stage::FIRST) 
	{
		m_enemyManager = std::make_unique<EnemyManager>();
		m_enemyManager->Spawn();
	}
	if (gameData->GetNextStage() == UserResources::Stage::BOSS) 
	{
		m_enemyManager = std::make_unique<EnemyManager>();
		m_enemyManager->SpawnBoss();
	}
	m_camera->Initialize({ 0,1.0f,25.0f });
	m_camera->SetDistance(DirectX::SimpleMath::Vector3{ 0.0f, 7.0f, 25.0f });
	//m_stage->Initialize();

	m_camera->SetTartet(m_player->GetCurrentPosition(), m_player->GetQuaternion());

	//m_cM->Register(m_stage.get());
	m_cM->Register(m_player.get());
	m_itemManager = std::make_unique<ItemManager>();
	m_itemManager->Initialize();


	m_hpGauge = UIFactory::CreateGauge();
	m_hpGauge->SetValue(m_player->GetCurrentHP(), m_player->GetMaxHP());

	m_holdGem = UIFactory::CreateHoldGem();

	ParticleManager::GetInstance()->SetCamera(m_camera.get());

	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}



/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime 前フレームからの経過時間
 *
 * @return なし
 */
void GameScene::Update(float elapsedTime)
{
	m_hpGauge->Update();
	m_holdGem->Update();
	m_buffUI->Update();

	auto traker = Graphics::GetInstance()->GetKeyboardTracker();

	 std::list<std::unique_ptr<Character>>& enemies =  m_enemyManager->GetEnemies();
	if (traker->pressed.Q || enemies.size()==0)
	{
		ParticleManager::GetInstance()->Reset();
		if (GetGameData()->GetNextStage()==UserResources::Stage::BOSS) 
		{
			SaveLight();
			GetGameData()->SetIsGameClear(true);
			ChangeScene<ResultScene>();
			return;
		}
		GetGameData()->SetNextStage(UserResources::Stage::BOSS);
		ChangeScene<GemSelectScene>();
	}
	else if (!m_player->IsAlive()) 
	{
		GetGameData()->SetIsGameClear(false);
		ChangeScene<ResultScene>();
	}

	m_player->Update(elapsedTime,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
	m_stage->Update(elapsedTime, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);

	//m_camera->SetEyePos(m_player->GetModelParams().GetPosition() + DirectX::SimpleMath::Vector3(0.0f, 1.0f, 5.0f));
	m_enemyManager->Update();
	m_camera->Update(elapsedTime);

	//m_player->Damage(2);
	m_hpGauge->SetValue(m_player->GetCurrentHP(), m_player->GetMaxHP());

	m_itemManager->Update();

	m_cM->CollisionCheck();

	ParticleManager::GetInstance()->Update();

}



/**
 * @brief 描画処理
 *
 * @param[in] context
 * @param[in] states
 * @param[in] proj
 *
 * @return なし
 */
void GameScene::Render()
{
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetView());
	//Graphics::GetInstance()->DrawPrimitiveBegin(m_camera->GetView(), Graphics::GetInstance()->GetProjectionMatrix());

	m_player->Draw();

	//m_player->GetShape()->AddDisplayCollision(m_displayCollision.get());
	m_stage->Draw();
	m_enemyManager->Draw();
	//m_stage->GetShape()->AddDisplayCollision(m_displayCollision.get());
	m_itemManager->Draw();

	//m_displayCollision->DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates(), Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());

	m_hpGauge->Render();
	m_holdGem->Render();
	m_buffUI->Render();

	ParticleManager::GetInstance()->Render();
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameScene::Finalize()
{
	m_cM->AllRelease();
	m_player->Finalize();
	m_stage->Finalize();
	m_camera->Finalize();
	m_enemyManager->Finalize();

	m_gameBGM->Stop();
	GameObject::ResetObjectNumber();

	Shader::GetInstance()->UnRegisterLight();
}

void GameScene::CreateDeviceDependentResources()
{
	//std::this_thread::sleep_for(std::chrono::seconds{ 3 });
}

void GameScene::CreateWindowSizeDependentResources()
{
}

void GameScene::OnDeviceLost()
{
}

void GameScene::SaveLight()
{
	//ステージのライトを取得
	auto& rock = m_stage->GetRocks();
	//配列番号
	int index = 0;
	for (std::list<std::unique_ptr<CandleStick>>::iterator it =rock.begin(); it != rock.end(); ++it) 
	{


		//ライトのオン・オフを記録
		GetGameData()->SetIsOnLightNumber(it->get()->IsOnLight(), index);
		index++;
	}
}

