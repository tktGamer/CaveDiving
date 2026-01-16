/**
 * @file   PlayerJumping.cpp
 *
 * @brief  プレイヤーのジャンプ状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/08
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerJumping.h"
#include "Game/Object/Player/Player.h"
#include "Game/Common/Graphics.h"

#include"Game/Particle/ParticleManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pPlayer プレイヤーのポインタ
 */
PlayerJumping::PlayerJumping(Player* pPlayer)
	: m_pPlayer(pPlayer)
{
	//音生成
	m_jumpSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::PLAYER_JUMP));
	m_jumpSound->SetVolume(0.1f);
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
	DirectX::SimpleMath::Vector3 velocity = m_pPlayer->GetVelocity();
	//ジャンプの速度を設定
	velocity.y = JUMP_POWER /** Messenger::GetInstance()->GetElapsedTime()*/;
	m_pPlayer->SetVelocity(velocity);
	m_jumpSound->Play(false);
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
	DirectX::Keyboard::KeyboardStateTracker* key = Graphics::GetInstance()->GetKeyboardTracker();
	DirectX::SimpleMath::Vector3 velocity = m_pPlayer->GetVelocity();
	//移動キーの方向に進む
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
	velocity += DirectX::SimpleMath::Vector3::Transform(direction * elapsedTime, m_pPlayer->GetQuaternion());

	//空中攻撃
	if (key->IsKeyPressed(DirectX::Keyboard::Z))
	{
		Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber(), Message::AIRATTACK);
	}

	//移動量が無くなったとみなし待機状態へ
	if (velocity.Length() <= Player::MIN_LENGTH)
	{
		Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber(), Message::IDLING);
	}
	//摩擦
	velocity.x *= World::AIR_FRICTION;
	velocity.z *= World::AIR_FRICTION;
	//重力
	velocity.y += World::GRAVITY * elapsedTime;

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
#ifdef _DEBUG
	auto debugFont = Graphics::GetInstance()->GetDebugFont();

	debugFont->AddString(L"Jumping", DirectX::SimpleMath::Vector2(500.0f, 50.0f));

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
