/**
 * @file   BatDamageMotion.cpp
 *
 * @brief  コウモリのダメージリアクションモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/05
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "BatDamageMotion.h"
#include"Game/Common/Sound.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pRightWing　右羽のポインタ
 * @param[in] pLeftWing　 左羽のポインタ
 */
BatDamageMotion::BatDamageMotion(Bat* pBat)
	: m_pBat{pBat}
{
	m_wingSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound("wing.wav"));
}



/**
 * @brief デストラクタ
 */
BatDamageMotion::~BatDamageMotion()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatDamageMotion::Initialize()
{
	DirectX::SimpleMath::Quaternion angle = m_pBat->GetQuaternion();
	//少し斜めに向ける
	angle *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(5.0f));
	m_pBat->SetQuaternion(angle);

}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return true  攻撃終了
 * @return false 攻撃中
 */
bool BatDamageMotion::Update()
{


	float motionLerp = GetMotionLerp();

	DirectX::SimpleMath::Quaternion angle = m_pBat->GetQuaternion();
	//Y軸回転させる
	angle *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(360.0f * Messenger::GetInstance()->GetElapsedTime()));
	//float angle = TKTLib::Lerp(-20.0f, 20.0f, motionLerp);
	//DirectX::SimpleMath::Quaternion rightWingMotionAngle
	//	= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(angle));
	//DirectX::SimpleMath::Quaternion leftWingMotionAngle
	//	= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-angle));

	m_pBat->SetQuaternion(angle);


	motionLerp += 3.0f * Messenger::GetInstance()->GetElapsedTime();

	SetMotionLerp(std::min(motionLerp, 1.0f));

	if (GetMotionLerp() >= 1.0f)
	{
		m_wingSound->Play(false);
		

		SetMotionLerp(0.0f);
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
void BatDamageMotion::Reset()
{
	//それぞれのオブジェクトを元の位置・角度に戻す
	//m_pBat->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(0.0f)));
	//m_pRightWing->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	//m_pRightWing->SetPosition(DirectX::SimpleMath::Vector3{ 0.0f, 0.0f, 0.0f });

	//m_pLeftWing->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	//m_pLeftWing->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	//m_pLeftWing->SetPosition(DirectX::SimpleMath::Vector3{ 0.0f, 0.0f, 0.0f });

	//m_numLoop = 0;

	SetMotionLerp(0.0f);
}

