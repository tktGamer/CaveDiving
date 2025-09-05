/**
 * @file   PlayerDamaged.cpp
 *
 * @brief  プレイヤーのダメージをくらった状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/09/05
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerDamaged.h"
#include "Game/Object/Player/Player.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player プレイヤーのポインタ
 */
PlayerDamaged::PlayerDamaged(Player* player)
	:m_player(player)
	,m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
}
/**
 * @brief デストラクタ
 */
PlayerDamaged::~PlayerDamaged()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerDamaged::Initialize()
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
void PlayerDamaged::PreUpdate()
{
	DirectX::SimpleMath::Vector3 velocity = m_player->GetVelocity();

	m_player->SetVelocity(DirectX::SimpleMath::Vector3::Zero);

	//当たった攻撃の方向を考慮してノックバック

}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerDamaged::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// キーボードステートを取得する
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();
	


	//移動キーが押されたら移動状態へ遷移
	if (key->GetLastState().Left || key->GetLastState().Right || key->GetLastState().Up || key->GetLastState().Down)
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::MOVING);
	}
	////ジャンプキーが押されたらジャンプ状態へ遷移
	//if (key->pressed.Space) 
	//{
	//	Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::JUMPING);
	//}
	////攻撃キーが押されたら攻撃状態へ遷移
	//if (key->pressed.Z) 
	//{
	//	Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::GROUNDATTACK);
	//}
	
	//回避キーが押されたら回避状態へ遷移
	if (key->pressed.X) 
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::AVOIDANCE);
	}

	DirectX::SimpleMath::Vector3 v = m_player->GetVelocity();
	
	//重力
	v.y += -0.8f * elapsedTime;

	m_player->SetVelocity(v);

	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());

}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerDamaged::PostUpdate()
{
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerDamaged::Render()
{

	auto debugFont = Graphics::GetInstance()->GetDebugFont();
	
	debugFont->AddString(L"Damaged", DirectX::SimpleMath::Vector2(500.0f, 50.0f));
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
void PlayerDamaged::Finalize()
{
}
