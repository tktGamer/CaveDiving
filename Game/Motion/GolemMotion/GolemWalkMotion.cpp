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
	m_operate{1},
	m_attackSound{}
{
	Messenger* messenger = Messenger::GetInstance();
	m_pGolem = messenger->GetObject(golemObjectID)->Cast<Golem>();
	m_pRightGolemArm = messenger->GetObject(golemObjectID + Golem::RIGHT_ARM_OBJ_NUMBER)->Cast<GolemArm>();
	m_pRightGolemFot = messenger->GetObject(golemObjectID + Golem::RIGHT_FOT_OBJ_NUMBER)->Cast<GolemFot>();
	m_pLeftGolemArm = messenger->GetObject(golemObjectID + Golem::LEFT_ARM_OBJ_NUMBER)->Cast<GolemArm>();
	m_pLeftGolemFot = messenger->GetObject(golemObjectID + Golem::LEFT_FOT_OBJ_NUMBER)->Cast<GolemFot>();

	m_attackSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::GOLEM_SLAMMED_DOWN));
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
	//スタート位置とゴール位置
	//m_handStartPosition = m_pRightGolemArm->GetPosition();
	//m_handGoalPosition = m_handStartPosition + SLAMMED_DOWN_MOVE;
	//m_startAngle = m_pRightGolemArm->GetLocalEuler();
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
	//それぞれのオブジェクトを元の位置・角度に戻す
	//m_pGolem->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	//m_pRightGolemArm->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	//m_pRightGolemArm->SetPosition(Golem::GOLEM_RIGHT_ARM_INIT_POS);
	//m_pLeftGolemArm->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, Golem::LEFT_HAND_INIT_ANGLE));
	//m_pLeftGolemArm->SetPosition(Golem::GOLEM_LEFT_ARM_INIT_POS);
}