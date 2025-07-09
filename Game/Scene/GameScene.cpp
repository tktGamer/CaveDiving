/**
 * @file   GameScene.cpp
 *
 * @brief  Xシーンに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GameScene.h"

#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"


#include"Game/Common/Collision/Sphere.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] sceneManager    シーンを管理しているマネージャ
 * @param[in] resourceManager リソースを管理しているマネージャ
 */
GameScene::GameScene(SceneManager* pSceneManager)
	: Scene{ pSceneManager }
	, m_pResourceManager{}
{
	TKTLib::ModelParams modelParams;

	m_camera = std::make_unique<Camera>();
	m_player = std::make_unique<Player>();
	m_stage = std::make_unique<Stage>();
	m_pResourceManager = ResourceManager::GetInstance();

	m_displayCollision = std::make_unique<Ito::DisplayCollision>(
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());
}



/**
 * @brief デストラクタ
 */
GameScene::~GameScene()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameScene::Initialize()
{
	m_camera->Initialize({ 0,1.0f,25.0f });
	m_camera->SetDistance(DirectX::SimpleMath::Vector3{ 0.0f, 7.0f, 25.0f });
	m_player->Initialize();
	m_stage->Initialize();

	m_camera->SetTartet(m_player->GetPosition(), m_player->GetQuaternion());
	m_camera->SetTargetPos(m_player->GetPosition());
}



/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime 前フレームからの経過時間
 *
 * @return なし
 */
void GameScene::Update(float elapsedTime)
{
	DirectX::Keyboard::KeyboardStateTracker* traker = Graphics::GetInstance()->GetKeyboardTracker();
	if (traker->pressed.Enter)
	{
		ChangeScene("Title", false);
	}
	m_player->Update(elapsedTime);
	m_stage->Update(elapsedTime);
	//m_camera->SetEyePos(m_player->GetModelParams().GetPosition() + DirectX::SimpleMath::Vector3(0.0f, 1.0f, 5.0f));
	m_camera->SetTargetPos(m_player->GetPosition());

	m_camera->Update(elapsedTime);
}



/**
 * @brief 描画処理
 *
 * @param[in] context
 * @param[in] states
 * @param[in] proj
 *
 * @return なし
 */
void GameScene::Render()
{
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetView());
	//Graphics::GetInstance()->DrawPrimitiveBegin(m_camera->GetView(), Graphics::GetInstance()->GetProjectionMatrix());
	Shader* shader = Shader::GetInstance();

	m_player->Draw();

	m_player->GetShape()->AddDisplayCollision(m_displayCollision.get());

	m_stage->Draw();
	m_stage->GetShape()->AddDisplayCollision(m_displayCollision.get());

	m_displayCollision->DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates()
		, Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());

	if (m_stage->GetShape()->Intersects(m_player->GetShape())) 
	{
		auto debugFont = Graphics::GetInstance()->GetDebugFont();

		debugFont->AddString(L"Hit", DirectX::SimpleMath::Vector2(0.0f, 20.0f));
	}

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameScene::Finalize()
{
	m_player->Finalize();
	m_stage->Finalize();
}

