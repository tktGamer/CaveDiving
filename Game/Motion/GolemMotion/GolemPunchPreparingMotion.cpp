/**
 * @file   GolemPunchPreparingMotion.cpp
 *
 * @brief  コウモリの攻撃準備のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/05
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GolemPunchPreparingMotion.h"

#include"Game/Object/Enemy/Golem/Golem.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pRightGolemHand　右羽のポインタ
 * @param[in] pLeftGolemHand　 左羽のポインタ
 */
GolemPunchPreparingMotion::GolemPunchPreparingMotion(Golem* pGolem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand)
	: m_pGolem{pGolem}
	,m_pRightGolemHand{ pRightGolemHand }
	, m_pLeftGolemHand{ pLeftGolemHand }
{

}



/**
 * @brief デストラクタ
 */
GolemPunchPreparingMotion::~GolemPunchPreparingMotion()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemPunchPreparingMotion::Initialize()
{
	//手の向きを変える
	m_pRightGolemHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(90.0f)));

	
	//スタート位置とゴール位置
	m_startPosition = m_pRightGolemHand->GetPosition();
	m_goalPosition = m_pRightGolemHand->GetPosition() + DirectX::SimpleMath::Vector3{ 0.0f,1.0f,6.0f };
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return true  攻撃終了
 * @return false 攻撃中
 */
bool GolemPunchPreparingMotion::Update()
{


	float motionLerp = GetMotionLerp();


	//現在位置を求める
	DirectX::SimpleMath::Vector3 currentPos = DirectX::SimpleMath::Vector3::Lerp(m_startPosition, m_goalPosition, motionLerp);
	m_pRightGolemHand->SetPosition(currentPos);

	
	motionLerp += 1.0f* Messenger::GetInstance()->GetElapsedTime();

	SetMotionLerp(std::min(motionLerp, 1.0f));

	//モーションが終了したら
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
void GolemPunchPreparingMotion::Reset()
{
	//それぞれのオブジェクトを元の位置・角度に戻す
	//m_pRightGolemHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(0.0f)));
	//m_pRightGolemHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	////m_pRightGolemHand->SetPosition(DirectX::SimpleMath::Vector3{ 0.0f, 0.0f, 0.0f });

	//m_pLeftGolemHand->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	//m_pLeftGolemHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	////m_pLeftGolemHand->SetPosition(DirectX::SimpleMath::Vector3{ 0.0f, 0.0f, 0.0f });


	SetMotionLerp(0.0f);
}

