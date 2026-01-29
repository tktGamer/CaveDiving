/**
 * @file   GolemChasing.cpp
 *
 * @brief  ゴーレムの追跡状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Golem/State/GolemChasing.h"
#include "Game/Object/Enemy/Golem/Golem.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] golem ゴーレムのポインタ
 */
GolemChasing::GolemChasing(Golem* golem)
	: m_golem{golem}
	, m_pPlayer{ Messenger::GetInstance()->GetObject(0) }
{
}
/**
 * @brief デストラクタ
 */
GolemChasing::~GolemChasing()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemChasing::Initialize()
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
void GolemChasing::PreUpdate()
{
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemChasing::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	DirectX::SimpleMath::Vector3 velocity = m_golem->GetVelocity();

	//自分からプレイヤーの角度を求める
	float radian = TKTLib::CaluculateRadian(m_golem->GetCurrentPosition(), m_pPlayer->GetCurrentPosition());
	//目標の角度
	DirectX::SimpleMath::Quaternion rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, radian);


	//目標に向かう
	DirectX::SimpleMath::Vector3 chaseSpeed = Character::MOVE::FRONT * CHASE_SPPED * elapsedTime;
	velocity += DirectX::SimpleMath::Vector3::Transform(chaseSpeed, rotate);


	//プレイヤーが範囲外にでて一定時間経ったら待機状態へ遷移
	float distance = DirectX::SimpleMath::Vector3::Distance(m_pPlayer->GetCurrentPosition(), m_golem->GetCurrentPosition());
	//範囲外なら遷移
	if (distance > Golem::CHASE_RANGE)
	{
		//待機状態
		Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::IDLING);
	}
	//攻撃範囲に入っていたら攻撃準備状態へ遷移
	if (distance < ATTACK_RANGE)
	{
		//ランダムに攻撃を決める
		m_golem->SetAttackMessage
		(
			static_cast<Message::AttackMesssage>(
			TKTLib::GetRand(
			Message::AttackMesssage::ATTACKTYPE_ONE, 
			Message::AttackMesssage::ATTACKTYPE_TWO))
		);
		//攻撃準備状態
		Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::ATTACKPREPARING);

	}

	//摩擦
	velocity *= World::GROUND_FRICTION;
	//重力
	velocity.y += World::GRAVITY * elapsedTime;

	m_golem->SetVelocity(velocity);
	//座標更新
	m_golem->SetPosition(m_golem->GetPosition() + m_golem->GetVelocity());

	// 姿勢に回転を加える
	m_golem->SetQuaternion(rotate);
}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemChasing::PostUpdate()
{
	//経過時間をリセット
	m_golem->ResetFrameCount();
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemChasing::Render()
{
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
void GolemChasing::Finalize()
{
}