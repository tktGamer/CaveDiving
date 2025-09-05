/**
 * @file   PlayerMoving.cpp
 *
 * @brief  プレイヤーの移動状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerMoving.h"
#include "Game/Object/Player/Player.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player プレイヤーのポインタ
 */
PlayerMoving::PlayerMoving(Player* player)
	: m_player(player)
	, m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
}
/**
 * @brief デストラクタ
 */
PlayerMoving::~PlayerMoving()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerMoving::Initialize()
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
void PlayerMoving::PreUpdate()
{
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerMoving::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// キーボードステートを取得する
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();

	//攻撃キーを押されたら地上攻撃状態へ遷移
	if (key->IsKeyPressed(DirectX::Keyboard::Z)) 
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::GROUNDATTACK);
	}
	//ジャンプキーを押されたらジャンプ状態へ遷移
	if (key->pressed.Space)
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::JUMPING);
	}
	//回避キーを押されたら回避状態へ遷移
	if (key->pressed.X)
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::AVOIDANCE);
	}

	DirectX::SimpleMath::Vector3 velocity = m_player->GetVelocity();

	//移動
	if (key->GetLastState().Up) 
	{
		velocity += DirectX::SimpleMath::Vector3::Transform(Character::MOVE::FRONT * elapsedTime, m_player->GetQuaternion());
	}
	if (key->GetLastState().Down)
	{
		velocity += DirectX::SimpleMath::Vector3::Transform(Character::MOVE::BACK * elapsedTime, m_player->GetQuaternion());
	}
	if (key->GetLastState().Left)
	{
		velocity += DirectX::SimpleMath::Vector3::Transform(Character::MOVE::LEFT * elapsedTime, m_player->GetQuaternion());
	}
	if (key->GetLastState().Right)
	{
		velocity += DirectX::SimpleMath::Vector3::Transform(Character::MOVE::RIGHT *elapsedTime, m_player->GetQuaternion());
	}


	if(velocity.Length()<=0.001f)
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::IDLING);
	}

	//摩擦
	velocity *= 0.96f;

	//重力
	velocity.y += -0.8f * elapsedTime;

	//速度を設定
	m_player->SetVelocity(velocity);

	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());



}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerMoving::PostUpdate()
{
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerMoving::Render()
{
	auto debugFont = Graphics::GetInstance()->GetDebugFont();

	debugFont->AddString(L"Moving", DirectX::SimpleMath::Vector2(500.0f, 50.0f));

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
void PlayerMoving::Finalize()
{
}
