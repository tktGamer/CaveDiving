/**
 * @file   BatAttackPreparingMotion.cpp
 *
 * @brief  コウモリの攻撃準備のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/05
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "BatAttackPreparingMotion.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pRightWing　右羽のポインタ
 * @param[in] pLeftWing　 左羽のポインタ
 */
BatAttackPreparingMotion::BatAttackPreparingMotion(Wing* pRightWing, Wing* pLeftWing)
	: m_pRightWing{ pRightWing }
	, m_pLeftWing{pLeftWing}
{

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
	//
	//m_pRightWing->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(0.0f)));

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
	float motionLerp = GetMotionLerp();


	//羽のモーションの角度を求める
	float angle = TKTLib::Lerp(0.0f, -110.0f, motionLerp);
	DirectX::SimpleMath::Quaternion handMotionAngle 
		= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(angle));

	 m_pRightWing->SetMotionAngle(handMotionAngle);
	 m_pLeftWing->SetMotionAngle(handMotionAngle);


	motionLerp += 3.0f * Messenger::GetInstance()->GetElapsedTime();

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
void BatAttackPreparingMotion::Reset()
{
	//それぞれのオブジェクトを元の位置・角度に戻す
	m_pRightWing->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(-50.0f)));
	m_pRightWing->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	m_pRightWing->SetPosition(DirectX::SimpleMath::Vector3{ 0.0f, 0.0f, 0.0f });

	m_pLeftWing->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftWing->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	m_pLeftWing->SetPosition(DirectX::SimpleMath::Vector3{ 0.0f, 0.0f, 0.0f });


	SetMotionLerp(0.0f);
}

