/**
 * @file   ResultScene.cpp
 *
 * @brief  リザルトシーンに関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2026/01/28
 */
// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ResultScene.h"
#include "Game/Common/ResourceManager.h"
#include"../Scene/PlayScene.h"
#include "../Scene/LoadScene.h"
#include"../Scene/TitleScene.h"
#include"../Common/DamageSystem.h"
#include"../Factory/UIFactory.h"
#include"Game/UI/UIManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
ResultScene::ResultScene()
	:
	m_backTexture{},
	m_holdGem{},
	m_gameover{},
	m_saveUI{},
	m_scoreUI{},
	m_clearSound{},
	m_decideMenuSound{}
{
}

/**
 * @brief デストラクタ
 */
ResultScene::~ResultScene()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ResultScene::Initialize()
{
	GetGameData()->SetTotalDamage(DamageSystem::GetInstance()->GetTotalDamage());
	//音生成
	m_decideMenuSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::MENU_DECIDE));
	m_clearSound	  = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::GAME_CLEAR));
	//クリア音再生
	m_clearSound->Play(false);

	m_saveUI = std::make_unique<SaveConfirm>(UIManager::WINDOW_SIZE_X, UIManager::WINDOW_SIZE_Y,GetGameData()->GetPlayerData().gemID);
	m_saveUI->Initialize();

	//ゲームクリア・ゲームオーバー文字
	if (GetGameData()->IsGameClear()) 
	{
		m_gameover = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::GAME_CLEAR,GAME_OVER_POS, GAME_OVER_SCALE, UserInterface::MIDDLE_CENTER);
	}
	else
	{
		m_gameover = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::GAME_OVER,GAME_OVER_POS, GAME_OVER_SCALE, UserInterface::MIDDLE_CENTER);

	}
	
	//スコア管理UIの生成
	m_scoreUI = std::make_unique<ScoreUIManager>(GetGameData()->GetScoreInfo());
	m_scoreUI->Initialize();

	//背景画像
	m_backTexture = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::GEM_BACK,BACK_POS, BACK_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER);
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	PreUpdate();
}


/**
 * @brief 事前更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ResultScene::PreUpdate()
{
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ResultScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	auto traker = Graphics::GetInstance()->GetKeyboardTracker();

	//選択したならシーン遷移
	if (m_saveUI->IsDecide()) 
	{
		ChangeScene<TitleScene>();
	}

	//スコア計算の処理が終わっていなかったら
	if (m_scoreUI->GetState() != ScoreUIManager::State::END) 
	{
		m_scoreUI->Update();

		
	}
	else if(m_isSaveUIActive)
	{
		m_saveUI->Update();
	}
	if (m_scoreUI->GetState() == ScoreUIManager::State::END && traker->IsKeyPressed(DirectX::Keyboard::Z)) 
	{
		m_isSaveUIActive = true;
	}
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ResultScene::Render()
{
	m_backTexture->Render();
	m_gameover->Render();

	m_scoreUI->Render();

	//スコア計算の処理が終わっていたらセーブ確認UIを表示
	if (m_isSaveUIActive)
	{
		m_saveUI->Render();
	}

}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ResultScene::Finalize()
{	
}

void ResultScene::CreateDeviceDependentResources()
{
}

void ResultScene::CreateWindowSizeDependentResources()
{
}

void ResultScene::OnDeviceLost()
{
}
