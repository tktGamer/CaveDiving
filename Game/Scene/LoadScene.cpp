/**
 * @file   LoadScene.cpp
 *
 * @brief  ロードシーンに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/28
 */
// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "LoadScene.h"
#include"Game/GameData.h"
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

	Animation2D::AnimationTexture textureInfo{};
	textureInfo.frameCount  = NOWLOADING_FRAME_COUNT;
	textureInfo.frameWidth  = NOWLOADING_FRAME_WIDTH;
	textureInfo.frameHeight = NOWLOADING_FRAME_HEIGHT;
	//画像生成
	m_nowloadingTexture = UIFactory::CreateAnimation2DUI(ResourcePath::TEXTURE::UI::LOAD,textureInfo,NOWLOADING_ANIMATION_TIME,true,
		NOWLOADING_POSITON,NOWLOADING_SCALE);
	//背景画像生成
	m_backTexture = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::LOAD_BACK,
		BACK_TEXTURE_POS, BACK_TEXTURE_SCALE, UserInterface::ANCHOR::TOP_LEFT);

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
	m_backTexture->Update();
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
	m_nowloadingTexture->Render();
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
