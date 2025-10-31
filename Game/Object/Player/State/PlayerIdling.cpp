/**
 * @file   PlayerIdling.cpp
 *
 * @brief  プレイヤーの待機状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/09/05
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerIdling.h"
#include "Game/Object/Player/Player.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player プレイヤーのポインタ
 */
PlayerIdling::PlayerIdling(Player* player)
	:m_player(player)
	,m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();

	m_idlingMotion = std::make_unique<PlayerIdlingMotion>
		(dynamic_cast<Hand*>( Messenger::GetInstance()->GetObject(player->GetObjectNumber()+1))
		,dynamic_cast<Hand*>( Messenger::GetInstance()->GetObject(player->GetObjectNumber() + 2)));
}
/**
 * @brief デストラクタ
 */
PlayerIdling::~PlayerIdling()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerIdling::Initialize()
{
	PreUpdate();
}

/**
 * @brief 事前処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerIdling::PreUpdate()
{
	DirectX::SimpleMath::Vector3 velocity = m_player->GetVelocity();

	m_player->SetVelocity(DirectX::SimpleMath::Vector3::Zero);

	m_idlingMotion->Initialize();
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// キーボードステートを取得する
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();
	
	m_idlingMotion->Update();

	//移動キーが押されたら移動状態へ遷移
	if (key->GetLastState().Left || key->GetLastState().Right || key->GetLastState().Up || key->GetLastState().Down)
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::MOVING);
	}
	//ジャンプキーが押されたらジャンプ状態へ遷移
	if (key->pressed.Space) 
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::JUMPING);
	}
	//攻撃キーが押されたら攻撃状態へ遷移
	if (key->pressed.Z) 
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::GROUNDATTACK);
	}
	//回避キーが押されたら回避状態へ遷移
	if (key->pressed.X) 
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::AVOIDANCE);
	}

	DirectX::SimpleMath::Vector3 v = m_player->GetVelocity();
	
	//重力
	v.y += -0.8f * elapsedTime;

	m_player->SetVelocity(v);

	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());

}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerIdling::PostUpdate()
{
	m_idlingMotion->Reset();
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerIdling::Render()
{

	auto debugFont = Graphics::GetInstance()->GetDebugFont();
	
	debugFont->AddString(L"Idling", DirectX::SimpleMath::Vector2(500.0f, 50.0f));
#ifdef _DEBUG
#endif // DEBUG

}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerIdling::Finalize()
{
}
