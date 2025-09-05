/**
 * @file   PlayerGroundAttack.cpp
 *
 * @brief  プレイヤーの攻撃状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerGroundAttack.h"
#include "Game/Object/Player/Player.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player プレイヤーのポインタ
 */
PlayerGroundAttack::PlayerGroundAttack(Player* player, Hand* hand)
	:m_player(player)
	,m_pHand{hand}
	,m_inputTime{0.0f}
	,m_isNextAttack{false}
{

	//m_groundCombo.emplace_back(std::make_unique<PlayerSlamAttack>(m_pHand));
	m_groundCombo.emplace_back(std::make_unique<PlayerFirstAttackMotion>(m_pHand));
	m_groundCombo.emplace_back(std::make_unique<PlayerSecondAttackMotion>(m_pHand));
	m_groundCombo.emplace_back(std::make_unique<PlayerThirdAttackMotion>(m_pHand));
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
	m_pHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(-90.0f)));

	m_inputTime = 0.0f;
	
	m_currentAttack = MotionType::PlayerGroundAttack::COMBO1;

	//ピッケルの当たり判定を有効にする
	Messenger::GetInstance()->Notify(m_player->GetObjectNumber() + 3, Message::COLLISIONVALID);

	//先頭の要素を初期化
	m_groundCombo.begin()->get()->Initialize();
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
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
		//次の攻撃をするか
		if (key->pressed.Z)
		{
			m_isNextAttack = true;
		}

		m_inputTime += elapsedTime;

	}



	//次の攻撃をするフラグがオンになったら
	if (m_isNextAttack)
	{
		m_currentAttack++;
		m_inputTime = 0.0f;
		m_isNextAttack = false;

		//要素内なら次のモーションを初期化処理
		if (m_currentAttack < m_groundCombo.size()) 
		{
			m_groundCombo[m_currentAttack]->Initialize();

		}
	}

	//一連の攻撃を終わった　入力時間が過ぎたら
	if (m_currentAttack >= m_groundCombo.size()|| m_inputTime >= 0.3f)
	{
		//待機状態へ遷移
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::IDLING);
	}



	m_player->SetVelocity(m_player->GetVelocity()*0.8f);



	//回避キーが押されたら
	if (key->pressed.X)
	{
		//回避状態へ遷移
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::AVOIDANCE);
	}

	

	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());

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
	//元の手の位置に戻す
	m_pHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(-50.0f)));
	m_pHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));

	//ピッケルの当たり判定を無効にする
	Messenger::GetInstance()->Notify(m_player->GetObjectNumber() + 3, Message::COLLISIONINVALID);


	for (std::unique_ptr<Motion>& groundMotion : m_groundCombo) 
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
	auto debugFont = Graphics::GetInstance()->GetDebugFont();

	debugFont->AddString(L"GroundAttack", DirectX::SimpleMath::Vector2(500.0f, 50.0f));

#ifdef _DEBUG
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

