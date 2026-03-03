/**
 * @file   PlayerGroundAttack.cpp
 *
 * @brief  プレイヤーの攻撃状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/20
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerGroundAttack.h"
#include "Game/Object/Player/Player.h"
#include"Game/Object/Player/Hand.h"
#include"Game//Object//Gem/GemManager.h"
#include"Game/Object/Gem/Unique/AllSpenningAttackGem.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player      プレイヤーのポインタ
 * @param[in] pRightHand  プレイヤー右手のポインタ
 * @param[in] pLeftHand   プレイヤー左手のポインタ
 */
PlayerGroundAttack::PlayerGroundAttack(Player* pPlayer, Hand* pRightHand, Hand* pLeftHand)
	:
	m_pPlayer(pPlayer),
	m_pRightHand{pRightHand},
	m_pLeftHand{pLeftHand},
	m_currentAttack{},
	m_groundCombo{},
	m_inputTime{}
{

	const std::vector<AllSpenningAttackGem*> gems =  m_pPlayer->GetHolderGem().FindHasGem<AllSpenningAttackGem>();
	//回転攻撃の宝石があったら
	if (!gems.empty()) 
	{
		m_groundCombo.emplace_back(std::make_unique<PlayerThirdAttackMotion>(pRightHand, pLeftHand));
		m_groundCombo.emplace_back(std::make_unique<PlayerThirdAttackMotion>(pRightHand, pLeftHand));
		m_groundCombo.emplace_back(std::make_unique<PlayerThirdAttackMotion>(pRightHand, pLeftHand));
	}
	else
	{
		m_groundCombo.emplace_back(std::make_unique<PlayerFirstAttackMotion>(pRightHand, pLeftHand));
		m_groundCombo.emplace_back(std::make_unique<PlayerSecondAttackMotion>(pRightHand, pLeftHand));
		m_groundCombo.emplace_back(std::make_unique<PlayerThirdAttackMotion>(pRightHand, pLeftHand));
	}
}
/**
 * @brief デストラクタ
 */
PlayerGroundAttack::~PlayerGroundAttack()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerGroundAttack::Initialize()
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
void PlayerGroundAttack::PreUpdate()
{
	m_pRightHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(-90.0f)));

	m_inputTime = 0.0f;
	
	m_currentAttack = MotionType::PlayerGroundAttack::COMBO1;

	//ピッケルの当たり判定を有効にする
	Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber() + Player::PIKEL_OBJ_NUMBER, Message::COLLISIONVALID);

	//先頭の要素を初期化
	m_groundCombo.begin()->get()->Initialize();
	//モーションによる攻撃力補正をセット
	m_pPlayer->SetMotionAttackRate(m_groundCombo.begin()->get()->GetAttackPowerModifier());
}

/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime
 *
 * @return なし
 */
void PlayerGroundAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// キーボードステートを取得する
	DirectX::Keyboard::KeyboardStateTracker* key = Graphics::GetInstance()->GetKeyboardTracker();

	//モーションの更新
	if (m_groundCombo[m_currentAttack]->Update())
	{
		//次の攻撃をするフラグがオンになったら
		if (m_pPlayer->IsAttackBuffered())
		{
			m_currentAttack++;
			m_inputTime = 0.0f;

			//要素内なら次のモーションを初期化処理
			if (m_currentAttack < m_groundCombo.size())
			{
				m_groundCombo[m_currentAttack]->Initialize();
				//モーションによる攻撃力補正をセット
				m_pPlayer->SetMotionAttackRate(m_groundCombo[m_currentAttack]->GetAttackPowerModifier());
			}
		}
		m_inputTime += elapsedTime;
	}

	//一連の攻撃を終わった　入力時間が過ぎたら
	if (m_currentAttack >= m_groundCombo.size()|| m_inputTime >= INPUT_TIME)
	{
		//待機状態へ遷移
		Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber(), Message::IDLING);
	}


	DirectX::SimpleMath::Vector3 velocity = m_pPlayer->GetVelocity();

	velocity *= World::GROUND_FRICTION;
	//重力
	velocity.y += World::GRAVITY * elapsedTime;

	m_pPlayer->SetVelocity(velocity);

	//回避キーが押されたら
	if (key->pressed.X)
	{
		//回避状態へ遷移
		Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber(), Message::AVOIDANCE);
	}

	
	//移動
	m_pPlayer->SetPosition(m_pPlayer->GetPosition() + m_pPlayer->GetVelocity());

}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerGroundAttack::PostUpdate()
{
	m_pRightHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, Player::RIGHT_HAND_Z_ANGLE));
	m_pRightHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);

	//ピッケルの当たり判定を無効にする
	Messenger::GetInstance()->Notify(m_pPlayer->GetObjectNumber() + Player::PIKEL_OBJ_NUMBER, Message::COLLISIONINVALID);

	//モーションをリセット
	for (std::unique_ptr<AttackMotion>& groundMotion : m_groundCombo)
	{
		groundMotion->Reset();
	}
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerGroundAttack::Render()
{
#ifdef _DEBUG
	auto debugFont = Graphics::GetInstance()->GetDebugFont();
	debugFont->AddString(L"GroundAttack", DirectX::SimpleMath::Vector2(500.0f, 50.0f));

#endif // DEBUG

}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerGroundAttack::Finalize()
{
}

