/**
 * @file   GemSelectScene.cpp
 *
 * @brief  宝石選択シーンに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/28
 */
// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GemSelectScene.h"
#include "Game/Common/ResourceManager.h"
#include"../Scene/GameScene.h"
#include "../Scene/LoadScene.h"
#include"Game/Scene/ResultScene.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
GemSelectScene::GemSelectScene()
	:
	m_gemSelectManager{},
	m_backTexture{}
{
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
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
	//宝石選択UI管理クラス生成
	m_gemSelectManager = std::make_unique<GemSelectUIManager>(GetGameData()->GetPlayerData().gemID);
	m_gemSelectManager->Initialize();
	//背景画像の生成
	m_backTexture = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::GEM_BACK, BACK_TEXTURE_POS, BACK_TEXTURE_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER);

	PreUpdate();

}

/**
 * @brief 初期化時更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
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
	UNREFERENCED_PARAMETER(elapsedTime);

	//宝石の選択が終わったら
	if (m_gemSelectManager->IsFinishSelect())
	{
		//宝石が選択されていた
		if (m_gemSelectManager->GetSlot() != Gem::BLANK_ID)
		{

			GameData::PlayerData playerData = GetGameData()->GetPlayerData();
			//プレイヤーデータの宝石ID更新
			playerData.gemID[m_gemSelectManager->GetSlot()] = m_gemSelectManager->GetHoldGem()->GetAbility().id;
			GetGameData()->SetPlayerData(playerData);
		}
		//ステージがすべてクリアされていたら
		if (GetGameData()->IsGameClear()) 
		{
			//リザルトシーンへ遷移
			ChangeScene<ResultScene>();
			return;
		}
		//ゲームシーンへ遷移
		ChangeScene<GameScene,LoadScene>();
	}

	//UI更新
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
