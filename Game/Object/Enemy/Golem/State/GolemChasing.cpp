/**
 * @file   GolemChasing.cpp
 *
 * @brief  コウモリの追跡状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Golem/State/GolemChasing.h"
#include "Game/Object/Enemy/Golem/Golem.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] golem コウモリのポインタ
 */
GolemChasing::GolemChasing(Golem* golem)
	: m_golem(golem)
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

	DirectX::SimpleMath::Vector3 v = m_golem->GetVelocity();



	//自分からプレイヤーの角度を求める
	float radian = CaluculateRadian(m_golem->GetCurrentPosition(), m_pPlayer->GetCurrentPosition());
	//目標の角度
	DirectX::SimpleMath::Quaternion rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, radian);

	//現在の角度と目標の角度の差分
	DirectX::SimpleMath::Quaternion diff = rotate - m_golem->GetQuaternion();


	v += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3{ 0.0f,0.0f,-0.65f * elapsedTime }, rotate);

	//プレイヤーが範囲外にでて一定時間経ったら待機状態へ遷移
	float distance = DirectX::SimpleMath::Vector3::Distance(m_pPlayer->GetCurrentPosition(), m_golem->GetCurrentPosition());
	//範囲外なら遷移
	if (distance > 15.0f)
	{
		Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::IDLING);
	}
	//攻撃範囲に入っていたら攻撃準備状態へ遷移
	if (distance < 4.5f)
	{
		Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::ATTACKPREPARING);

	}


	v *= 0.95f;
	v.y += -0.8f * elapsedTime;

	m_golem->SetVelocity(v);

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

/**
 * @brief 二点のラジアン角を求める
 *
 * @param[in] eye    自分
 * @param[in] target 相手
 *
 * @return ラジアン角
 */
const float GolemChasing::CaluculateRadian(const DirectX::SimpleMath::Vector3& eye, const DirectX::SimpleMath::Vector3& target)
{

	//自分から相手の方向
	DirectX::SimpleMath::Vector3 direction = eye - target;
	direction.Normalize();

	// X-Z 平面上での角度を計算
	float angle = std::atan2(direction.x, direction.z);

	return angle;
}
