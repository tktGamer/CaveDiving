/**
 * @file   PlayerAirAttack.cpp
 *
 * @brief  プレイヤーの攻撃状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/07
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerAirAttack.h"
#include "Game/Object/Player/Player.h"
#include"Game/Object/Player/Hand.h"
#include"Game/Motion/PlayerMotion/PlayerAirSpenningMotion.h"
#include"Game/Object/Gem/GemManager.h"
#include"Game/Object/Gem/Unique/AllSpenningAttackGem.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player プレイヤーのポインタ
 * @param[in] pRightHand 右手のポインタ
 * @param[in] pLeftHand 左手のポインタ
 */
PlayerAirAttack::PlayerAirAttack(Player* pPlayer, Hand* pRightHand, Hand* pLeftHand)
	:m_pPlayer(pPlayer)
{
	const std::vector<AllSpenningAttackGem*>& gems = m_pPlayer->GetHolderGem().IsHasGem<AllSpenningAttackGem>();
	//所持宝石によって攻撃モーションを変化
	if (gems.size() >= SPIN_ATTACK_GEM_NUM) 
	{
		m_airAttack = std::make_unique<PlayerAirSpenningMotion>(pPlayer, pRightHand, pLeftHand);
	}
	else
	{
		m_airAttack = std::make_unique<PlayerSlamAttackMotion>(pPlayer,pRightHand,pLeftHand);

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
	//モーション初期化
	m_airAttack->Initialize();
	//モーションによる攻撃力補正をセット
	m_pPlayer->SetMotionAttackRate(m_airAttack.get()->GetAttackPowerModifier());

	//ピッケルの当たり判定を有効にする
	Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber() + Player::PIKEL_OBJ_NUMBER, Message::COLLISIONVALID);

}

/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime
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


	m_pPlayer->SetVelocity(m_pPlayer->GetVelocity()*0.8f);


	//回避キーが押されたら
	if (key->pressed.X)
	{
		//回避状態へ遷移
		Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber(), Message::AVOIDANCE);
	}

	DirectX::SimpleMath::Vector3 velocity = m_pPlayer->GetVelocity();

	velocity.y += World::GRAVITY*3 * elapsedTime;
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
void PlayerAirAttack::PostUpdate()
{
	//ピッケルの当たり判定を無効にする
	Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber() + Player::PIKEL_OBJ_NUMBER, Message::COLLISIONINVALID);

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

