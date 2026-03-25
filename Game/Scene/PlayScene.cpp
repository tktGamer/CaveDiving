/**
 * @file   GameScene.cpp
 *
 * @brief  ゲームシーンに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/25
 */
// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include<fstream>
#include<sstream>
#include "PlayScene.h"
#include"../Scene/TitleScene.h"
#include"../Scene/GemSelectScene.h"
#include"Game/Scene/ResultScene.h"
#include"Game/UI/UIManager.h"
#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"
#include"Game/Shader/ShaderManager.h"
#include"Game/Common/Collision/Sphere.h"
#include"../Factory/UIFactory.h"
#include"../Factory/GameObjectFactory.h"
#include"Game/Particle/ParticleManager.h"
#include"Game/Command/Move/MoveFrontCommand.h"
#include"Game/Command/Move/MoveBackCommand.h"
#include"Game/Command/Move/MoveLeftCommand.h"
#include"Game/Command/Move/MoveRightCommand.h"
#include"Game/Command/Move/JumpCommand.h"
#include"Game/Command/Attack/AttackCommand.h"
#include"Game/Command/Avoid/AvoidCommand.h"
#include"Game/Command/Move/RotationCommand.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
PlayScene::PlayScene()
	:
	m_objects{},
	m_renderPipeLine{},
	m_player{},
	m_camera{},
	m_enemyManager{},
	m_itemManager{}

{
	//当たり判定表示クラス
	m_displayCollision = std::make_unique<Ito::DisplayCollision>(
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());
	//当たり判定管理クラス
	m_collsionManager = CollisionManager::GetInstance();
}



/**
 * @brief デストラクタ
 */
PlayScene::~PlayScene()
{
	UIManager::GetInstance()->ClearUI();
}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayScene::Initialize()
{
	//メッセンジャーリセット
	Messenger::GetInstance()->DestroyInstance();
	m_objects.clear();
	m_renderPipeLine = std::make_unique<RenderPipeLine>();
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
	//キー入力管理生成
	CreateInputCommand();
	//バフUI管理クラスの生成
	m_buffUI = std::make_unique<BuffUIControl>(UIManager::WINDOW_SIZE_X, UIManager::WINDOW_SIZE_Y);
	m_buffUI->Initialize();
	//オブジェクトの生成
	CreateObjects();
	//UI生成
	CreateUI();
	//パーティクルマネージャーにカメラをセット
	ParticleManager::GetInstance()->SetCamera(m_camera.get());
	//操作するオブジェクトを設定する
	Messenger::GetInstance()->SetOperateObject(m_player->GetObjectNumber());

	//初期時更新処理
	PreUpdate();
}


/**
 * @brief 初期時更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayScene::PreUpdate()
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();

	//UIの更新
	m_buffUI->Update();
	UIManager::GetInstance()->Update();
	
	//オブジェクトの更新--
	for (auto& object : m_objects)
	{
		object->Update(DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
	}

	m_camera->Update(elapsedTime);


	//衝突判定
	m_collsionManager->CollisionCheck();

	//ゲーム中のBGM再生
	m_gameBGM = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::GAME_BGM));
	m_gameBGM->SetVolume(0.8f);
	m_gameBGM->Play(true);
}

/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime 前フレームからの経過時間
 *
 * @return なし
 */
