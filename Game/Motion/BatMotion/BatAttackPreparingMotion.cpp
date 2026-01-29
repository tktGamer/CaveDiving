/**
 * @file   BatAttackPreparingMotion.cpp
 *
 * @brief  コウモリの攻撃準備のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/25
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "BatAttackPreparingMotion.h"
#include"Game/Object/Enemy/Bat/Wing.h"

#include"Game/Common/Sound.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pRightWing　右羽のポインタ
 * @param[in] pLeftWing　 左羽のポインタ
 */
BatAttackPreparingMotion::BatAttackPreparingMotion(Wing* pRightWing, Wing* pLeftWing)
	: 
	m_pRightWing{ pRightWing },
	m_pLeftWing{pLeftWing},
	m_numLoop{},
	m_wingSound{}
{
	m_wingSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::BAT_WING));
}



/**
 * @brief デストラクタ
 */
BatAttackPreparingMotion::~BatAttackPreparingMotion()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttackPreparingMotion::Initialize()
{
	m_numLoop = 0;
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
bool BatAttackPreparingMotion::Update()
{
	//既定回数モーションを繰り返したら
	if (m_numLoop >= MOTION_LOOP)
	{
		return true;
	}


	float motionLerp = GetMotionLerp();


	//羽のモーションの角度を求める
	float angle = TKTLib::Lerp(WING_ANGLE_MIN, WING_ANGLE_MAX, motionLerp);
	//右羽
	DirectX::SimpleMath::Quaternion rightWingMotionAngle 
		= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, angle);
	//左羽
	DirectX::SimpleMath::Quaternion leftWingMotionAngle 
		= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, -angle);
	 //角度を設定
	 m_pRightWing->SetMotionAngle(rightWingMotionAngle);
	 m_pLeftWing->SetMotionAngle(leftWingMotionAngle);

	//モーション進行
	motionLerp += MOTION_SPEED * Messenger::GetInstance()->GetElapsedTime();
	SetMotionLerp(std::min(motionLerp, Motion::MOTION_FINISH));

	//完了したらループ
	if (GetMotionLerp() >= Motion::MOTION_FINISH)
	{
		m_wingSound->Play(false);
		m_numLoop++;

		SetMotionLerp(0.0f);
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
void BatAttackPreparingMotion::Reset()
{
	//それぞれのオブジェクトを元の位置・角度に戻す
	m_pRightWing->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftWing->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);

}

