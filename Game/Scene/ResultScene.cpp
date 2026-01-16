/**
 * @file   ResultScene.cpp
 *
 * @brief  リザルトシーンに関するソースファイル
 *
 * @author 制作者名  
 *
 * @date   日付  
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ResultScene.h"

#include "Game/Common/ResourceManager.h"

#include"../Scene/GameScene.h"
#include "../Scene/LoadScene.h"
#include"../Scene/TitleScene.h"
#include"../Common/DamageSystem.h"
#include"../Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
ResultScene::ResultScene()
	
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
	m_decideMenuSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound("decidemenu.wav"));
	m_clearSound	  = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound("gameclear.wav"));
	//クリア音再生
	m_clearSound->Play(false);
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	m_saveUI = std::make_unique<SaveConfirm>(1280, 720,GetGameData()->GetPlayerData().gemID);
	m_saveUI->Initialize();

	//ゲームクリア・ゲームオーバー文字
	if (GetGameData()->IsGameClear()) 
	{
		m_gameover = UIFactory::CreateUserInterface(L"UI/gameclear.png", { 650.0f,100.0f }, { 1.0f,1.0f }, UserInterface::MIDDLE_CENTER);
	}
	else
	{
		m_gameover = UIFactory::CreateUserInterface(L"UI/gameover.png", { 650.0f,100.0f }, { 1.0f,1.0f }, UserInterface::MIDDLE_CENTER);

	}
	
	m_scoreUI = std::make_unique<ScoreUIManager>(GetGameData()->GetScoreInfo());
	m_scoreUI->Initialize();

	//背景画像
	m_backTexture = UIFactory::CreateUserInterface(L"gemselectback.png", { 650.0f, 360.0f }, { 1.0f,1.0f }, UserInterface::ANCHOR::MIDDLE_CENTER);
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	PreUpdate();
}

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

	m_scoreUI->Render();

	//スコア計算の処理が終わっていたらセーブ確認UIを表示
	if (m_isSaveUIActive)
	{
		m_saveUI->Render();
	}

	//m_gameover->Render();
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
