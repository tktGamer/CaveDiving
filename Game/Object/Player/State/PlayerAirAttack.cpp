/**
 * @file   PlayerAirAttack.cpp
 *
 * @brief  プレイヤーの攻撃状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/11/19
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerAirAttack.h"
#include "Game/Object/Player/Player.h"
#include"Game/Motion/PlayerMotion/PlayerAirSpenningMotion.h"
#include"Game/Object/Gem/GemManager.h"
#include"Game/Object/Gem/Unique/AllSpenningAttackGem.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player プレイヤーのポインタ
 */
PlayerAirAttack::PlayerAirAttack(Player* player, Hand* pRightHand, Hand* pLeftHand)
	:m_player(player)
{
	std::vector<AllSpenningAttackGem*> gems = GemManager::GetInstance()->IsHasGem<AllSpenningAttackGem>();
	if (gems.size() >= 2) 
	{
		m_airAttack = std::make_unique<PlayerAirSpenningMotion>(player, pRightHand, pLeftHand);
	}
	else
	{
		m_airAttack = std::make_unique<PlayerSlamAttackMotion>(player,pRightHand,pLeftHand);

	}
}
/**
 * @brief デストラクタ
 */
PlayerAirAttack::~PlayerAirAttack()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerAirAttack::Initialize()
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
void PlayerAirAttack::PreUpdate()
{
	
	m_currentAttack = MotionType::PlayerAirAttack::JUMP;

	m_airAttack->Initialize();

	//ピッケルの当たり判定を有効にする
	Messenger::GetInstance()->Notify(m_player->GetObjectNumber() + 3, Message::COLLISIONVALID);

}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerAirAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// キーボードステートを取得する
	DirectX::Keyboard::KeyboardStateTracker* key = Graphics::GetInstance()->GetKeyboardTracker();

	//モーションの更新
	if (m_airAttack->Update())
	{

	}


	m_player->SetVelocity(m_player->GetVelocity()*0.8f);


	//回避キーが押されたら
	if (key->pressed.X)
	{
		//回避状態へ遷移
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::AVOIDANCE);
	}

	DirectX::SimpleMath::Vector3 v = m_player->GetVelocity();

	v.y += -3.0f * elapsedTime;
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
void PlayerAirAttack::PostUpdate()
{
	//ピッケルの当たり判定を無効にする
	Messenger::GetInstance()->Notify(m_player->GetObjectNumber() + 3, Message::COLLISIONINVALID);

	m_airAttack->Reset();

}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerAirAttack::Render()
{


#ifdef _DEBUG
	auto debugFont = Graphics::GetInstance()->GetDebugFont();
	debugFont->AddString(L"AirAttack", DirectX::SimpleMath::Vector2(500.0f, 50.0f));
#endif // DEBUG

}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerAirAttack::Finalize()
{
}

