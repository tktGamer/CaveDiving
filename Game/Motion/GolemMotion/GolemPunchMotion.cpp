/**
 * @file   GolemPunchMotion.cpp
 *
 * @brief  ゴーレムの攻撃のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"Game/Common/Sound.h"
#include "GolemPunchMotion.h"
#include"Game/Object/Enemy/Golem/Golem.h"
#include"Game/Object/Enemy/Golem/GolemHand.h"
#include"Game/Object/Enemy/Golem/GolemArm.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] golemObjectID　ゴーレムのオブジェクト番号
 */
GolemPunchMotion::GolemPunchMotion(const int& golemObjectID)
	: 
	AttackMotion{GOLEM_PUNCH_MOTION_MODIFIER},
	m_pGolem{},
	m_pRightGolemHand{},
	m_pLeftGolemHand{},
	m_startPosition{},
	m_goalPosition{},
	m_coolTime{},
	m_attackSound{}
{
	Messenger* messenger = Messenger::GetInstance();
	m_pGolem = messenger->GetObject(golemObjectID)->Cast<Golem>();
	m_pRightGolemArm = messenger->GetObject(golemObjectID + Golem::RIGHT_ARM_OBJ_NUMBER)->Cast<GolemArm>();
	m_pRightGolemHand = messenger->GetObject(golemObjectID + Golem::RIGHT_HAND_OBJ_NUMBER)->Cast<GolemHand>();
	m_pLeftGolemArm = messenger->GetObject(golemObjectID + Golem::LEFT_ARM_OBJ_NUMBER)->Cast<GolemArm>();
	m_pLeftGolemHand = messenger->GetObject(golemObjectID + Golem::LEFT_HAND_OBJ_NUMBER)->Cast<GolemHand>();

	m_attackSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::GOLEM_PUNCH));
}



/**
 * @brief デストラクタ
 */
GolemPunchMotion::~GolemPunchMotion()
{

}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemPunchMotion::Initialize()
{
	//スタート位置とゴール位置
	m_startPosition = m_pRightGolemArm->GetPosition();
	m_goalPosition  = m_startPosition + PUNCH_MOVE;
	//モーション値初期化
	SetMotionLerp(0.0f);

	m_attackSound->Play(false);
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return true  攻撃終了
 * @return false 攻撃中
 */
bool GolemPunchMotion::Update()
{
	float motionLerp = GetMotionLerp();


	//現在位置を求める
	DirectX::SimpleMath::Vector3 currentPos = DirectX::SimpleMath::Vector3::Lerp(m_startPosition, m_goalPosition, motionLerp);
	m_pRightGolemArm->SetPosition(currentPos);
	//手の角度を求める
	DirectX::SimpleMath::Vector3 angle = DirectX::SimpleMath::Vector3::Lerp(START_MOTION_ANGLE, END_MOTION_ANGLE, motionLerp);
	m_pRightGolemHand->SetLocalRotationEuler(angle);
	//モーション進行
	motionLerp +=  PUNCH_MOTION_SPEED * Messenger::GetInstance()->GetElapsedTime();
	SetMotionLerp(std::min(motionLerp, Motion::MOTION_FINISH));

	//モーションが終了したら
	if (GetMotionLerp() >= Motion::MOTION_FINISH)
	{
		//隙の時間
		m_coolTime += Messenger::GetInstance()->GetElapsedTime();
		if (m_coolTime > COOL_TIME)
		{
			return true;
		}
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
void GolemPunchMotion::Reset()
{
	//それぞれのオブジェクトを元の位置・角度に戻す
	m_pGolem->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	m_pRightGolemArm->SetPosition(Golem::GOLEM_RIGHT_ARM_INIT_POS);
	m_pLeftGolemArm->SetPosition(Golem::GOLEM_LEFT_ARM_INIT_POS);
	//前に向けていたのを下に向ける
	m_pRightGolemArm->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftGolemArm->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	m_pRightGolemHand->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
}