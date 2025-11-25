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
#include"Game/Scene/ResultScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"

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

	GameData* gameData = GetGameData();

	//ゲーム中のBGM再生
	m_gameBGM = std::make_unique<Sound>(m_pResourceManager->RequestSound("gamebgm.wav"));
	m_gameBGM->SetVolume(0.8f);
	m_gameBGM->Play(true);


	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	//バフUI管理クラスの生成
	m_buffUI = std::make_unique<BuffUIControl>(w, h);
	m_buffUI->Initialize();


	//オブジェクトの生成--
	//プレイヤーの生成
	m_player = GameObjectFactory::CreatePlayer(m_buffUI.get(), nullptr, DirectX::SimpleMath::Vector3{ 0.0f,1.0f,0.0f });
	m_cM->Register(m_player.get());

	//ステージの生成
	m_stage = GameObjectFactory::CreateStage(nullptr, DirectX::SimpleMath::Vector3{ 0.0f,-2.0f,0.0f }, DirectX::SimpleMath::Quaternion::Identity
		, GetGameData()->GetIsOnLights(), 10);

	//敵の生成
	m_enemyManager = std::make_unique<EnemyManager>();
	if (gameData->GetNextStage() == GameData::Stage::FIRST)
	{
		m_enemyManager->Spawn();
	}
	if (gameData->GetNextStage() == GameData::Stage::BOSS)
	{
		m_enemyManager->SpawnBoss();
	}

	//カメラの生成
	m_camera = std::make_unique<Camera>();
	m_camera->Initialize({ 0,1.0f,25.0f });
	m_camera->SetDistance(DirectX::SimpleMath::Vector3{ 0.0f, 7.0f, 25.0f });
	m_camera->SetTartet(m_player->GetCurrentPosition(), m_player->GetQuaternion(), m_player->GetVelocity());

	//アイテム管理クラスの生成
	m_itemManager = std::make_unique<ItemManager>();
	m_itemManager->Initialize();

	//HPゲージUIの生成
	m_hpGauge = UIFactory::CreateGauge();
	m_hpGauge->SetValue(m_player->GetCurrentHP(), m_player->GetMaxHP());
	//所持宝石UIの生成
	m_holdGem = UIFactory::CreateHoldGem();

	m_clearConditionsUI = std::make_unique<ClearConditions>(DirectX::SimpleMath::Vector2{ 1240,150 });
	m_clearConditionsUI->Initialize(w, h);
	ParticleManager::GetInstance()->SetCamera(m_camera.get());
	Sound::SetListenerObject(m_player.get());

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
	auto traker = Graphics::GetInstance()->GetKeyboardTracker();
	//UIの更新
	m_hpGauge->Update();
	m_holdGem->Update();
	m_buffUI->Update();

	std::list<std::unique_ptr<Character>>& enemies = m_enemyManager->GetEnemies();
	m_clearConditionsUI->Update(enemies.size());

	//ゲームクリア・ゲームオーバー判定
	if (traker->pressed.Q || enemies.size() == 0)
	{
		ParticleManager::GetInstance()->Reset();
		if (GetGameData()->GetNextStage() == GameData::Stage::BOSS)
		{
			//SaveLight();
			GetGameData()->SetIsGameClear(true);
			ChangeScene<GemSelectScene>();
			return;
		}
		GetGameData()->SetNextStage(GameData::Stage::BOSS);
		//ステージのライト状況を保存
		SaveLight();
		ChangeScene<GemSelectScene>();
	}
	else if (!m_player->IsAlive()) 
	{
		GetGameData()->SetIsGameClear(false);
		ChangeScene<ResultScene>();
	}

	//オブジェクトの更新--
	m_player->Update(DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
	m_stage->Update(DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);

	//m_camera->SetEyePos(m_player->GetModelParams().GetPosition() + DirectX::SimpleMath::Vector3(0.0f, 1.0f, 5.0f));
	m_enemyManager->Update();
	m_camera->Update(elapsedTime);

	//HPゲージの更新
	m_hpGauge->SetValue(m_player->GetCurrentHP(), m_player->GetMaxHP());

	m_itemManager->Update();

	//衝突判定
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

	ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//設定情報を取得
	auto renderTarget = Graphics::GetInstance()->GetDeviceResources()->GetRenderTargetView();
	auto depthStencil = Graphics::GetInstance()->GetDeviceResources()->GetDepthStencilView();
	auto offScreenRTV = m_offScreenRT->GetRenderTargetView();
	auto offScreenSRV = m_offScreenRT->GetShaderResourceView();

	// 画面のサイズを取得
	RECT rect = Graphics::GetInstance()->GetDeviceResources()->GetOutputSize();


	//レンダーターゲットを変更----------------
	context->ClearRenderTargetView(offScreenRTV, DirectX::Colors::Black);
	context->ClearDepthStencilView(
		depthStencil,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, //フラグ　　デプスとステンシルのクリア
		1.0f,
		0);
	context->OMSetRenderTargets(1, &offScreenRTV, depthStencil);

	//---------------------------------------------------------------------------//
	//ブラーするオブジェクトの描画
	//---------------------------------------------------------------------------//

	m_stage->Draw();


	//Pass1 offScreenSRVをもとにblur1RTV blur1SRVに明るい部分を抽出する----------------------------------------

	//レンダーターゲットを切り替えると絵の出力先が変わる
	auto blur1RTV = m_blur1RT->GetRenderTargetView();
	auto blur1SRV = m_blur1RT->GetShaderResourceView();

	//切り替え
	context->OMSetRenderTargets(1, &blur1RTV, nullptr);

	D3D11_VIEWPORT vp_blur = { 0.0f,0.0f,rect.right / 2.0f,rect.bottom / 2.0f,0.0f,1.0f };
	context->RSSetViewports(1, &vp_blur);

	//抽出
	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::BloomExtract);
	m_basicPostProcess->SetBloomExtractParameter(0.25f);
	m_basicPostProcess->SetSourceTexture(offScreenSRV);//レンダーターゲットをソースにして作成
	m_basicPostProcess->Process(context);
	//----------------------------------------

	//Pass2 blur1SRVをもとにblur2RTV(blur2SRV)に横にぶれた画像を作成する-----------------
	auto blur2RTV = m_blur2RT->GetRenderTargetView();
	auto blur2SRV = m_blur2RT->GetShaderResourceView();
	//切り替え
	context->OMSetRenderTargets(1, &blur2RTV, nullptr);

	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::Effect::BloomBlur);
	m_basicPostProcess->SetBloomBlurParameters
	(	
		true,//横のぼかしができる
		4.0f,	//ぼかしの量
		1.0f	//明るさ 1 => 元の画像の明るさ
	);

	m_basicPostProcess->SetSourceTexture(blur1SRV);
	m_basicPostProcess->Process(context);

	//------------------------------------------------------

	//Pass3 blur2SRVをもとにblur1RTV(blur1SRV)に縦にぶれた画像を作成する-----------------
	//切り替え
	context->OMSetRenderTargets(1, &blur1RTV, nullptr);

	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::Effect::BloomBlur);
	m_basicPostProcess->SetBloomBlurParameters
	(
		false,//横のぼかしができる
		4.0f,	//ぼかしの量
		1.0f	//明るさ 1 => 元の画像の明るさ
	);

	m_basicPostProcess->SetSourceTexture(blur2SRV);
	m_basicPostProcess->Process(context);


	// -------------------------------------------------------------------------- //
	// レンダーターゲットとビューポートを元に戻す
	// -------------------------------------------------------------------------- //
	//auto renderTarget = Graphics::GetInstance()->GetDeviceResources()->GetRenderTargetView();
	//auto depthStencil = Graphics::GetInstance()->GetDeviceResources()->GetDepthStencilView();


	context->ClearRenderTargetView(renderTarget, DirectX::Colors::Black);
	context->ClearDepthStencilView(depthStencil, /*D3D11_CLEAR_DEPTH |*/ D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);
	//-----------------------------------------------------
	// ビューポートを元に戻す
	//-----------------------------------------------------
	auto const viewport = Graphics::GetInstance()->GetDeviceResources()->GetScreenViewport();
	context->RSSetViewports(1, &viewport);




	//Pass4 offScreenSRVとblur1STVをもとにぼかした画像を作成する-----------------
	m_dualPostProcess->SetEffect(DirectX::DualPostProcess::BloomCombine);
	m_dualPostProcess->SetBloomCombineParameters
	(
		1.25f,//合成される光　明るさ
		1.0f,
		0.0f,//ライト　彩度
		1.0f//白っぽくなる
	);

	m_dualPostProcess->SetSourceTexture(offScreenSRV);
	m_dualPostProcess->SetSourceTexture2(blur1SRV);//追加するもの

	m_dualPostProcess->Process(context);


	//------------------------------------------------------
		//---------------------------------------------------------------------------//
	//通常描画
	//---------------------------------------------------------------------------//


	m_player->Draw();

	//m_player->GetShape()->AddDisplayCollision(m_displayCollision.get());
	m_enemyManager->Draw();
	//m_stage->GetShape()->AddDisplayCollision(m_displayCollision.get());
	m_itemManager->Draw();

	//m_displayCollision->DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates(), Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());

	m_hpGauge->Render();
	m_holdGem->Render();
	m_buffUI->Render();
	m_clearConditionsUI->Render();

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
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//レンダーテクスチャの作成
	m_offScreenRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R8G8B8A8_UNORM);//画像の保存形式の指定
	m_offScreenRT->SetDevice(device);
	RECT rect = Graphics::GetInstance()->GetDeviceResources()->GetOutputSize();
	m_offScreenRT->SetWindow(rect);


	//ベーシックエフェクト作成
	m_basicPostProcess = std::make_unique<DirectX::BasicPostProcess>(device);

	//レンダーテクスチャの作成
	//画面サイズを半分にする
	rect.right /= 2.0f;
	rect.bottom /= 2.0f;

	//ブラーの作成
	m_blur1RT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R8G8B8A8_UNORM);
	m_blur1RT->SetDevice(device);
	m_blur1RT->SetWindow(rect);

	m_blur2RT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R8G8B8A8_UNORM);
	m_blur2RT->SetDevice(device);
	m_blur2RT->SetWindow(rect);

	//デュアルポストプロセスの作成
	m_dualPostProcess = std::make_unique<DirectX::DualPostProcess>(device);
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

