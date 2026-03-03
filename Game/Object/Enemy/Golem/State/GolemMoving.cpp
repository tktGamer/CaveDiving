/**
 * @file   GolemMoving.cpp
 *
 * @brief  ゴーレムの移動状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Golem/State/GolemMoving.h"
#include "Game/Object/Enemy/Golem/Golem.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] golem ゴーレムのポインタ
 */
GolemMoving::GolemMoving(Golem* golem)
	: m_golem{golem},
	  m_walkMotion{}
{
	m_walkMotion = std::make_unique<GolemWalkMotion>(golem->GetObjectNumber());
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
	//進む方向を決める
	float directionX = static_cast<float>(TKTLib::GetRand(Character::MOVE::LEFT.x, Character::MOVE::RIGHT.x));
	float directionZ = static_cast<float>(TKTLib::GetRand(Character::MOVE::FRONT.z, Character::MOVE::BACK.z));

	DirectX::SimpleMath::Vector3 direction = { directionX,0.0f,directionZ };

	direction.Normalize();

	// X-Z 平面上での角度を計算
	float angle = std::atan2(-direction.z, direction.x);

	//目標の角度
	DirectX::SimpleMath::Quaternion rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, angle);

	m_golem->SetQuaternion(rotate);


	//向いている方向に進む
	m_golem->SetVelocity(DirectX::SimpleMath::Vector3::Transform(Character::MOVE::FRONT * 5.0f * Messenger::GetInstance()->GetElapsedTime(), m_golem->GetQuaternion()));
	//モーション初期化
	m_walkMotion->Initialize();
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

	//座標更新
	m_golem->SetPosition(m_golem->GetPosition() + m_golem->GetVelocity());

	//一定時間経ったら遷移
	if (m_golem->GetFrameCount() >= CHANGE_IDLING_TIME)
	{
		//待機状態へ
		Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::IDLING);
	}
	//重力
	DirectX::SimpleMath::Vector3 velocity = m_golem->GetVelocity();
	velocity.y += World::GRAVITY * elapsedTime;
	m_golem->SetVelocity(velocity);

	//モーションを更新
	m_walkMotion->Update();

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
	//経過時間リセット
	m_golem->ResetFrameCount();
	//モーションリセット
	m_walkMotion->Reset();
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