void PlayScene::Update(float elapsedTime)
{
	//ゲームクリア・ゲームオーバー判定
	if (IsFinish()) 
	{
		return;
	}

	//キーボード入力処理
	m_inputHandler->Update(Messenger::GetInstance()->GetOperateObjectID());
	//オブジェクトの更新--
	for(auto& object : m_objects)
	{
		object->Update(DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
	}
	m_camera->Update(elapsedTime);

	//UIの更新
	m_clearConditionsUI->Update(m_enemyManager->GetEnemyCount());
	m_buffUI->Update();
	UIManager::GetInstance()->Update();

	//衝突判定
	m_collsionManager->CollisionCheck();
	//パーティクルの更新
	ParticleManager::GetInstance()->Update();
	//経過時間を記録  スコアのため
	GetGameData()->AddTime(elapsedTime);
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayScene::Render()
{
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetView());

	WallShader::CameraToPlayerCB cameraToPlayerCB;
	cameraToPlayerCB.cameraPos = m_camera->GetEyePos();
	cameraToPlayerCB.fadeRadius = 10.0f;
	cameraToPlayerCB.playerPos = m_player->GetCurrentPosition();
	cameraToPlayerCB.fadestrength = 0.1f;

	ShaderManager::GetInstance()->SetCameraToPlayerCB(cameraToPlayerCB);

	//オブジェクトの描画
	m_renderPipeLine->Render();
	//m_displayCollision->DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates(), Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());
	
	//UI描画
	m_buffUI->Render();
	m_clearConditionsUI->Render();
	UIManager::GetInstance()->Render();
	//パーティクル描画
	ParticleManager::GetInstance()->Render();
}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayScene::Finalize()
{
	//プレイヤーのデータ保存
	GetGameData()->SetPlayerCurrentHP(m_player->GetCurrentHP());
	SavePlayer();
	//当たり判定登録解除
	m_collsionManager->AllRelease();
	//終了処理
	for (auto object : m_objects) 
	{
		object->Finalize();
	}
	m_camera->Finalize();
	//BGMストップ
	m_gameBGM->Stop();
	//カウントされたオブジェクト番号をリセット
	GameObject::ResetObjectNumber();
	//メッセンジャークラスに登録されたライトを解除
	Messenger::GetInstance()->UnRegisterLight();
	//パーティクル消去
	ParticleManager::GetInstance()->Reset();
}


/**
 * @brief 
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayScene::CreateDeviceDependentResources()
{
	//std::this_thread::sleep_for(std::chrono::seconds{ 3 });
	//auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
}

void PlayScene::CreateWindowSizeDependentResources()
{
	//std::this_thread::sleep_for(std::chrono::seconds{ 3 });
	m_renderPipeLine->ReSize();
}

void PlayScene::OnDeviceLost()
{
}


/**
 * @brief 入力処理生成
 *
 * @param[in] なし
 *
 * @return  なし
 */
void PlayScene::CreateInputCommand()
{
	m_inputHandler = std::make_unique<InputHandler>();
	//コマンド登録
	m_inputHandler->Register(DirectX::Keyboard::Keys::Up,		 InputHandler::InputType::Hold,		std::make_unique<MoveFrontCommand>());
	m_inputHandler->Register(DirectX::Keyboard::Keys::Left,		 InputHandler::InputType::Hold,		std::make_unique<MoveLeftCommand>());
	m_inputHandler->Register(DirectX::Keyboard::Keys::Down,		 InputHandler::InputType::Hold,		std::make_unique<MoveBackCommand>());
	m_inputHandler->Register(DirectX::Keyboard::Keys::Right,	 InputHandler::InputType::Hold,		std::make_unique<MoveRightCommand>());
	m_inputHandler->Register(DirectX::Keyboard::Keys::Space,	 InputHandler::InputType::Pressed,  std::make_unique<JumpCommand>());
	m_inputHandler->Register(DirectX::Keyboard::Keys::Z,		 InputHandler::InputType::Pressed,  std::make_unique<AttackCommand>());
	m_inputHandler->Register(DirectX::Keyboard::Keys::X,		 InputHandler::InputType::Pressed,  std::make_unique<AvoidCommand>());
	m_inputHandler->Register(DirectX::Keyboard::Keys::LeftShift, InputHandler::InputType::Hold,		std::make_unique<RotationCommand>(1.0f));
	m_inputHandler->Register(DirectX::Keyboard::Keys::C,		 InputHandler::InputType::Hold,		std::make_unique<RotationCommand>(-1.0f));

}

void PlayScene::CreateObjects()
{
	//プレイヤーの生成
	m_player = GameObjectFactory::CreatePlayer(m_buffUI.get(), GetGameData()->GetPlayerData(), nullptr, PLAYER_INIT_POSITION);
	m_collsionManager->Register(m_player.get());
	m_objects.push_back(m_player.get());
	//ステージの生成
	m_ground = GameObjectFactory::CreateGround(nullptr, INITIAL_GROUND_POS, DirectX::SimpleMath::Quaternion::Identity, INITIAL_GROUND_SCALE);
	m_wall = GameObjectFactory::CreateWall(nullptr, INITIAL_WALL_POS, DirectX::SimpleMath::Quaternion::Identity, INITIAL_WALL_SCALE);
	m_objects.push_back(m_ground.get());
	m_objects.push_back(m_wall.get());
	m_collsionManager->Register(m_ground.get());
	GenerateIlumiRock(GetGameData()->GetIsOnLights(), ROCK_NUM);
	//敵の生成
	SpawnEnemy();
	//カメラの生成
	m_camera = GameObjectFactory::CreateCamera(CAMERA_INIT_POSITION, CAMERA_INIT_DISTANCE, m_player.get());
	//アイテム管理クラスの生成
	m_itemManager = std::make_unique<ItemManager>();
	m_itemManager->Initialize();

	//レンダーパイプラインに登録
	m_renderPipeLine->Register(RenderPipeLine::RenderLayer::Stage, m_ground.get());
	m_renderPipeLine->Register(RenderPipeLine::RenderLayer::Stage, m_wall.get());
	m_renderPipeLine->Register(RenderPipeLine::RenderLayer::Character, m_player.get());
	//石の登録
	for (std::unique_ptr<RumiRock>& rock : m_rocks)
	{
		m_renderPipeLine->Register(RenderPipeLine::RenderLayer::Stage, rock.get());
	}
	//敵の登録
	for (const std::unique_ptr<Character>& enemy : m_enemyManager->GetEnemies())
	{
		m_renderPipeLine->Register(RenderPipeLine::RenderLayer::Character, enemy.get());
		m_objects.push_back(enemy.get());

	}
	//アイテムの登録
	for (const std::unique_ptr<Item>& item : m_itemManager->GetItems())
	{
		m_renderPipeLine->Register(RenderPipeLine::RenderLayer::Item, item.get());
		m_objects.push_back(item.get());
	}

}

/**
 * @brief UI生成
 *
 * @param[in] なし
 *
 * @return  なし
 */
void PlayScene::CreateUI()
{
	GameData* gameData = GetGameData();
	auto uiManager = UIManager::GetInstance();
	//HPゲージUIの生成
	uiManager->RequestAddUI(UIFactory::CreateGauge(HP_GAUGE_UI_POS,DirectX::SimpleMath::Vector2::One,UserInterface::ANCHOR::MIDDLE_LEFT,
										m_player->GetCurrentHP(),m_player->GetMaxHP()));
	//所持宝石UIの生成
	uiManager->RequestAddUI(UIFactory::CreateHoldGem(gameData->GetPlayerData().gemID,HOLD_GEM_UI_POS));
	//クリア条件UI
	m_clearConditionsUI = UIFactory::CreateClearConditions(CLEAR_CONDITION_UI_POS);
	

	//攻撃操作方法
	std::vector<DirectX::Keyboard::Keys> key;
	key.push_back(DirectX::Keyboard::Keys::Z);
	uiManager->RequestAddUI(UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::ATTACK_ACTION, ATTACK_ACTION_UI_POS, ATTACK_ACTION_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));
	uiManager->RequestAddUI(UIFactory::CreateKeyUI(key, ResourcePath::TEXTURE::UI::Key::Z, ATTACK_KEY_UI_POS, ATTACK_KEY_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));
	//回避操作方法
	key.clear();
	key.push_back(DirectX::Keyboard::Keys::X);
	uiManager->RequestAddUI(UIFactory::CreateKeyUI(key,ResourcePath::TEXTURE::UI::Key::X, AVOID_KEY_UI_POS, AVOID_KEY_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));
	uiManager->RequestAddUI(UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::AVOID_ACTION,AVOID_ACTION_UI_POS,AVOID_ACTION_UI_SCALE,UserInterface::ANCHOR::MIDDLE_CENTER));
	//ジャンプ操作方法
	key.clear();
	key.push_back(DirectX::Keyboard::Keys::Space);
	uiManager->RequestAddUI(UIFactory::CreateKeyUI(key, ResourcePath::TEXTURE::UI::Key::SPACE, JUMP_KEY_UI_POS, JUMP_KEY_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));
	uiManager->RequestAddUI(UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::JUMP_ACTION, JUMP_ACTION_UI_POS, JUMP_ACTION_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));
	//視点回転操作方法
	key.clear();
	key.push_back(DirectX::Keyboard::Keys::LeftShift);
	uiManager->RequestAddUI(UIFactory::CreateKeyUI(key, ResourcePath::TEXTURE::UI::Key::SHIFT, LEFT_ROTATION_KEY_UI_POS, LEFT_ROTATION_KEY_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));
	key.clear();
	key.push_back(DirectX::Keyboard::Keys::C);
	uiManager->RequestAddUI(UIFactory::CreateKeyUI(key, ResourcePath::TEXTURE::UI::Key::C, RIGHT_ROTATION_KEY_UI_POS, RIGHT_ROTATION_KEY_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));
	uiManager->RequestAddUI(UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::ROTATION_ACTION, ROTATION_ACTION_UI_POS, ROTATION_ACTION_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));
	//移動操作方法
	uiManager->RequestAddUI(UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::MOVE_ACTION,MOVE_ACTION_UI_POS,MOVE_ACTION_UI_SCALE,UserInterface::ANCHOR::MIDDLE_CENTER));
	key.clear();
	key.push_back(DirectX::Keyboard::Keys::Left);
	uiManager->RequestAddUI(UIFactory::CreateKeyUI(key, ResourcePath::TEXTURE::UI::Key::LEFT_ARROW, LEFT_MOVE_KEY_UI_POS, LEFT_MOVE_KEY_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));
	key.clear();
	key.push_back(DirectX::Keyboard::Keys::Up);
	uiManager->RequestAddUI(UIFactory::CreateKeyUI(key, ResourcePath::TEXTURE::UI::Key::UP_ARROW, FRONT_MOVE_KEY_UI_POS, FRONT_MOVE_KEY_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));
	key.clear();
	key.push_back(DirectX::Keyboard::Keys::Right);
	uiManager->RequestAddUI(UIFactory::CreateKeyUI(key, ResourcePath::TEXTURE::UI::Key::RIGHT_ARROW, RIGHT_MOVE_KEY_UI_POS, RIGHT_MOVE_KEY_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));
	key.clear();
	key.push_back(DirectX::Keyboard::Keys::Down);
	uiManager->RequestAddUI(UIFactory::CreateKeyUI(key, ResourcePath::TEXTURE::UI::Key::DOWN_ARROW, BACK_MOVE_KEY_UI_POS, BACK_MOVE_KEY_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER));

}


