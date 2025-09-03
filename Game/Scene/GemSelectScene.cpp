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
	m_gemSelectUI = std::make_unique<GemSelect>();
	m_gemSelectUI->Initialize(w, h);
	m_gemSelectUI->Randomize();

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
	
	if (traker->pressed.Space)
	{
		//現在のシーンを削除
		ChangeScene<GameScene>();
		
	}

	m_gemSelectUI->Update();
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
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world;

	DirectX::SpriteBatch* spriteBatch = graphics->GetSpriteBatch();

	spriteBatch->Begin();
	
	spriteBatch->End();

	m_gemSelectUI->Render();
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
