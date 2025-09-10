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

	m_gemSelectManager = std::make_unique<GemSelectUIManager>();
	m_gemSelectManager->Initialize();
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();


}



/**
 * @brief 更新処理
 *
 * @param[in] inputDevice 入力デバイス
 *
 * @return なし
 */
void GemSelectScene::Update(float elapsedTime)
{
	auto traker = Graphics::GetInstance()->GetKeyboardTracker();
	
	if (m_gemSelectManager->IsFinishSelect())
	{
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
