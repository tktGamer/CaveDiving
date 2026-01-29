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
#include "GolemPunchMotion.h"
#include"Game/Object/Enemy/Golem/Golem.h"
#include"Game/Object/Enemy/Golem/GolemHand.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pGolem ゴーレムのポインタ
 * @param[in] pRightGolemHand 右手のポインタ
 * @param[in] pLeftGolemHand  左手のポインタ
 */
GolemPunchMotion::GolemPunchMotion(Golem* pGolem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand)
	: 
	AttackMotion{GOLEM_PUNCH_MOTION_MODIFIER},
	m_pGolem{ pGolem },
	m_pRightGolemHand{ pRightGolemHand },
	m_pLeftGolemHand{ pLeftGolemHand },
	m_startPosition{},
	m_goalPosition{},
	m_coolTime{},
	m_attackSound{}
{
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
	m_startPosition = m_pRightGolemHand->GetPosition();
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
	m_pRightGolemHand->SetPosition(currentPos);

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
	m_pRightGolemHand->SetPosition(Golem::RIGHTHAND_INIT_POS);
	m_pLeftGolemHand->SetPosition(Golem::LEFTHAND_INIT_POS);
	//前に向けていたのを下に向ける
	m_pRightGolemHand->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftGolemHand->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
}