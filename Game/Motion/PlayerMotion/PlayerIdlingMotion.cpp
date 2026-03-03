/**
 * @file   PlayerIdlingMotion.cpp
 *
 * @brief  プレイヤーの待機のモーションに関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *　
 * @date   日付　2026/01/18
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
	: 
	m_pRightHand{ pRightHand },
	m_pLeftHand{pLeftHand},
	m_operate{TKTLib::INT_ONE}
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

	//手を上下に動かす Y軸変化
	float handPosY = TKTLib::Lerp(MOTION_Y_POS_MIN, MOTION_Y_POS_MAX, motionLerp);

	//手の位置を設定
	//右手
	DirectX::SimpleMath::Vector3 pos = m_pRightHand->GetPosition();
	pos.y = handPosY;
	m_pRightHand->SetPosition(pos);
	//左手
	pos = m_pLeftHand->GetPosition();
	pos.y = handPosY;
	m_pLeftHand->SetPosition(pos);

	//モーション進行
	motionLerp += m_operate * Messenger::GetInstance()->GetElapsedTime();
	SetMotionLerp(std::min(motionLerp,Motion::MOTION_FINISH));
	//モーションが完了したら
	if (std::abs(GetMotionLerp()) >= Motion::MOTION_FINISH)
	{
		//進行方向を逆にする
		m_operate = -m_operate;
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