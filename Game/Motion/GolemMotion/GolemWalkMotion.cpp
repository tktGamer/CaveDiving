/**
 * @file   GolemWalkMotion.cpp
 *
 * @brief  ゴーレムの歩行のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/02
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GolemWalkMotion.h"
#include"Game/Object/Enemy/Golem/Golem.h"
#include"Game/Object/Enemy/Golem/GolemFot.h"
#include"Game/Object/Enemy/Golem/GolemArm.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] golemObjectID  ゴーレムのオブジェクト番号
 */
GolemWalkMotion::GolemWalkMotion(const int& golemObjectID)
	: 
	Motion{},
	m_pGolem{},
	m_pRightGolemArm{},
	m_pRightGolemFot{},
	m_pLeftGolemArm{},
	m_pLeftGolemFot{},
	m_handStartPosition{},
	m_handGoalPosition{},
	m_coolTime{},
	m_operate{1}
{
	Messenger* messenger = Messenger::GetInstance();
	m_pGolem = messenger->GetObject(golemObjectID)->Cast<Golem>();
	m_pRightGolemArm = messenger->GetObject(golemObjectID + Golem::RIGHT_ARM_OBJ_NUMBER)->Cast<GolemArm>();
	m_pRightGolemFot = messenger->GetObject(golemObjectID + Golem::RIGHT_FOT_OBJ_NUMBER)->Cast<GolemFot>();
	m_pLeftGolemArm = messenger->GetObject(golemObjectID + Golem::LEFT_ARM_OBJ_NUMBER)->Cast<GolemArm>();
	m_pLeftGolemFot = messenger->GetObject(golemObjectID + Golem::LEFT_FOT_OBJ_NUMBER)->Cast<GolemFot>();
}

/**
 * @brief デストラクタ
 */
GolemWalkMotion::~GolemWalkMotion()
{

}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemWalkMotion::Initialize()
{
	m_coolTime = TKTLib::FLOAT_ZERO;

	SetMotionLerp(TKTLib::FLOAT_ZERO);

}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return true  攻撃終了
 * @return false 攻撃中
 */
bool GolemWalkMotion::Update()
{
	float motionLerp = GetMotionLerp();


	//現在位置を求める
	float currentPosZ = TKTLib::Lerp(MOTION_Z_POS_MIN, MOTION_Z_POS_MAX, motionLerp);

	DirectX::SimpleMath::Vector3 position = m_pRightGolemFot->GetPosition();
	position.z = currentPosZ;
	m_pRightGolemFot->SetPosition(position);
	//右手基準なのでXを変える
	position = m_pLeftGolemFot->GetPosition();
	position.z = -currentPosZ;
	m_pLeftGolemFot->SetPosition(position);



	//モーション進行
	motionLerp += m_operate * WALK_MOTION_SPEED * Messenger::GetInstance()->GetElapsedTime();
	SetMotionLerp(std::min(motionLerp, Motion::MOTION_FINISH));
	//モーションが完了したら
	if (std::abs(GetMotionLerp()) >= Motion::MOTION_FINISH)
	{
		//進行方向を逆にする
		m_operate = -m_operate;
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
void GolemWalkMotion::Reset()
{
}