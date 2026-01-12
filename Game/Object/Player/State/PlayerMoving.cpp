/**
 * @file   PlayerMoving.cpp
 *
 * @brief  プレイヤーの移動状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/08
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerMoving.h"
#include "Game/Object/Player/Player.h"
#include"Game/Particle/ParticleManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pPlayer プレイヤーのポインタ
 */
PlayerMoving::PlayerMoving(Player* pPlayer)
	: m_pPlayer(pPlayer)
{
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
 * @param[in] elapsedTime
 *
 * @return なし
 */
void PlayerMoving::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// キーボードステートを取得する
	DirectX::Keyboard::KeyboardStateTracker* key = Graphics::GetInstance()->GetKeyboardTracker();

	//攻撃キーを押されたら地上攻撃状態へ遷移
	if (key->IsKeyPressed(DirectX::Keyboard::Z)) 
	{
		Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber(), Message::GROUNDATTACK);
	}
	//ジャンプキーを押されたらジャンプ状態へ遷移
	if (key->pressed.Space)
	{
		Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber(), Message::JUMPING);
	}
	//回避キーを押されたら回避状態へ遷移
	if (key->pressed.X)
	{
		Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber(), Message::AVOIDANCE);
	}

	//移動
	DirectX::SimpleMath::Vector3 velocity = m_pPlayer->GetVelocity();
	//方向
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	if (key->GetLastState().Up)
	{
		direction += Character::MOVE::FRONT;
	}
	if (key->GetLastState().Down)
	{
		direction += Character::MOVE::BACK;

	}
	if (key->GetLastState().Left)
	{
		direction += Character::MOVE::LEFT;

	}
	if (key->GetLastState().Right)
	{
		direction += Character::MOVE::RIGHT;
	}
	//角度を考慮して速度に加算
	velocity += DirectX::SimpleMath::Vector3::Transform(direction*Player::MOVE_SPEED * elapsedTime, m_pPlayer->GetQuaternion());
	//ベクトルがある程度小さくなったら待機状態へ
	if(velocity.Length() <= Player::MIN_LENGTH)
	{
		Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber(), Message::IDLING);
	}

	//摩擦
	velocity *= World::GROUND_FRICTION;

	//重力
	velocity.y += World::GRAVITY * elapsedTime;

	//速度を設定
	m_pPlayer->SetVelocity(velocity);

	m_pPlayer->SetPosition(m_pPlayer->GetPosition() + m_pPlayer->GetVelocity());



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
#ifdef _DEBUG
	auto debugFont = Graphics::GetInstance()->GetDebugFont();

	debugFont->AddString(L"Moving", DirectX::SimpleMath::Vector2(500.0f, 50.0f));

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
