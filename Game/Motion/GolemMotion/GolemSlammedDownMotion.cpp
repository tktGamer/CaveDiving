/**
 * @file   GolemSlammedDownMotion.cpp
 *
 * @brief  の攻撃のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/05
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GolemSlammedDownMotion.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pGolem のポインタ
 */
GolemSlammedDownMotion::GolemSlammedDownMotion(Golem* pGolem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand)
	: m_pGolem{ pGolem }
	, m_pRightGolemHand{ pRightGolemHand }
	, m_pLeftGolemHand{ pLeftGolemHand }
	,m_coolTime{0.0f}
{
	m_attackSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound("golemslam.wav"));

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
	m_rightHandStartPosition = m_pRightGolemHand->GetPosition();
	m_rightHandGoalPosition = m_pRightGolemHand->GetPosition() + DirectX::SimpleMath::Vector3{ 0.0f,-8.5f,0.0f };
	m_leftHandStartPosition = m_pLeftGolemHand->GetPosition();
	m_leftHandGoalPosition = m_pLeftGolemHand->GetPosition() + DirectX::SimpleMath::Vector3{ 0.0f,-8.5f,0.0f };

	m_coolTime = 0.0f;

	
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
	DirectX::SimpleMath::Vector3 currentPos = DirectX::SimpleMath::Vector3::Lerp(m_rightHandStartPosition, m_rightHandGoalPosition, motionLerp);
	m_pRightGolemHand->SetPosition(currentPos);

	currentPos = DirectX::SimpleMath::Vector3::Lerp(m_leftHandStartPosition, m_leftHandGoalPosition, motionLerp);
	m_pLeftGolemHand->SetPosition(currentPos);


	motionLerp += 2.0f * Messenger::GetInstance()->GetElapsedTime();

	SetMotionLerp(std::min(motionLerp, 1.0f));

	//モーションが終了したら
	if (GetMotionLerp() >= 1.0f)
	{
		m_attackSound->OncePlay(false);
		m_coolTime += Messenger::GetInstance()->GetElapsedTime();
		if (m_coolTime > 0.5f) 
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
	m_pRightGolemHand->SetPosition(DirectX::SimpleMath::Vector3{ 0.0f ,0.0f,0.0f });
	m_pLeftGolemHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftGolemHand->SetPosition(DirectX::SimpleMath::Vector3{ 0.0f ,0.0f,0.0f });


	SetMotionLerp(0.0f);
}

