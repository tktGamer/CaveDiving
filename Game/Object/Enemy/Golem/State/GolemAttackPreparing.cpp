/**
 * @file   GolemAttackPreparing.cpp
 *
 * @brief  ゴーレムの攻撃準備状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/09/03
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Golem/State/GolemAttackPreparing.h"
#include "Game/Object/Enemy/Golem/Golem.h"
#include"Game//Object/Player/Player.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] golem ゴーレムのポインタ
 */
GolemAttackPreparing::GolemAttackPreparing(Golem* golem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand)
	:m_golem(golem)
	, m_pRightHand{pRightGolemHand}
	,m_pLeftHand{pLeftGolemHand}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();


}
/**
 * @brief デストラクタ
 */
GolemAttackPreparing::~GolemAttackPreparing()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttackPreparing::Initialize()
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
void GolemAttackPreparing::PreUpdate()
{
	DecideMotion();
	m_attackPreparingMotion->Initialize();

}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttackPreparing::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	GameObject* pPlayer = Messenger::GetInstance()->GetObject(0);

	//自分からプレイヤーの角度を求める
	float radian = CaluculateRadian(m_golem->GetCurrentPosition(), pPlayer->GetCurrentPosition());
	//目標の角度
	DirectX::SimpleMath::Quaternion rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, radian);

	//現在の角度と目標の角度の差分
	//DirectX::SimpleMath::Quaternion diff = rotate - m_golem->GetQuaternion();

	m_golem->SetQuaternion(rotate);


	//攻撃予備モーションが終わったら攻撃状態へ遷移
	if (m_attackPreparingMotion->Update())
	{
		Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::MessageID::GROUNDATTACK);
	}

}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttackPreparing::PostUpdate()
{
	m_attackPreparingMotion->Reset();
	m_golem->ResetFrameCount();

}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttackPreparing::Render()
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
void GolemAttackPreparing::Finalize()
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
const float GolemAttackPreparing::CaluculateRadian(const DirectX::SimpleMath::Vector3& eye, const DirectX::SimpleMath::Vector3& target)
{

	//自分から相手の方向
	DirectX::SimpleMath::Vector3 direction = eye - target;
	direction.Normalize();

	// X-Z 平面上での角度を計算
	float angle = std::atan2(direction.x, direction.z);

	return angle;
}

void GolemAttackPreparing::DecideMotion()
{
	switch (m_golem->GetAttackMessage()) 
	{
	case Message::AttackMesssage::ATTACKTYPE_ONE:
		m_attackPreparingMotion = std::make_unique<GolemPunchPreparingMotion>(m_golem, m_pRightHand, m_pLeftHand);
		break;
	case Message::AttackMesssage::ATTACKTYPE_TWO:
		m_attackPreparingMotion = std::make_unique<GolemSlammedDownPreparingMotion>(m_golem, m_pRightHand, m_pLeftHand);

		break;
	}
}
