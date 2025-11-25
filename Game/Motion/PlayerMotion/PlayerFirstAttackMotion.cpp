/**
 * @file   PlayerFirstAttackMotion.cpp
 *
 * @brief  プレイヤーの第一攻撃のモーションに関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *　
 * @date   日付　2025/09/05
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PlayerFirstAttackMotion.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
PlayerFirstAttackMotion::PlayerFirstAttackMotion( Hand* pRightHand, Hand* pLeftHand)
	: AttackMotion{0.9f}
	, m_pRightHand{ pRightHand }
	, m_pLeftHand{pLeftHand}
	, m_isNextAttack{ false }
	, m_inputTime{1.0f}
{
	m_sound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound("pikelswing.wav"));
}



/**
 * @brief デストラクタ
 */
PlayerFirstAttackMotion::~PlayerFirstAttackMotion()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerFirstAttackMotion::Initialize()
{
	//真横に向ける
	m_pRightHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(-90.0f)));

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
bool PlayerFirstAttackMotion::Update()
{
	float motionLerp = GetMotionLerp();

	//今回の角度を計算
	float rightHandAngle = TKTLib::Lerp(0.0f,170.0f,motionLerp);
	float leftHandAngle  = TKTLib::Lerp(0.0f, 30.0f, motionLerp);

	DirectX::SimpleMath::Quaternion rightHandMotionAngle
		= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(rightHandAngle));

	DirectX::SimpleMath::Quaternion leftHandMotionAngle
		= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(leftHandAngle));


	motionLerp += 5.0f * Messenger::GetInstance()->GetElapsedTime();

	m_pRightHand->SetMotionAngle(rightHandMotionAngle);
	m_pLeftHand->SetMotionAngle(leftHandMotionAngle);


	SetMotionLerp(std::min(motionLerp,1.0f));

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
void PlayerFirstAttackMotion::Reset()
{
	m_isNextAttack = false;
	SetMotionLerp(0.0f);
}

