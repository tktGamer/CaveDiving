/**
 * @file   PlayerSlamAttackMotion.cpp
 *
 * @brief  プレイヤーの叩きつけ攻撃のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PlayerSlamAttackMotion.h"
#include"Game/Object/Player/Hand.h"
#include"Game/Object/Player/Player.h"
#include"Game/Common/Sound.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pPlayer     プレイヤーのポインタ
 * @param[in] pRightHand　右手のポインタ
 * @param[in] pLeftHand　 左手のポインタ
 * 
 */
PlayerSlamAttackMotion::PlayerSlamAttackMotion(Player* pPlayer, Hand* pRightHand, Hand* pLeftHand)
	: 
	AttackMotion{ SLAMMED_ATTACK_MOTION_MODIFIER },
	m_pPlayer{pPlayer},
	m_pRightHand{ pRightHand },
	m_pLeftHand{pLeftHand},
	m_sound{}
{
}

/**
 * @brief デストラクタ
 */
PlayerSlamAttackMotion::~PlayerSlamAttackMotion()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerSlamAttackMotion::Initialize()
{
	//つるはしを縦向きにさせる
	m_pRightHand->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	//頭の上に移動させる
	m_pRightHand->SetPosition(RIGHT_HAND_POS);
	m_pLeftHand->SetPosition(LEFT_HAND_POS);

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
bool PlayerSlamAttackMotion::Update()
{
	float motionLerp = GetMotionLerp();
	//手のモーションの角度を求める
	float angle = TKTLib::Lerp(HAND_START_MOTION_X_ANGLE, HAND_END_MOTION_X_ANGLE, motionLerp);
	DirectX::SimpleMath::Quaternion handMotionAngle 
		= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, angle);
	//モーション角度設定
	 m_pRightHand->SetMotionAngle(handMotionAngle);
	 m_pLeftHand->SetMotionAngle(handMotionAngle);

	 //プレイヤーのモーションの角度を求める
	 m_pPlayer->SetMotionAngle(
		 DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			 DirectX::SimpleMath::Vector3::UnitX,
			 TKTLib::Lerp(PLAYER_START_MOTION_X_ANGLE, PLAYER_END_MOTION_X_ANGLE, motionLerp))
	 );

	 //モーション値進行
	motionLerp += SLAMMED_ATTACK_MOTION_SPEED * Messenger::GetInstance()->GetElapsedTime();
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
void PlayerSlamAttackMotion::Reset()
{
	//それぞれのオブジェクトを元の位置・角度に戻す
	//右手
	m_pRightHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, Player::RIGHT_HAND_Z_ANGLE));
	m_pRightHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	m_pRightHand->SetPosition(Player::RIGHT_HAND_INIT_POS);
	//左手
	m_pLeftHand->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftHand->SetPosition(Player::LEFT_HAND_INIT_POS);
	//プレイヤー
	m_pPlayer->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
}