/**
 * @file   PlayerAirSpenningMotion.cpp
 *
 * @brief  プレイヤーの叩きつけ攻撃のモーションに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PlayerAirSpenningMotion.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pPlayer     プレイヤーのポインタ
 * @param[in] pRightHand　右手のポインタ
 * @param[in] pLeftHand　 左手のポインタ
 */
PlayerAirSpenningMotion::PlayerAirSpenningMotion(Player* pPlayer, Hand* pRightHand, Hand* pLeftHand)
	: m_pPlayer{ pPlayer }
	, m_pRightHand{ pRightHand }
	, m_pLeftHand{ pLeftHand }
{

}



/**
 * @brief デストラクタ
 */
PlayerAirSpenningMotion::~PlayerAirSpenningMotion()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerAirSpenningMotion::Initialize()
{
	//つるはしを縦向きにさせる
	m_pRightHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(0.0f)));

	//頭の上に移動させる
	m_pRightHand->SetPosition(DirectX::SimpleMath::Vector3{ -1.5f,2.0f,0.0f });
	m_pLeftHand->SetPosition(DirectX::SimpleMath::Vector3{ 1.45f,2.0f,0.0f });
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return true  攻撃終了
 * @return false 攻撃中
 */
bool PlayerAirSpenningMotion::Update()
{
	float motionLerp = GetMotionLerp();


	//手のモーションの角度を求める
	float angle = TKTLib::Lerp(0.0f, -110.0f, motionLerp);
	DirectX::SimpleMath::Quaternion handMotionAngle
		= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(angle));

	m_pRightHand->SetMotionAngle(handMotionAngle);
	m_pLeftHand->SetMotionAngle(handMotionAngle);

	//プレイヤーのモーションの角度を求める
	m_pPlayer->SetMotionAngle(
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(TKTLib::Lerp(0.0f, -360.0f, motionLerp)))
	);

	motionLerp += 5.0f * Messenger::GetInstance()->GetElapsedTime();

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
void PlayerAirSpenningMotion::Reset()
{
	//それぞれのオブジェクトを元の位置・角度に戻す
	m_pRightHand->SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(-50.0f)));
	m_pRightHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	m_pRightHand->SetPosition(DirectX::SimpleMath::Vector3{ 0.0f, 0.0f, 0.0f });

	m_pLeftHand->SetQuaternion(DirectX::SimpleMath::Quaternion::Identity);
	m_pLeftHand->SetMotionAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	m_pLeftHand->SetPosition(DirectX::SimpleMath::Vector3{ 0.0f, 0.0f, 0.0f });

	m_pPlayer->SetMotionAngle(DirectX::SimpleMath::Quaternion::Identity);

	SetMotionLerp(0.0f);
}

