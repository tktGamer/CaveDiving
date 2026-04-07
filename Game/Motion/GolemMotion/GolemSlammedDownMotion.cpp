/**
 * @file   GolemSlammedDownMotion.cpp
 *
 * @brief  叩きつけの攻撃のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/02
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GolemSlammedDownMotion.h"
#include "Game/Object/Enemy/Golem/Golem.h"
#include "Game/Object/Enemy/Golem/GolemArm.h"
#include"Game/Object/Enemy/Golem/GolemHand.h"
#include"Game/Common/Sound.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] golemObjectID  ゴーレムのオブジェクト番号
 */
GolemSlammedDownMotion::GolemSlammedDownMotion(const int& golemObjectID)
	: 
	AttackMotion{ GOLEM_SLAMMED_DOWN_MOTION_MODIFIER },
	m_pGolem{},
	m_pRightGolemHand{},
	m_pLeftGolemHand{},
	m_handStartPosition{},
	m_handGoalPosition{},
	m_coolTime{},
	m_attackSound{}
{
	Messenger* messenger = Messenger::GetInstance();
	m_pGolem = messenger->GetObject(golemObjectID)->Cast<Golem>();
	m_pRightGolemArm = messenger->GetObject(golemObjectID + Golem::RIGHT_ARM_OBJ_NUMBER)->Cast<GolemArm>();
	m_pRightGolemHand = messenger->GetObject(golemObjectID + Golem::RIGHT_HAND_OBJ_NUMBER)->Cast<GolemHand>();
	m_pLeftGolemArm = messenger->GetObject(golemObjectID + Golem::LEFT_ARM_OBJ_NUMBER)->Cast<GolemArm>();
	m_pLeftGolemHand = messenger->GetObject(golemObjectID + Golem::LEFT_HAND_OBJ_NUMBER)->Cast<GolemHand>();

	m_attackSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::GOLEM_SLAMMED_DOWN));
}

/**
 * @brief デストラクタ
 */
GolemSlammedDownMotion::~GolemSlammedDownMotion()
{

}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemSlammedDownMotion::Initialize()
{
	//スタート位置とゴール位置
	m_handStartPosition = m_pRightGolemArm->GetPosition();
	m_handGoalPosition = m_handStartPosition + SLAMMED_DOWN_MOVE;
	m_startAngle = m_pRightGolemArm->GetLocalEuler();
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
bool GolemSlammedDownMotion::Update()
{
	float motionLerp = GetMotionLerp();


	//現在位置を求める
	DirectX::SimpleMath::Vector3 currentPos = DirectX::SimpleMath::Vector3::Lerp(m_handStartPosition, m_handGoalPosition, motionLerp);
	m_pRightGolemArm->SetPosition(currentPos);
	//右手基準なのでXを変える
	currentPos.x = -currentPos.x;
	m_pLeftGolemArm->SetPosition(currentPos);


	//今回の角度を計算
	float handAngle = TKTLib::Lerp(m_startAngle.x, ARM_END_MOTION_X_ANGLE, motionLerp);

	//角度設定
	m_pRightGolemArm->SetLocalRotationEuler({ handAngle,0.0f,0.0f });
	m_pLeftGolemArm->SetLocalRotationEuler({ handAngle,0.0f,0.0f });


	//モーション値進行
	motionLerp += SLAMMED_MOTION_SPEED * Messenger::GetInstance()->GetElapsedTime();

	SetMotionLerp(std::min(motionLerp, Motion::MOTION_FINISH));

	//モーションが終了したら
	if (GetMotionLerp() >= Motion::MOTION_FINISH)
	{
		m_attackSound->OncePlay(false);
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
void GolemSlammedDownMotion::Reset()
{
	//それぞれのオブジェクトを元の位置・角度に戻す
	m_pGolem->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	m_pRightGolemArm->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	m_pRightGolemArm->SetPosition(Golem::GOLEM_RIGHT_ARM_INIT_POS);
	m_pLeftGolemHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftGolemArm->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, Golem::LEFT_HAND_INIT_ANGLE));
	m_pLeftGolemArm->SetPosition(Golem::GOLEM_LEFT_ARM_INIT_POS);
}