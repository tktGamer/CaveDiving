/**
 * @file   PlayerThirdAttackMotion.cpp
 *
 * @brief  プレイヤーの第三攻撃のモーションに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PlayerThirdAttackMotion.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
PlayerThirdAttackMotion::PlayerThirdAttackMotion(Hand* pRightHand, Hand* pLeftHand)
	: m_pRightHand{ pRightHand }
	,m_pLeftHand{pLeftHand}
	, m_isNextAttack{ false }
{
	m_sound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound("turnattack.wav"));

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
bool PlayerThirdAttackMotion::Update()
{
	float motionLerp = GetMotionLerp();

	float rightHandAngle = TKTLib::Lerp(0.0f, 360.0f, motionLerp);
	float leftHandAngle = TKTLib::Lerp(-177.0f, 190.0f, motionLerp);

	DirectX::SimpleMath::Quaternion rightHandMotionAngle
		= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(rightHandAngle));

	DirectX::SimpleMath::Quaternion leftHandMotionAngle
		= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(leftHandAngle));


	motionLerp += 4.0f * Messenger::GetInstance()->GetElapsedTime();

	m_pRightHand->SetMotionAngle(rightHandMotionAngle);
	m_pLeftHand->SetMotionAngle(leftHandMotionAngle);

	SetMotionLerp(std::min(motionLerp, 1.0f));

	if (GetMotionLerp() >= 1.0f)
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
	m_isNextAttack = false;
	SetMotionLerp(0.0f);
}

