/**
 * @file   BatChasing.cpp
 *
 * @brief  コウモリの追跡状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Bat/State/BatChasing.h"
#include "Game/Object/Enemy/Bat/Bat.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] bat コウモリのポインタ
 */
BatChasing::BatChasing(Bat* bat)
	: 
	m_bat{bat},
	m_pPlayer{}
{
	//プレイヤーオブジェクトを取得
	Messenger* messenger = Messenger::GetInstance();
	m_pPlayer = messenger->GetObject(messenger->GetPlayerObjectID());
}
/**
 * @brief デストラクタ
 */
BatChasing::~BatChasing()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatChasing::Initialize()
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
void BatChasing::PreUpdate()
{
}

/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime
 *
 * @return なし
 */
void BatChasing::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	//追跡
	Movement();
	//状態遷移
	CheckStateTransition();
}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatChasing::PostUpdate()
{
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatChasing::Render()
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
void BatChasing::Finalize()
{
}

/**
 * @brief 移動処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatChasing::Movement()
{
	//フレーム間時間
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();


	//自分からプレイヤーの角度を求める
	float radian = TKTLib::CaluculateRadian(m_bat->GetCurrentPosition(), m_pPlayer->GetCurrentPosition());
	//目標の角度
	DirectX::SimpleMath::Quaternion rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, radian);

	//現在の角度と目標の角度の差分
	//DirectX::SimpleMath::Quaternion diff = rotate - m_bat->GetQuaternion();

	DirectX::SimpleMath::Vector3 velocity = m_bat->GetVelocity();
	//目標に向かう
	DirectX::SimpleMath::Vector3 chaseSpeed = Character::MOVE::FRONT * CHASE_SPPED * elapsedTime;
	velocity += DirectX::SimpleMath::Vector3::Transform(chaseSpeed, rotate);


	//摩擦
	velocity *= World::GROUND_FRICTION;
	//重力
	velocity.y += World::GRAVITY * elapsedTime;
	//速度を設定
	m_bat->SetVelocity(velocity);
	//座標更新
	m_bat->SetPosition(m_bat->GetPosition() + m_bat->GetVelocity());

	// 姿勢に回転を加える
	m_bat->SetQuaternion(rotate);
}

/**
 * @brief 状態遷移判定
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatChasing::CheckStateTransition()
{
	//プレイヤーが範囲外にでて一定時間経ったら待機状態へ遷移
	float distance = DirectX::SimpleMath::Vector3::Distance(m_pPlayer->GetCurrentPosition(), m_bat->GetCurrentPosition());
	//範囲外なら遷移
	if (distance > Bat::CHASE_RANGE)
	{
		//待機状態へ
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::IDLING);
		return;
	}
	//攻撃範囲に入っていたら攻撃準備状態へ遷移
	if (distance < ATTACK_RANGE)
	{
		//攻撃準備状態へ
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::ATTACKPREPARING);
		return;
	}
}