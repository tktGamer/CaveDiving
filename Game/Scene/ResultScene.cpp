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

	m_titleTexture = *m_pResourceManager->RequestTexture("title.png");
	m_pressSpaceTexture = *m_pResourceManager->RequestTexture("pressspace.png");

	//m_camera->Initialize({ 0,11.0f,10.0f });


	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);


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
void ResultScene::Update(float elapsedTime)
{
	auto traker = Graphics::GetInstance()->GetKeyboardTracker();
	
	if (traker->pressed.Space)
	{
		//ChangeScene<GameScene,LoadScene>();
	}
	/*m_camera->SetEyePosX(m_length * std::cos(r));
	m_camera->SetEyePosZ(m_length * std::sin(r));*/

	//m_camera->Update(elapsedTime);
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

	spriteBatch->Begin();
	//spriteBatch->Draw(m_titleTexture, DirectX::SimpleMath::Vector2(400, 100));
	//spriteBatch->Draw(m_pressSpaceTexture, DirectX::SimpleMath::Vector2(400, 550));

	
	spriteBatch->End();
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
