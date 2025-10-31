/**
 * @file   PlayerIdlingMotion.cpp
 *
 * @brief  プレイヤーの待機のモーションに関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *　
 * @date   日付　2025/09/05
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PlayerIdlingMotion.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
PlayerIdlingMotion::PlayerIdlingMotion( Hand* pRightHand, Hand* pLeftHand)
	: m_pRightHand{ pRightHand }
	, m_pLeftHand{pLeftHand}
	, m_operate{1}
{

}



/**
 * @brief デストラクタ
 */
PlayerIdlingMotion::~PlayerIdlingMotion()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerIdlingMotion::Initialize()
{
	//真横に向ける
	//m_pRightHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(-90.0f)));

	SetMotionLerp(0.5f);
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return true  終了
 * @return false 中
 */
bool PlayerIdlingMotion::Update()
{
	float motionLerp = GetMotionLerp();

	//今回の角度を計算

	//手を上下に動かす Y軸変化
	float rightHandY = TKTLib::Lerp(-0.06f, 0.1f, motionLerp);
	float leftHandY  = TKTLib::Lerp(-0.06f, 0.1f, motionLerp);

	//DirectX::SimpleMath::Quaternion rightHandMotionAngle
	//	= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(rightHandAngle));

	//DirectX::SimpleMath::Quaternion leftHandMotionAngle
	//	= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(leftHandAngle));


	motionLerp += m_operate * Messenger::GetInstance()->GetElapsedTime();

	DirectX::SimpleMath::Vector3 pos = m_pRightHand->GetPosition();
	pos.y = rightHandY;
	m_pRightHand->SetPosition(pos);
	pos = m_pLeftHand->GetPosition();
	pos.y = leftHandY;
	m_pLeftHand->SetPosition(pos);


	SetMotionLerp(std::min(motionLerp,1.0f));

	if (std::abs(GetMotionLerp()) >= 1.0f)
	{
		m_operate *= -1;
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
void PlayerIdlingMotion::Reset()
{
	DirectX::SimpleMath::Vector3 pos = m_pRightHand->GetPosition();
	pos.y = 0.0f;
	m_pRightHand->SetPosition(pos);
	pos = m_pLeftHand->GetPosition();
	pos.y = 0.0f;
	m_pLeftHand->SetPosition(pos);

	SetMotionLerp(0.0f);
}

