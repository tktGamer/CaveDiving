/**
 * @file   PlayerJumping.cpp
 *
 * @brief  プレイヤーのジャンプ状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerJumping.h"
#include "Game/Object/Player/Player.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player プレイヤーのポインタ
 */
PlayerJumping::PlayerJumping(Player* player)
	: m_player(player)
	, m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
}
/**
 * @brief デストラクタ
 */
PlayerJumping::~PlayerJumping()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerJumping::Initialize()
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
void PlayerJumping::PreUpdate()
{
	DirectX::SimpleMath::Vector3 v = m_player->GetVelocity();
	//ジャンプの速度を設定
	v.y = 0.5f;
	m_player->SetVelocity(v);

}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerJumping::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// キーボードステートを取得する
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();
	DirectX::SimpleMath::Vector3 v = m_player->GetVelocity();


	if (key->GetLastState().Up)
	{
		v -= DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f) * elapsedTime, m_player->GetQuaternion());
	}
	if (key->GetLastState().Down)
	{
		v += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f) * elapsedTime, m_player->GetQuaternion());

	}
	if (key->GetLastState().Left)
	{
		v -= DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f) * elapsedTime, m_player->GetQuaternion());

	}
	if (key->GetLastState().Right)
	{
		v += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f) * elapsedTime, m_player->GetQuaternion());

	}
	if (key->IsKeyPressed(DirectX::Keyboard::Z))
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::AIRATTACK);
	}


	if (v.Length() <= 0.001f)
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::IDLING);
	}
	v *= 0.96f;
	v.y += -0.89f * elapsedTime;

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
void PlayerJumping::PostUpdate()
{
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerJumping::Render()
{
	auto debugFont = Graphics::GetInstance()->GetDebugFont();

	debugFont->AddString(L"Jumping", DirectX::SimpleMath::Vector2(500.0f, 50.0f));

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
void PlayerJumping::Finalize()
{
}
