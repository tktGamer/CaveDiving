/**
 * @file   PlayerMoving.cpp
 *
 * @brief  プレイヤーの移動状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Player/State/PlayerMoving.h"
#include "Game/Object/Player/Player.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player プレイヤーのポインタ
 */
PlayerMoving::PlayerMoving(Player* player)
	: m_player(player)
	, m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
}
/**
 * @brief デストラクタ
 */
PlayerMoving::~PlayerMoving()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerMoving::Initialize()
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
void PlayerMoving::PreUpdate()
{
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerMoving::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// キーボードステートを取得する
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();

	if (key->IsKeyPressed(DirectX::Keyboard::Z)) 
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::ATTACK);
	}
	if (key->pressed.Space)
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::JUMPING);
	}
	if (key->pressed.X)
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::AVOIDANCE);
	}

	DirectX::SimpleMath::Vector3 v = m_player->GetVelocity();

	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;
	//移動
	if (key->GetLastState().Up) 
	{
		v -= DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f,0.0f,1.0f) * elapsedTime, m_player->GetQuaternion());
		//rotateVelocity = DirectX::SimpleMath::Vector3::Transform(v, m_player->GetQuaternion());
	}
	if (key->GetLastState().Down)
	{
		//v.z += 1.0f*elapsedTime;
		v += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f) * elapsedTime, m_player->GetQuaternion());

	}
	if (key->GetLastState().Left)
	{
		//v.x -= 1.0f*elapsedTime;
		v -= DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f) * elapsedTime, m_player->GetQuaternion());

		//q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(2.0f));
	}
	if (key->GetLastState().Right)
	{
		//v.x += 1.0f*elapsedTime;
		v += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f)*elapsedTime, m_player->GetQuaternion());

		///q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-2.0f));
	}

	// 姿勢に回転を加える
	m_player->SetQuaternion(m_player->GetQuaternion() * q);

	if(v.Length()<=0.001f)
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::IDLING);
	}
	v *= 0.96f;
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
void PlayerMoving::PostUpdate()
{
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void PlayerMoving::Render()
{
	auto debugFont = Graphics::GetInstance()->GetDebugFont();

	debugFont->AddString(L"Moving", DirectX::SimpleMath::Vector2(500.0f, 50.0f));

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
void PlayerMoving::Finalize()
{
}