/**
 * @brief 石の生成
 *
 * @param[in] isOnLight　ライトがオンかの配列
 * @param[in] size　配列の要素数
 *
 * @return なし
 */
void PlayScene::GenerateIlumiRock(bool* isOnLight, int size)
{

	//パスの生成
	std::string path = ResourcePath::DATA::LIGHT;
	//ファイルのオープン
	std::ifstream ifs{ path };
	if (!ifs.is_open())
	{
		//読み込み失敗
		return;
	}

	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	while (ifs)
	{
		int id = 0;
		//ライトの番号を読み込む
		ifs >> id;
		ifs.ignore(); //カンマを読み飛ばす

		if (id <= 0)
		{
			break;
		}

		//スポーン位置
		DirectX::SimpleMath::Vector3 spawnPos = DirectX::SimpleMath::Vector3::Zero;
		DirectX::SimpleMath::Vector3 color = DirectX::SimpleMath::Vector3::One;
		float intensity = 1.0f;

		//座標を読み込む
		ifs >> spawnPos.x;
		ifs.ignore(); //カンマを読み飛ばす
		ifs >> spawnPos.y;
		ifs.ignore(); //カンマを読み飛ばす
		ifs >> spawnPos.z;
		ifs.ignore(); //カンマを読み飛ばす

		//ライトの色を読み込む
		ifs >> color.x;
		ifs.ignore(); //カンマを読み飛ばす
		ifs >> color.y;
		ifs.ignore(); //カンマを読み飛ばす
		ifs >> color.z;
		ifs.ignore(); //カンマを読み飛ばす
		//ライト強度を読み込む
		ifs >> intensity;
		ifs.ignore(); //カンマを読み飛ばす


		ModelShader::PointLightCB lightdata;
		lightdata.LightColor = color;
		lightdata.LightIntensity = intensity;
		//石生成
		m_rocks.emplace_back(GameObjectFactory::CreateRumiRock(nullptr, spawnPos, DirectX::SimpleMath::Quaternion::Identity, lightdata, isOnLight[id - 1]));
		CollisionManager::GetInstance()->Register(m_rocks.back().get());
		m_objects.push_back(m_rocks.back().get());

	}
	ifs.close();
}

