/**
 * @file   PlayerThirdAttackMotion.cpp
 *
 * @brief  プレイヤーの第三攻撃のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PlayerThirdAttackMotion.h"
#include"Game/Object/Player/Hand.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pRightHand　右手のポインタ
 * @param[in] pLeftHand　 左手のポインタ
 * 
 */
PlayerThirdAttackMotion::PlayerThirdAttackMotion(Hand* pRightHand, Hand* pLeftHand)
	: 
	AttackMotion{THIRD_ATTACK_MOTION_MODIFIER},
	m_pRightHand{ pRightHand },
	m_pLeftHand{pLeftHand},
	m_sound{}
{
	m_sound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::PLAYER_SPIN));
}

/**
 * @brief デストラクタ
 */
PlayerThirdAttackMotion::~PlayerThirdAttackMotion()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerThirdAttackMotion::Initialize()
{
	//攻撃音再生
	m_sound->Play(false);

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
bool PlayerThirdAttackMotion::Update()
{
	float motionLerp = GetMotionLerp();

	//手のモーション角度を求める
	float rightHandAngle = TKTLib::Lerp(RIGHT_HAND_START_MOTION_Y_ANGLE, RIGHT_HAND_END_MOTION_Y_ANGLE, motionLerp);
	float leftHandAngle = TKTLib::Lerp(LEFT_HAND_START_MOTION_Y_ANGLE, LEFT_HAND_END_MOTION_Y_ANGLE, motionLerp);
	//クォータニオンにする
	DirectX::SimpleMath::Quaternion rightHandMotionAngle
		= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, rightHandAngle);

	DirectX::SimpleMath::Quaternion leftHandMotionAngle
		= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, leftHandAngle);
	//モーション角度設定
	m_pRightHand->SetMotionAngle(rightHandMotionAngle);
	m_pLeftHand->SetMotionAngle(leftHandMotionAngle);

	//モーション値進行
	motionLerp += THIRD_ATTACK_MOTION_SPEED * Messenger::GetInstance()->GetElapsedTime();
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
void PlayerThirdAttackMotion::Reset()
{
}