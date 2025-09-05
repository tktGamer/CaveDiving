/**
 * @file   PlayerAvoidance.cpp
 *
 * @brief  プレイヤーの回避状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerAvoidance.h"
#include "Game/Object/Player/Player.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player プレイヤーのポインタ
 */
PlayerAvoidance::PlayerAvoidance(Player* player)
	: m_player(player)
	, m_dodgeTime{ 0.0f }
	, m_maxDodgeDuration{0.05f}
	, m_dodgeDirection{}
{
}
/**
 * @brief デストラクタ
 */
PlayerAvoidance::~PlayerAvoidance()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerAvoidance::Initialize()
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
void PlayerAvoidance::PreUpdate()
{
	// キーボードステートを取得する
	DirectX::Keyboard::KeyboardStateTracker* key = Graphics::GetInstance()->GetKeyboardTracker();

	m_dodgeTime = 0;
	//回避方向を決定する
	m_dodgeDirection = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f,0.0f,-5.0f),m_player->GetQuaternion());

	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	//回避方向を決定する
	if (key->GetLastState().Up)
	{
		direction += DirectX::SimpleMath::Vector3(0.0f, 0.0f, -1.0f);
	}
	else if (key->GetLastState().Down)
	{
		direction += DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f);

	}
	if (key->GetLastState().Left)
	{
		direction += DirectX::SimpleMath::Vector3(-1.0f, 0.0f, 0.0f);

	}
	else if (key->GetLastState().Right)
	{
		direction += DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f);

	}

	//移動キーの入力がなかったら
	if (direction == DirectX::SimpleMath::Vector3::Zero) 
	{
		direction += DirectX::SimpleMath::Vector3(0.0f, 0.0f, -1.0f);

	}
	//正規化
	direction.Normalize();
	direction *= DODGE_SPEED;

	//回避方向を決定
	m_dodgeDirection = DirectX::SimpleMath::Vector3::Transform(direction, m_player->GetQuaternion());
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerAvoidance::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	float e = Messenger::GetInstance()->GetElapsedTime();

	m_player->SetPosition(m_player->GetPosition() + m_dodgeDirection);

	m_dodgeTime += e;

	//回避時間を終えたら
	if (m_dodgeTime > m_maxDodgeDuration) 
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::IDLING);
	}
}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerAvoidance::PostUpdate()
{
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerAvoidance::Render()
{
	auto debugFont = Graphics::GetInstance()->GetDebugFont();

	debugFont->AddString(L"Avoidance", DirectX::SimpleMath::Vector2(500.0f, 50.0f));


}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerAvoidance::Finalize()
{
}
