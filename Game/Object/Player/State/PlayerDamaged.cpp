/**
 * @file   PlayerDamaged.cpp
 *
 * @brief  プレイヤーのダメージをくらった状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/20
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerDamaged.h"
#include "Game/Object/Player/Player.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pPlayer プレイヤーのポインタ
 */
PlayerDamaged::PlayerDamaged(Player* pPlayer)
	:
	m_pPlayer{pPlayer},
	m_knockbackTime{}
{
}
/**
 * @brief デストラクタ
 */
PlayerDamaged::~PlayerDamaged()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerDamaged::Initialize()
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
void PlayerDamaged::PreUpdate()
{

	m_knockbackTime = 0.0f;

	//当たった攻撃の方向を考慮してノックバック
	m_pPlayer->SetVelocity(m_pPlayer->GetDamageDirection() * KNOCKBACK_POWER);
	m_pPlayer->SetDamageFlash();
}

/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime
 *
 * @return なし
 */
void PlayerDamaged::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	m_knockbackTime += elapsedTime;
	//ノックバックが終わったか
	if (m_knockbackTime > KNOCKBACK_TIME)
	{
		Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber(), Message::IDLING);
		return;
	}

	DirectX::SimpleMath::Vector3 velocity = m_pPlayer->GetVelocity();

	//重力
	velocity.y += World::GRAVITY * elapsedTime;

	m_pPlayer->SetVelocity(velocity);
	//ノックバックさせる
	m_pPlayer->SetPosition(m_pPlayer->GetPosition() + m_pPlayer->GetVelocity()*elapsedTime);
}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerDamaged::PostUpdate()
{
	//m_pPlayer->SetInvincible(false);
	//m_pPlayer->SetVelocity(DirectX::SimpleMath::Vector3::Zero);
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerDamaged::Render()
{
#ifdef _DEBUG
	auto debugFont = Graphics::GetInstance()->GetDebugFont();	
	debugFont->AddString(L"Damaged", DirectX::SimpleMath::Vector2(500.0f, 50.0f));
#endif // DEBUG
}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerDamaged::Finalize()
{
}