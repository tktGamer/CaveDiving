/**
 * @file   BatAttackMotion.cpp
 *
 * @brief  コウモリの攻撃のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/25
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "BatAttackMotion.h"
#include"Game/Object/Enemy/Bat/Bat.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pBat		 コウモリのポインタ
 * @param[in] pRightWing コウモリの右羽ポインタ
 * @param[in] pLeftWing コウモリの左羽ポインタ
 */
BatAttackMotion::BatAttackMotion(Bat* pBat, Wing* pRightWing, Wing* pLeftWing)
	: 
	AttackMotion{BAT_ATTACK_MOTION_MODIFIER},
	m_pBat{pBat},
	m_pRightWing{pRightWing},
	m_pLeftWing{pLeftWing}
{

}

/**
 * @brief デストラクタ
 */
BatAttackMotion::~BatAttackMotion()
{

}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttackMotion::Initialize()
{
	//攻撃の姿勢にする
	m_pBat->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::UnitX, BAT_ATTACK_MOTION_INIT_ANGLE));
	m_pRightWing->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::UnitY, RIGHT_WING_ATTACK_MOTION_INIT_ANGLE));
	m_pLeftWing->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::UnitY, LEFT_WING_ATTACK_MOTION_INIT_ANGLE));


	//突進させる
	DirectX::SimpleMath::Vector3 speed = Character::MOVE::FRONT * BAT_ATTACK_SPEED * Messenger::GetInstance()->GetElapsedTime();
	m_pBat->SetVelocity(DirectX::SimpleMath::Vector3::Transform(speed, m_pBat->GetCurrentQuaternion()));

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
bool BatAttackMotion::Update()
{
	float motionLerp = GetMotionLerp();


	//時間経過
	motionLerp += Messenger::GetInstance()->GetElapsedTime();

	SetMotionLerp(std::min(motionLerp, Motion::MOTION_FINISH));
	//モーションが完了したら
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
void BatAttackMotion::Reset()
{
	//それぞれのオブジェクトを元の位置・角度に戻す
	m_pBat->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	m_pRightWing->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftWing->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);


}