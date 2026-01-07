/**
 * @file   GemSelectScene.cpp
 *
 * @brief  宝石選択シーンに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GemSelectScene.h"

#include "Game/Common/ResourceManager.h"

#include"../Scene/GameScene.h"
#include "../Scene/LoadScene.h"
#include"Game/Scene/ResultScene.h"


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
GemSelectScene::GemSelectScene()
	: m_pResourceManager{}
	,m_gemSelectManager{}
{
	m_pResourceManager = ResourceManager::GetInstance();

}



/**
 * @brief デストラクタ
 */
GemSelectScene::~GemSelectScene()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemSelectScene::Initialize()
{

	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	m_gemSelectManager = std::make_unique<GemSelectUIManager>(GetGameData()->GetPlayerData().gemID);
	m_gemSelectManager->Initialize();

	m_backTexture = std::make_unique<UserInterface>();
	m_backTexture->SetWindowSize(w, h);
	m_backTexture->Create(L"gemselectback.png", { 650, 360 }, { 1.0f,1.0f }, UserInterface::ANCHOR::MIDDLE_CENTER);


	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
	PreUpdate();

}

void GemSelectScene::PreUpdate()
{
	m_gemSelectManager->Update();
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemSelectScene::Update(float elapsedTime)
{
	
	//宝石の選択が終わったらゲームシーンへ
	if (m_gemSelectManager->IsFinishSelect())
	{
		if (m_gemSelectManager->GetSlot() != -1) 
		{

		GameData::PlayerData playerData = GetGameData()->GetPlayerData();
		playerData.gemID[m_gemSelectManager->GetSlot()] =
		m_gemSelectManager->GetHoldGem()->GetAbility().id;
		GetGameData()->SetPlayerData(playerData);
		}
		if (GetGameData()->IsGameClear()) 
		{
			ChangeScene<ResultScene>();
			return;
		}
		ChangeScene<GameScene,LoadScene>();
	}


	m_gemSelectManager->Update();
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemSelectScene::Render()
{
	m_backTexture->Render();
	m_gemSelectManager->Render();
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemSelectScene::Finalize()
{
	
}

void GemSelectScene::CreateDeviceDependentResources()
{
}

void GemSelectScene::CreateWindowSizeDependentResources()
{
}

void GemSelectScene::OnDeviceLost()
{
}
