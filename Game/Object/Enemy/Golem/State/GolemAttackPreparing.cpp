/**
 * @file   GolemAttackPreparing.cpp
 *
 * @brief  ゴーレムの攻撃準備状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Golem/State/GolemAttackPreparing.h"
#include "Game/Object/Enemy/Golem/Golem.h"
#include"Game//Object/Player/Player.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] golem ゴーレムのポインタ
 */
GolemAttackPreparing::GolemAttackPreparing(Golem* golem)
	:m_golem{golem},
     m_attackPreparingMotion{}
{
}
/**
 * @brief デストラクタ
 */
GolemAttackPreparing::~GolemAttackPreparing()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttackPreparing::Initialize()
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
void GolemAttackPreparing::PreUpdate()
{
	//モーション決定
	DecideMotion();
	//モーション初期化
	m_attackPreparingMotion->Initialize();
}

/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime
 *
 * @return なし
 */
void GolemAttackPreparing::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	//プレイヤーのオブジェクトを取得
	Messenger* messenger = Messenger::GetInstance();
	GameObject* pPlayer = messenger->GetObject(messenger->GetPlayerObjectID());

	//自分からプレイヤーの角度を求める
	float radian = TKTLib::CaluculateRadian(m_golem->GetCurrentPosition(), pPlayer->GetCurrentPosition());
	//目標の角度
	DirectX::SimpleMath::Quaternion rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, radian);

	//角度設定
	m_golem->SetQuaternion(rotate);

	//攻撃予備モーションが終わったら遷移
	if (m_attackPreparingMotion->Update())
	{
		//攻撃状態へ
		Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::MessageID::ATTACK);
	}
}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttackPreparing::PostUpdate()
{
	//モーションリセット
	m_attackPreparingMotion->Reset();
	//経過時間リセット
	m_golem->ResetFrameCount();
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttackPreparing::Render()
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
void GolemAttackPreparing::Finalize()
{
}

/**
 * @brief 攻撃の準備モーションを決定する
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttackPreparing::DecideMotion()
{
	switch (m_golem->GetAttackMessage()) 
	{
	case Message::AttackMesssage::ATTACKTYPE_ONE:
		m_attackPreparingMotion = std::make_unique<GolemPunchPreparingMotion>(m_golem->GetObjectNumber());
		break;
	case Message::AttackMesssage::ATTACKTYPE_TWO:
		m_attackPreparingMotion = std::make_unique<GolemSlammedDownPreparingMotion>(m_golem->GetObjectNumber());

		break;
	}
}
