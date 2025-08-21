/**
 * @file   GameScene.cpp
 *
 * @brief  Xシーンに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GameScene.h"
#include"../Scene/TitleScene.h"
#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"


#include"Game/Common/Collision/Sphere.h"

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


	m_camera = std::make_unique<Camera>();
	m_player = std::make_unique<Player>(nullptr,DirectX::SimpleMath::Vector3{0.0f,1.0f,0.0f},DirectX::XMConvertToRadians(0.0f));
	m_player->Initialize();
	m_stage = std::make_unique<Stage>(nullptr, DirectX::SimpleMath::Vector3{ 0.0f,-2.0f,0.0f }, DirectX::XMConvertToRadians(0.0f));
	m_enemyManager = std::make_unique<EnemyManager>();
	m_enemyManager->Spawn();
	m_camera->Initialize({ 0,1.0f,25.0f });
	m_camera->SetDistance(DirectX::SimpleMath::Vector3{ 0.0f, 7.0f, 25.0f });
	m_stage->Initialize();

	m_camera->SetTartet(m_player->GetPosition(), m_player->GetQuaternion());

	m_cM->Register(m_stage.get());
	m_cM->Register(m_player.get());


	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);
	m_gemSelectUI = std::make_unique<GemSelect>();
	m_gemSelectUI->Initialize(w,h);
	m_gemSelectUI->Randomize();

	m_hpGauge = std::make_unique<Gauge>();
	m_hpGauge->Initialize(w, h);
	m_hpGauge->SetValue(m_player->GetCurrentHP(), m_player->GetMaxHP());

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
	m_gemSelectUI->Update();
	m_hpGauge->Update();

	auto traker = Graphics::GetInstance()->GetKeyboardTracker();

	 std::list<std::unique_ptr<GameObject>>& enemies =  m_enemyManager->GetEnemies();
	if (traker->pressed.Enter || enemies.size()==0)
	{
		ChangeScene<TitleScene>();
	}
	m_player->Update(elapsedTime,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
	m_stage->Update(elapsedTime, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
	//m_camera->SetEyePos(m_player->GetModelParams().GetPosition() + DirectX::SimpleMath::Vector3(0.0f, 1.0f, 5.0f));
	m_enemyManager->Update();
	m_camera->Update(elapsedTime);

	m_player->Damage(6);

	m_cM->CollisionCheck();
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
	m_enemyManager->Draw();
	m_stage->Draw();
	//m_stage->GetShape()->AddDisplayCollision(m_displayCollision.get());

	m_displayCollision->DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates(), Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());

	m_gemSelectUI->Render();
	m_hpGauge->Render();

	if (m_stage->GetShape()->Intersects(m_player->GetShape())) 
	{
		auto debugFont = Graphics::GetInstance()->GetDebugFont();

		debugFont->AddString(L"Hit", DirectX::SimpleMath::Vector2(0.0f, 20.0f));
	}

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

