/**
 * @file   PlayerIdling.cpp
 *
 * @brief  プレイヤーの待機状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/20
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerIdling.h"
#include "Game/Object/Player/Player.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pPlayer プレイヤーのポインタ
 */
PlayerIdling::PlayerIdling(Player* pPlayer)
	:
	m_pPlayer{pPlayer},
	m_idlingMotion{}
{
	//モーションを生成
	m_idlingMotion = std::make_unique<PlayerIdlingMotion>
		(dynamic_cast<Hand*>( Messenger::GetInstance()->GetObject(m_pPlayer->GetObjectNumber() + Player::RIGHT_HAND_OBJ_NUMBER)),
		 dynamic_cast<Hand*>( Messenger::GetInstance()->GetObject(m_pPlayer->GetObjectNumber() + Player::LEFT_HAND_OBJ_NUMBER)));
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
	//速度を初期化
	m_pPlayer->SetVelocity(DirectX::SimpleMath::Vector3::Zero);
	//モーションを初期化
	m_idlingMotion->Initialize();
}

/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime
 *
 * @return なし
 */
void PlayerIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	//モーションを更新
	m_idlingMotion->Update();


	DirectX::SimpleMath::Vector3 velocity = m_pPlayer->GetVelocity();
	
	//重力
	velocity.y += World::GRAVITY * elapsedTime;
	m_pPlayer->SetVelocity(velocity);
	//座標更新
	m_pPlayer->SetPosition(m_pPlayer->GetPosition() + m_pPlayer->GetVelocity());

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
	//モーションをリセット
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
#ifdef _DEBUG
	auto debugFont = Graphics::GetInstance()->GetDebugFont();
	debugFont->AddString(L"Idling", DirectX::SimpleMath::Vector2(500.0f, 50.0f));
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