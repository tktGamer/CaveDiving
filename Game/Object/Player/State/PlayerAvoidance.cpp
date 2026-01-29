/**
 * @file   PlayerAvoidance.cpp
 *
 * @brief  プレイヤーの回避状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/20
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
PlayerAvoidance::PlayerAvoidance(Player* pPlayer)
	: 
	m_pPlayer(pPlayer),
	m_dodgeDirection{},
	m_dodgeTime{}
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
	//回避方向
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	//回避方向を決定する
	if (key->GetLastState().Up)
	{
		direction += Character::MOVE::FRONT;
	}
	else if (key->GetLastState().Down)
	{
		direction += Character::MOVE::BACK;

	}
	if (key->GetLastState().Left)
	{
		direction += Character::MOVE::LEFT;

	}
	else if (key->GetLastState().Right)
	{
		direction += Character::MOVE::RIGHT;

	}

	//移動キーの入力がなかったら
	if (direction == DirectX::SimpleMath::Vector3::Zero) 
	{
		direction += Character::MOVE::FRONT;

	}
	//正規化
	direction.Normalize();
	direction *= DODGE_SPEED;

	//回避方向を決定
	m_dodgeDirection = DirectX::SimpleMath::Vector3::Transform(direction, m_pPlayer->GetQuaternion());
}

/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime
 *
 * @return なし
 */
void PlayerAvoidance::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	m_pPlayer->SetPosition(m_pPlayer->GetPosition() + m_dodgeDirection);

	m_dodgeTime += elapsedTime;

	//回避時間を終えたら
	if (m_dodgeTime > DOOGE_TIME) 
	{
		Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber(), Message::IDLING);
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
#ifdef _DEBUG
	auto debugFont = Graphics::GetInstance()->GetDebugFont();
	debugFont->AddString(L"Avoidance", DirectX::SimpleMath::Vector2(500.0f, 50.0f));
#endif // DEBUG
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