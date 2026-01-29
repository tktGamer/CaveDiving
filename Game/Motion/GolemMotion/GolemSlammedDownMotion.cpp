/**
 * @file   GolemSlammedDownMotion.cpp
 *
 * @brief  叩きつけの攻撃のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GolemSlammedDownMotion.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pGolem		  ゴーレムのポインタ
 * @param[in] pRightGolemHand 右手のポインタ
 * @param[in] pLeftGolemHand  左手のポインタ
 */
GolemSlammedDownMotion::GolemSlammedDownMotion(Golem* pGolem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand)
	: 
	AttackMotion{ GOLEM_SLAMMED_DOWN_MOTION_MODIFIER },
	m_pGolem{ pGolem },
	m_pRightGolemHand{ pRightGolemHand },
	m_pLeftGolemHand{ pLeftGolemHand },
	m_handStartPosition{},
	m_handGoalPosition{},
	m_coolTime{},
	m_attackSound{}
{
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
	m_handStartPosition = m_pRightGolemHand->GetPosition();
	m_handGoalPosition  = m_handStartPosition + SLAMMED_DOWN_MOVE;

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
	m_pRightGolemHand->SetPosition(currentPos);
	//右手基準なのでXを変える
	currentPos.x = -currentPos.x;
	m_pLeftGolemHand->SetPosition(currentPos);

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
	m_pRightGolemHand->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	m_pRightGolemHand->SetPosition(Golem::RIGHTHAND_INIT_POS);
	m_pLeftGolemHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftGolemHand->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftGolemHand->SetPosition(Golem::LEFTHAND_INIT_POS);
}