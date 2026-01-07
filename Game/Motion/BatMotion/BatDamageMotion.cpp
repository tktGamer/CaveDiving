/**
 * @file   BatDamageMotion.cpp
 *
 * @brief  コウモリのダメージリアクションモーションに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/25
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "BatDamageMotion.h"
#include"Game/Common/Sound.h"
#include"Game/Object/Enemy/Bat/Bat.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pBat コウモリのポインタ
 */
BatDamageMotion::BatDamageMotion(Bat* pBat)
	: m_pBat{pBat}
{
	m_wingSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::BAT_WING));
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
	angle *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DIAGONAL_ANGLE);
	m_pBat->SetQuaternion(angle);

	SetMotionLerp(0.0f);

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
	angle *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::UnitY,
		BAT_DAMAGE_REACTION_ROTATE_SPEED * Messenger::GetInstance()->GetElapsedTime());

	m_pBat->SetQuaternion(angle);


	motionLerp += 3.0f * Messenger::GetInstance()->GetElapsedTime();

	SetMotionLerp(std::min(motionLerp, 1.0f));

	if (GetMotionLerp() >= Motion::MOTION_FINISH)
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
}

