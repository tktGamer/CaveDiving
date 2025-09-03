/**
 * @file   AttackMotion.cpp
 *
 * @brief  攻撃のモーションに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "AttackMotion.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
AttackMotion::AttackMotion(Hand* pRightHand, Hand* pLeftHand)
	:m_pRightHand{pRightHand}
	, m_pLeftHand{pLeftHand}
	, m_isNextAttack{ false }
	, m_attackType{ Attack::COMBO1 }
	, m_motionLerp{ 0.0f }
{

}



/**
 * @brief デストラクタ
 */
AttackMotion::~AttackMotion()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void AttackMotion::Initialize()
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
bool AttackMotion::Update()
{
	switch (m_attackType) 
	{
	case Attack::COMBO1:
			if (FirstAttack())
			{
				//攻撃ボタンを押していたら次の攻撃へ
				if (m_isNextAttack)
				{
					m_attackType = Attack::COMBO2;
					m_motionLerp = 0.0f;
					m_isNextAttack = false;
				}
				else 
				{
					//攻撃終了
					return true;
				}
			}
			break;
	case Attack::COMBO2:
			if (SecondAttack())
			{
				//攻撃ボタンを押していたら次の攻撃へ
				if (m_isNextAttack)
				{
					m_attackType = Attack::COMBO3;
					m_motionLerp = 0.0f;
					m_isNextAttack = false;

				}
				else
				{
					//攻撃終了
					return true;
				}
			}
			break;
	case Attack::COMBO3:
			if (ThirdAttack())
			{

				//攻撃終了
				return true;
			}
			break;
	}

	//攻撃中はfalseを返す
	return false;
}





/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void AttackMotion::Reset()
{
	m_isNextAttack = false;
	m_attackType = Attack::COMBO1;
	m_motionLerp = 0.0f;
}

bool AttackMotion::FirstAttack()
{
	DirectX::SimpleMath::Quaternion start = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	DirectX::SimpleMath::Quaternion end = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(170.0f));
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;
	//	//* DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(45.0f))
	//	//* DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(45.0f))
	//	DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(-90.0f));

	//q = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	//q = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(145.0f));

	DirectX::SimpleMath::Quaternion::Lerp(start, end, m_motionLerp, q);
	m_motionLerp += 5.0f * Messenger::GetInstance()->GetElapsedTime();
	//m_pHand->SetQuaternion()
	m_pRightHand->SetMotionAngle(q);


	if (m_motionLerp >= 1.0f)
	{
		return true;
	}
	return false;
}

bool AttackMotion::SecondAttack()
{
	DirectX::SimpleMath::Quaternion start = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(170.0f));
	DirectX::SimpleMath::Quaternion end = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;

	DirectX::SimpleMath::Quaternion::Lerp(start, end, m_motionLerp, q);
	m_motionLerp += 5.0f * Messenger::GetInstance()->GetElapsedTime();

	m_pRightHand->SetMotionAngle(q);


	if (m_motionLerp >= 1.0f)
	{
		return true;
	}
	return false;
}

bool AttackMotion::ThirdAttack()
{
	DirectX::SimpleMath::Quaternion start = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	DirectX::SimpleMath::Quaternion end = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(170.0f));
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(TKTLib::Lerp(0.0f, 360.0f, m_motionLerp)));

	//DirectX::SimpleMath::Quaternion::Lerp(start, end, m_motionLerp, q);
	m_motionLerp += 4.0f * Messenger::GetInstance()->GetElapsedTime();

	m_pRightHand->SetMotionAngle(q);


	if (m_motionLerp >= 1.0f)
	{
		return true;
	}
	return false;
}

void AttackMotion::SetIsNextAttack(bool isNext)
{
	m_isNextAttack = isNext;
}
