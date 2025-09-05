/**
 * @file   BatAttackMotion.cpp
 *
 * @brief  コウモリの攻撃のモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/05
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "BatAttackMotion.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pBat コウモリのポインタ
 */
BatAttackMotion::BatAttackMotion(Bat* pBat)
	: m_pBat{pBat}
{

}



/**
 * @brief デストラクタ
 */
BatAttackMotion::~BatAttackMotion()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttackMotion::Initialize()
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
bool BatAttackMotion::Update()
{
	float motionLerp = GetMotionLerp();


	//羽のモーションの角度を求める
	float angle = TKTLib::Lerp(0.0f, -110.0f, motionLerp);
	DirectX::SimpleMath::Quaternion handMotionAngle 
		= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(angle));

	 //m_pBat->SetMotionAngle(handMotionAngle);


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
void BatAttackMotion::Reset()
{
	//それぞれのオブジェクトを元の位置・角度に戻す
	//m_pBat->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));


	SetMotionLerp(0.0f);
}

