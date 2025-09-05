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
PlayerFirstAttackMotion::PlayerFirstAttackMotion( Hand* pRightHand)
	: m_pRightHand{ pRightHand }
	, m_isNextAttack{ false }
	,m_inputTime{1.0f}
{

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

	DirectX::SimpleMath::Quaternion start = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	DirectX::SimpleMath::Quaternion end = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(170.0f));
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;

	DirectX::SimpleMath::Quaternion::Lerp(start, end, motionLerp, q);
	motionLerp += 5.0f * Messenger::GetInstance()->GetElapsedTime();

	m_pRightHand->SetMotionAngle(q);

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

