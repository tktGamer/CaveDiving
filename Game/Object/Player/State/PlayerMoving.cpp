/**
 * @file   PlayerMoving.cpp
 *
 * @brief  プレイヤーの移動状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/20
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
	: m_pPlayer{pPlayer}
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

	//進行方向を取得
	DirectX::SimpleMath::Vector3 direction = m_pPlayer->CalcMoveDirection();
	//入力がなければ待機状態へ
	if (direction == DirectX::SimpleMath::Vector3::Zero) 
	{
		Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber(), Message::IDLING);
		return;
	}
	//速度を取得
	DirectX::SimpleMath::Vector3 velocity = m_pPlayer->GetVelocity();
	//角度を考慮して速度に加算
	velocity += DirectX::SimpleMath::Vector3::Transform(direction*Player::MOVE_SPEED * elapsedTime, m_pPlayer->GetQuaternion());
	

	//摩擦
	velocity.x *= World::GROUND_FRICTION;
	velocity.z *= World::GROUND_FRICTION;

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