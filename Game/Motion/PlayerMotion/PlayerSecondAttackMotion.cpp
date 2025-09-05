/**
 * @file   PlayerSecondAttackMotion.cpp
 *
 * @brief  プレイヤーの第二攻撃のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/05
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PlayerSecondAttackMotion.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
PlayerSecondAttackMotion::PlayerSecondAttackMotion(Hand* pRightHand)
	: m_pRightHand{ pRightHand }
	,m_pLeftHand{}
	, m_isNextAttack{ false }
{

}



/**
 * @brief デストラクタ
 */
PlayerSecondAttackMotion::~PlayerSecondAttackMotion()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerSecondAttackMotion::Initialize()
{

}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return true  攻撃終了
 * @return false 攻撃中
 */
bool PlayerSecondAttackMotion::Update()
{
	float motionLerp = GetMotionLerp();


	DirectX::SimpleMath::Quaternion start = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(170.0f));
	DirectX::SimpleMath::Quaternion end = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;

	DirectX::SimpleMath::Quaternion::Lerp(start, end, motionLerp, q);
	motionLerp += 5.0f * Messenger::GetInstance()->GetElapsedTime();

	m_pRightHand->SetMotionAngle(q);
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
void PlayerSecondAttackMotion::Reset()
{
	m_isNextAttack = false;
	SetMotionLerp(0.0f);
}

