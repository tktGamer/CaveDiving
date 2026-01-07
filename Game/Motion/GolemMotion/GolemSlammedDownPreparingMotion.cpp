/**
 * @file   GolemSlammedDownPreparingMotion.cpp
 *
 * @brief  ゴーレムの叩きつけ攻撃の準備のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/30
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GolemSlammedDownPreparingMotion.h"
#include"Game/Object/Enemy/Golem/GolemHand.h"

#include"Game/Object/Enemy/Golem/Golem.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pGolem　ゴーレムのポインタ
 * @param[in] pRightGolemHand　ゴーレムの右手のポインタ
 * @param[in] pLeftGolemHand　 ゴーレムの左手のポインタ
 */
GolemSlammedDownPreparingMotion::GolemSlammedDownPreparingMotion(Golem* pGolem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand)
	: m_pGolem{ pGolem }
	, m_pRightGolemHand{ pRightGolemHand }
	, m_pLeftGolemHand{ pLeftGolemHand }
{

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
	//手の向きを変える
	m_pRightGolemHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX,SLAM_HAND_ANGLE));
	m_pLeftGolemHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX,SLAM_HAND_ANGLE));


	//スタート位置とゴール位置
	m_handStartPosition = m_pRightGolemHand->GetPosition();
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
	m_pRightGolemHand->SetPosition(currentPos);

	m_pLeftGolemHand->SetPosition(currentPos);

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

