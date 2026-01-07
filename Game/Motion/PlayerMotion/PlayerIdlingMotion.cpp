/**
 * @file   PlayerIdlingMotion.cpp
 *
 * @brief  プレイヤーの待機のモーションに関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *　
 * @date   日付　2025/12/31
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PlayerIdlingMotion.h"
#include"Game/Object/Player/Hand.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 *
 * @param[in] pRightHand　右手のポインタ
 * @param[in] pLeftHand　 左手のポインタ
 */
PlayerIdlingMotion::PlayerIdlingMotion(Hand* pRightHand, Hand* pLeftHand)
	: m_pRightHand{ pRightHand }
	, m_pLeftHand{pLeftHand}
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
	SetMotionLerp(0.0f);
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
	float handPosY = TKTLib::Lerp(MOTION_Y_POS_MIN, MOTION_Y_POS_MAX, motionLerp);



	//
	DirectX::SimpleMath::Vector3 pos = m_pRightHand->GetPosition();
	pos.y = handPosY;
	m_pRightHand->SetPosition(pos);
	pos = m_pLeftHand->GetPosition();
	pos.y = handPosY;
	m_pLeftHand->SetPosition(pos);

	//モーション進行
	motionLerp += m_operate * Messenger::GetInstance()->GetElapsedTime();

	SetMotionLerp(std::min(motionLerp,Motion::MOTION_FINISH));

	if (std::abs(GetMotionLerp()) >= Motion::MOTION_FINISH)
	{
		//進行方向を逆にする
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
}