/**
 * @brief ステージを終了するか
 *
 * @param[in] なし
 *
 * @return true   終了
 * @return false  未了
 */
const bool PlayScene::IsFinish() 
{
	auto traker = Graphics::GetInstance()->GetKeyboardTracker();
	
	//ゲームクリア・ゲームオーバー判定
	if (traker->pressed.Q || m_enemyManager->GetEnemyCount() == 0 && !GetGameData()->IsStageClear())
	{
		GameData* gameData = GetGameData();
		GameData::PlayerData playerData = gameData->GetPlayerData();
		//HP設定
		playerData.currentHP = m_player->GetCurrentHP();
		playerData.maxHP = m_player->GetMaxHP();
		//プレイヤーの情報を設定
		gameData->SetPlayerData(playerData);

		//最終ステージなら
		if (gameData->GetNextStage() == GameData::Stage::BOSS)
		{
			//SaveLight();
			gameData->SetIsGameClear(true);
			gameData->SetPlayerCurrentHP(m_player->GetCurrentHP());
			ChangeScene<GemSelectScene>();
			return true;
		}
		gameData->SetNextStage();

		//ステージのライト状況を保存
		SaveLight();
		gameData->SetIsStageClear(true);
		ChangeScene<GemSelectScene>();
	}
	//プレイヤーが死んだら
	else if (!m_player->IsAlive())
	{
		GetGameData()->SetIsGameClear(false);
		GetGameData()->SetPlayerCurrentHP(m_player->GetCurrentHP());

		ChangeScene<ResultScene>();
		return true;
	}

	return false;
}
/**
 * @brief プレイヤーの状態を保存
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayScene::SavePlayer()
{

	const HolderGem& playerHolderGem = m_player->GetHolderGem();
	//プレイヤーの状態を保存する型
	GameData::PlayerData saveData;
	//現在HP
	saveData.currentHP = m_player->GetCurrentHP();
	//最大HP
	saveData.maxHP = m_player->GetMaxHP();
	//所持宝石
	auto& gems = playerHolderGem.GetGems();
	//所持数分要素を確保
	saveData.gemID.resize(gems.size());

	for (int i = 0; i < gems.size(); i++)
	{
		int id = Gem::BLANK_ID;
		//宝石があるなら
		if (gems[i])
		{
			//宝石のIDを保存
			id = gems[i]->GetAbility().id;
		}
		saveData.gemID[i] = id;
	}
	//シーンを超えて保存
	GetGameData()->SetPlayerData(saveData);

}

/**
 * @brief ライトの状態を記録
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayScene::SaveLight()
{
	////ステージのライトを取得
	//auto& rock = m_stage->GetRocks();
	//配列番号
	int index = 0;
	for (std::list<std::unique_ptr<RumiRock>>::iterator it =m_rocks.begin(); it != m_rocks.end(); ++it)
	{

		//ライトのオン・オフを記録
		GetGameData()->SetIsOnLightNumber(it->get()->IsOnLight(), index);
		index++;
	}
}


/**
 * @brief 敵の生成
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayScene::SpawnEnemy()
{
	GameData* gameData = GetGameData();
	//敵管理クラスの生成
	m_enemyManager = std::make_unique<EnemyManager>();

	
	//敵生成
	m_enemyManager->Spawn(gameData->GetEnemySpawnDataPath());
	//クリアフラグを偽に
	gameData->SetIsStageClear(false);
}

