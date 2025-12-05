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
#include"../Fuctory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
ResultScene::ResultScene()
	: m_pResourceManager{}
{
	m_camera = std::make_unique<Camera>();
	m_pResourceManager = ResourceManager::GetInstance();


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

	m_decideMenuSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound("decidemenu.wav"));
	m_clearSound	  = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound("gameclear.wav"));
	m_clearSound->Play(false);
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);
	m_saveMessage =UIFactory::CreateUserInterface(L"UI/savemessage.png", { 650.0f,400.0f }, { 1.0f,1.0f }, UserInterface::MIDDLE_CENTER);


	m_menu = UIFactory::CreateMenu(ResourceManager::GetInstance()->RequestSound("cursormove.wav"));
	m_menu->Add(L"UI/yesfont.png", { 350.0f,600.0f }, { 1.0f,1.0f }, UserInterface::ANCHOR::MIDDLE_CENTER);
	m_menu->Add(L"UI/nofont.png", { 950.0f,600.0f }, { 1.0f,1.0f }, UserInterface::ANCHOR::MIDDLE_CENTER);


	//ゲームクリア・ゲームオーバー文字
	if (GetGameData()->IsGameClear()) 
	{
		m_gameover = UIFactory::CreateUserInterface(L"UI/gameclear.png", { 650.0f,100.0f }, { 1.0f,1.0f }, UserInterface::MIDDLE_CENTER);
	}
	else
	{
		m_gameover = UIFactory::CreateUserInterface(L"UI/gameover.png", { 650.0f,100.0f }, { 1.0f,1.0f }, UserInterface::MIDDLE_CENTER);

	}

	m_backTexture = UIFactory::CreateUserInterface(L"gemselectback.png", { 650, 360 }, { 1.0f,1.0f }, UserInterface::ANCHOR::MIDDLE_CENTER);
	m_totalDamageUI = std::make_unique<TotalDamage>(DirectX::SimpleMath::Vector2{ 1100,220 });
	m_totalDamageUI->Initialize(w, h,DamageSystem::GetInstance()->GetTotalDamage());
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();


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
	
	auto tracker = Graphics::GetInstance()->GetKeyboardTracker();

	m_menu->Update();

	if (tracker->pressed.Space)
	{
		int menuIndex = m_menu->GetMenuIndex();
		m_decideMenuSound->Play(false);
		switch (menuIndex)
		{
			//「はい」の場合
		case 0:
			//所持している宝石を保存する
			GemManager::GetInstance()->SavePlayerHoldGem();
			ChangeScene<TitleScene>();
			break;
			//「いいえ」の場合
		case 1:
			//表示を消す
			ChangeScene<TitleScene>();

			break;
		}
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
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix proj = graphics->GetProjectionMatrix();

	//auto view=m_camera->GetView();
	//m_testPlayer.Draw(*context, *states, view, proj);
	DirectX::SimpleMath::Matrix world;

	DirectX::SpriteBatch* spriteBatch = graphics->GetSpriteBatch();
	m_backTexture->Draw();


	spriteBatch->Begin();
	//spriteBatch->Draw(m_titleTexture, DirectX::SimpleMath::Vector2(400, 100));
	//spriteBatch->Draw(m_pressSpaceTexture, DirectX::SimpleMath::Vector2(400, 550));

	
	spriteBatch->End();

	m_gameover->Draw();
	m_totalDamageUI->Render();
	m_saveMessage->Draw();
	m_menu->Render();

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
