/**
 * @file   PlayerAirSpenningMotion.cpp
 *
 * @brief  プレイヤーの空中回転攻撃のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/30
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PlayerAirSpenningMotion.h"
#include"Game/Object/Player/Hand.h"
#include"Game/Object/Player/Player.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pPlayer     プレイヤーのポインタ
 * @param[in] pRightHand　右手のポインタ
 * @param[in] pLeftHand　 左手のポインタ
 */
PlayerAirSpenningMotion::PlayerAirSpenningMotion(Player* pPlayer, Hand* pRightHand, Hand* pLeftHand)
	: AttackMotion{ AIR_SPIN_MOTION_MODIFIER }
	, m_pPlayer{ pPlayer }
	, m_pRightHand{ pRightHand }
	, m_pLeftHand{ pLeftHand }
{
	m_sound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::PLAYER_SPIN));
}



/**
 * @brief デストラクタ
 */
PlayerAirSpenningMotion::~PlayerAirSpenningMotion()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerAirSpenningMotion::Initialize()
{
	//つるはしを縦向きにさせる
	m_pRightHand->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);

	//頭の上に移動させる
	m_pRightHand->SetPosition(RIGHT_HAND_POS);
	m_pLeftHand->SetPosition(LEFT_HAND_POS);

	SetMotionLerp(0.0f);
	m_sound->Play(false);
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return true  攻撃終了
 * @return false 攻撃中
 */
bool PlayerAirSpenningMotion::Update()
{
	float motionLerp = GetMotionLerp();


	//手のモーションの角度を求める
	float angle = TKTLib::Lerp(HAND_START_MOTION_X_ANGLE, HAND_END_MOTION_X_ANGLE, motionLerp);
	DirectX::SimpleMath::Quaternion handMotionAngle
		= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, angle);

	m_pRightHand->SetMotionAngle(handMotionAngle);
	m_pLeftHand->SetMotionAngle(handMotionAngle);

	//プレイヤーのモーションの角度を求める
	m_pPlayer->SetMotionAngle(
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, 
			TKTLib::Lerp(PLAYER_START_MOTION_X_ANGLE, PLAYER_END_MOTION_X_ANGLE, motionLerp))
	);

	motionLerp += AIR_SPIN_MOTION_SPEED * Messenger::GetInstance()->GetElapsedTime();

	SetMotionLerp(std::min(motionLerp, Motion::MOTION_FINISH));

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
void PlayerAirSpenningMotion::Reset()
{
	//それぞれのオブジェクトを元の位置・角度に戻す
	m_pRightHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, Player::RIGHT_HAND_Z_ANGLE));
	m_pRightHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	m_pRightHand->SetPosition(Player::RIGHT_HAND_INIT_POS);

	m_pLeftHand->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftHand->SetPosition(Player::LEFT_HAND_INIT_POS);

	m_pPlayer->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);

}

