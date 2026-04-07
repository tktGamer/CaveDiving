/**
 * @file   BatDamaged.cpp
 *
 * @brief  コウモリのダメージをくらった状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Bat/State/BatDamaged.h"
#include"Game/Motion/BatMotion/BatDamageMotion.h"
#include "Game/Object/Enemy/Bat/Bat.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] bat コウモリのポインタ
 */
BatDamaged::BatDamaged(Bat* bat)
	:
	m_bat(bat),
	m_damageMotion{}
{
	//モーションを生成
	m_damageMotion = std::make_unique<BatDamageMotion>(m_bat);
}
/**
 * @brief デストラクタ
 */
BatDamaged::~BatDamaged()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatDamaged::Initialize()
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
void BatDamaged::PreUpdate()
{
	//モーションを初期化
	m_damageMotion->Initialize();
	//ノックバックさせる
	m_bat->SetVelocity(m_bat->GetDamageDirection());
	//白く点滅
	m_bat->SetDamageFlash();
}

/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime
 *
 * @return なし
 */
void BatDamaged::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	//モーションを更新
	m_damageMotion->Update();

	DirectX::SimpleMath::Vector3 velocity= m_bat->GetVelocity();
	//重力
	velocity.y += World::GRAVITY * elapsedTime;

	//一定時間経過したら移動状態へ遷移
	if (m_bat->GetFrameCount() > CHANGE_IDLING_TIME) 
	{
		//待機状態へ遷移
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::IDLING);
	}
	//ノックバック時間
	else if (m_bat->GetFrameCount() < KNOCKBACK_TIME)
	{
		m_bat->SetVelocity(velocity);
		//位置更新
		m_bat->SetPosition(m_bat->GetPosition() + m_bat->GetVelocity() * KNOCKBACK_POWER * elapsedTime);
	}
}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatDamaged::PostUpdate()
{
	//経過時間をリセット
	m_bat->ResetFrameCount();
	//無敵状態を解除
	m_bat->SetInvincible(false);
	//モーションリセット
	m_damageMotion->Reset();
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatDamaged::Render()
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
void BatDamaged::Finalize()
{
}