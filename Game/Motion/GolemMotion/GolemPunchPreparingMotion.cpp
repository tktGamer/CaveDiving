/**
 * @file   GolemPunchPreparingMotion.cpp
 *
 * @brief  ゴーレムのパンチ攻撃の準備のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GolemPunchPreparingMotion.h"
#include"Game/Object/Enemy/Golem/Golem.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pGilem　ゴーレムのポインタ
 * @param[in] pRightGolemHand　右手のポインタ
 * @param[in] pLeftGolemHand　 左手のポインタ
 */
GolemPunchPreparingMotion::GolemPunchPreparingMotion(const int& golemObjectID)
	:
	m_pGolem{},
	m_pRightGolemArm{},
	m_pRightGolemHand{},
	m_pLeftGolemArm{},
	m_pLeftGolemHand{},
	m_startPosition{},
	m_goalPosition{}
{
	Messenger* messenger = Messenger::GetInstance();
	m_pGolem = messenger->GetObject(golemObjectID)->Cast<Golem>();
	m_pRightGolemArm  = messenger->GetObject(golemObjectID + Golem::RIGHT_ARM_OBJ_NUMBER)->Cast<GolemArm>();
	m_pRightGolemHand = messenger->GetObject(golemObjectID + Golem::RIGHT_HAND_OBJ_NUMBER)->Cast<GolemHand>();
	m_pLeftGolemArm   = messenger->GetObject(golemObjectID + Golem::LEFT_ARM_OBJ_NUMBER)->Cast<GolemArm>();
	m_pLeftGolemHand  = messenger->GetObject(golemObjectID + Golem::LEFT_HAND_OBJ_NUMBER)->Cast<GolemHand>();
}

/**
 * @brief デストラクタ
 */
GolemPunchPreparingMotion::~GolemPunchPreparingMotion()
{

}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemPunchPreparingMotion::Initialize()
{
	//手の向きを変える 正面に向ける
	m_pRightGolemArm->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, PUNCH_HAND_ANGLE));
	//スタート位置とゴール位置
	m_startPosition = m_pRightGolemArm->GetPosition();
	m_goalPosition  = m_startPosition + HAND_GOAL_POS;

	SetMotionLerp(0.0f);
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return true  攻撃終了
 * @return false 攻撃中
 */
bool GolemPunchPreparingMotion::Update()
{

	float motionLerp = GetMotionLerp();

	//現在位置を求める
	DirectX::SimpleMath::Vector3 currentPos = DirectX::SimpleMath::Vector3::Lerp(m_startPosition, m_goalPosition, motionLerp);
	m_pRightGolemArm->SetPosition(currentPos);

	//モーション進行	
	motionLerp += Messenger::GetInstance()->GetElapsedTime();

	SetMotionLerp(std::min(motionLerp, Motion::MOTION_FINISH));

	//モーションが終了したら
	if (GetMotionLerp() >= Motion::MOTION_FINISH)
	{
		return true;
	}

	return false;
}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemPunchPreparingMotion::Reset()
{
}