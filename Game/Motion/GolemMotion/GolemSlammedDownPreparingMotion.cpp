/**
 * @file   GolemSlammedDownPreparingMotion.cpp
 *
 * @brief  ゴーレムの叩きつけ攻撃の準備のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/01
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GolemSlammedDownPreparingMotion.h"
#include"Game/Object/Enemy/Golem/Golem.h"
#include"Game/Object/Enemy/Golem/GolemArm.h"
#include"Game/Object/Enemy/Golem/GolemHand.h"
#include"Game/Common/Sound.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in]  golemObjectID  ゴーレムのオブジェクト番号
 */
GolemSlammedDownPreparingMotion::GolemSlammedDownPreparingMotion(const int& golemObjectID)
	:
	m_pGolem{},  
	m_pRightGolemHand{},
	m_pLeftGolemHand{},
	m_handStartPosition{},
	m_handGoalPosition{},
	m_attackSound{}
{
	Messenger* messenger = Messenger::GetInstance();
	m_pGolem = messenger->GetObject(golemObjectID)->Cast<Golem>();
	m_pRightGolemArm = messenger->GetObject(golemObjectID + Golem::RIGHT_ARM_OBJ_NUMBER)->Cast<GolemArm>();
	m_pRightGolemHand = messenger->GetObject(golemObjectID + Golem::RIGHT_HAND_OBJ_NUMBER)->Cast<GolemHand>();
	m_pLeftGolemArm = messenger->GetObject(golemObjectID + Golem::LEFT_ARM_OBJ_NUMBER)->Cast<GolemArm>();
	m_pLeftGolemHand = messenger->GetObject(golemObjectID + Golem::LEFT_HAND_OBJ_NUMBER)->Cast<GolemHand>();

}

/**
 * @brief デストラクタ
 */
GolemSlammedDownPreparingMotion::~GolemSlammedDownPreparingMotion()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemSlammedDownPreparingMotion::Initialize()
{
	//スタート位置とゴール位置
	m_handStartPosition = m_pRightGolemArm->GetPosition();
	m_handGoalPosition = m_handStartPosition + SLAM_PREPARE_MOVE;

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
bool GolemSlammedDownPreparingMotion::Update()
{
	float motionLerp = GetMotionLerp();

	//現在位置を求める
	DirectX::SimpleMath::Vector3 currentPos = DirectX::SimpleMath::Vector3::Lerp(m_handStartPosition, m_handGoalPosition, motionLerp);
	//右手位置設定
	m_pRightGolemArm->SetPosition(currentPos);
	//右手基準なのでXを変える
	currentPos.x = -currentPos.x;
	//左手位置設定
	m_pLeftGolemArm->SetPosition(currentPos);

	//今回の角度を計算
	float handAngle = TKTLib::Lerp(ARM_START_MOTION_X_ANGLE, ARM_END_MOTION_X_ANGLE, motionLerp);

	//モーション角度設定
	m_pRightGolemArm->SetLocalRotationEuler({ handAngle,0.0f,0.0f });
	m_pLeftGolemArm->SetLocalRotationEuler({handAngle,0.0f,0.0f});

	//モーション値進行
	motionLerp +=  Messenger::GetInstance()->GetElapsedTime();
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
void GolemSlammedDownPreparingMotion::Reset()
{
}