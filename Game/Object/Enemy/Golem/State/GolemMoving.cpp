/**
 * @file   GolemMoving.cpp
 *
 * @brief  コウモリの移動状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2025/09/03
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Golem/State/GolemMoving.h"
#include "Game/Object/Enemy/Golem/Golem.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player プレイヤーのポインタ
 */
GolemMoving::GolemMoving(Golem* golem)
	: m_golem(golem)
	, m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
}
/**
 * @brief デストラクタ
 */
GolemMoving::~GolemMoving()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemMoving::Initialize()
{
	PreUpdate();
}

/**
 * @brief 事前処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemMoving::PreUpdate()
{
	//８方向から進む方向を決める
	float directionX = TKTLib::GetRand(-1.0f, 1.0f);
	float directionZ = TKTLib::GetRand(-1.0f, 1.0f);

	DirectX::SimpleMath::Vector3 direction = { directionX,0.0f,directionZ };

	direction.Normalize();

	// X-Z 平面上での角度を計算
	float angle = std::atan2(-direction.z, direction.x);

	//目標の角度
	DirectX::SimpleMath::Quaternion rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, angle);

	m_golem->SetQuaternion(rotate);

	//m_golem->SetVelocity(direction);

	//向いている方向に進む
	m_golem->SetVelocity(DirectX::SimpleMath::Vector3::Transform(Character::MOVE::FRONT * 5.0f * Messenger::GetInstance()->GetElapsedTime(), m_golem->GetQuaternion()));

}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemMoving::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	m_golem->SetPosition(m_golem->GetPosition() + m_golem->GetVelocity());

	//一定時間経ったら待機状態へ遷移
	if (m_golem->GetFrameCount() >= 2.0f)
	{
		Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::IDLING);

	}


	//プレイヤーを取得
	GameObject* pPlayer = Messenger::GetInstance()->GetObject(0);
	//プレイヤーか確認
	if (pPlayer && pPlayer->GetObjectType() == Tag::Player)
	{
		//現在位置とプレイヤーの位置の距離
		DirectX::SimpleMath::Vector3 playerPos = pPlayer->GetCurrentPosition();
		float distance = DirectX::SimpleMath::Vector3::Distance(playerPos, m_golem->GetCurrentPosition());
		//範囲内なら遷移
		if (distance < 15.0f)
		{
			Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::CHASING);
		}
	}



}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemMoving::PostUpdate()
{
	m_golem->ResetFrameCount();

}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemMoving::Render()
{

#ifdef _DEBUG
#endif // DEBUG

}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemMoving::Finalize()
{
}
