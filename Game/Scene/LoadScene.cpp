/**
 * @file   LoadScene.cpp
 *
 * @brief  ロードシーンに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/13
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "LoadScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"
#include"Game/Factory/UIFactory.h"



// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
LoadScene::LoadScene()
	: m_nowloadingTexture{},
	  m_backTexture{}
{
}



/**
 * @brief デストラクタ
 */
LoadScene::~LoadScene()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void LoadScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	ResourceManager* resourceManager = ResourceManager::GetInstance();
	Animation2D::AnimationTexture textureInfo{};
	textureInfo.frameCount = 4;
	textureInfo.frameWidth = 1;
	textureInfo.frameHeight = 4;
	m_nowloadingTexture = UIFactory::CreateAnimation2DUI(L"loading.png",textureInfo,6,true,
		DirectX::SimpleMath::Vector2{800.0f,590.0f},DirectX::SimpleMath::Vector2{1.0f,1.0f});
	m_backTexture = UIFactory::CreateUserInterface(L"loadback.jpg",
		DirectX::SimpleMath::Vector2{}, DirectX::SimpleMath::Vector2{ 0.7f,0.7f }, UserInterface::ANCHOR::TOP_LEFT);


	PreUpdate();
}


/**
 * @brief 事前更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void LoadScene::PreUpdate()
{
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void LoadScene::Update(float elapsedTime)
{
	m_nowloadingTexture->Update();

}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void LoadScene::Render()
{
	m_backTexture->Render();
	m_nowloadingTexture->Draw();
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void LoadScene::Finalize()
{
	
}

void LoadScene::CreateDeviceDependentResources()
{
}

void LoadScene::CreateWindowSizeDependentResources()
{
}

void LoadScene::OnDeviceLost()
{
}
