/**
 * @file   LogoScene.cpp
 *
 * @brief  ロゴシーンに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/12
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "LogoScene.h"

#include "Game/Common/ResourceManager.h"
#include"Game/Common/Sound.h"
#include"../Scene/TitleScene.h"

#include"../Factory/UIFactory.h"
#include"../Factory/GameObjectFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
LogoScene::LogoScene()
	
{


}



/**
 * @brief デストラクタ
 */
LogoScene::~LogoScene()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void LogoScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	m_logoAnimation = UIFactory::CreateAnimation2DUI(ResourcePath::TEXTURE::UI::LOGO,
		Animation2D::AnimationTexture{ 18,6,3 }, 2.0f, false, DirectX::SimpleMath::Vector2{ 640.0f,360.0f }, DirectX::SimpleMath::Vector2{ 1.9f,1.9f });
	PreUpdate();
}

void LogoScene::PreUpdate()
{
}



/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime
 *
 * @return なし
 */
void LogoScene::Update(float elapsedTime)
{
	auto traker = Graphics::GetInstance()->GetKeyboardTracker();
	//スペースキーを押したら、アニメーションが終わったらシーン遷移
	if (traker->pressed.Space || m_logoAnimation->IsFinish())
	{
		ChangeScene<TitleScene>();
	}

	m_logoAnimation->Update();
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void LogoScene::Render()
{
	//アニメーション
	m_logoAnimation->Draw();
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void LogoScene::Finalize()
{
}

void LogoScene::CreateDeviceDependentResources()
{
}

void LogoScene::CreateWindowSizeDependentResources()
{
}

void LogoScene::OnDeviceLost()
{
}
