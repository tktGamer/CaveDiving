/**
 * @file   GolemAttack.cpp
 *
 * @brief  コウモリの攻撃状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/09/03
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Golem/State/GolemAttack.h"
#include "Game/Object/Enemy/Golem/Golem.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] golem コウモリのポインタ
 */
GolemAttack::GolemAttack(Golem* golem)
	:m_golem(golem)
	, m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();

	//m_attackMotion = std::make_unique<GolemAttackMotion>(golem, pRightWing, pLeftWing);
}
/**
 * @brief デストラクタ
 */
GolemAttack::~GolemAttack()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttack::Initialize()
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
void GolemAttack::PreUpdate()
{
	//m_attackMotion->Initialize();

	m_golem->SetVelocity(DirectX::SimpleMath::Vector3::Transform(Character::MOVE::FRONT * 15.0f * Messenger::GetInstance()->GetElapsedTime(), m_golem->GetCurrentQuaternion()));

}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	DirectX::SimpleMath::Vector3 v = m_golem->GetVelocity();


	v.y += -0.05f * elapsedTime;


	m_golem->SetVelocity(v);

	m_golem->SetPosition(m_golem->GetPosition() + m_golem->GetVelocity());

}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttack::PostUpdate()
{
	//m_attackMotion->Reset();
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttack::Render()
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
void GolemAttack::Finalize()
{
}

