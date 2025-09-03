/**
 * @file   BatMoving.cpp
 *
 * @brief  コウモリの移動状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Bat/State/BatMoving.h"
#include "Game/Object/Enemy/Bat/Bat.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] player プレイヤーのポインタ
 */
BatMoving::BatMoving(Bat* bat)
	: m_bat(bat)
	, m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
}
/**
 * @brief デストラクタ
 */
BatMoving::~BatMoving()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::Initialize()
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
void BatMoving::PreUpdate()
{
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// キーボードステートを取得する
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();
	DirectX::SimpleMath::Vector3 v = m_bat->GetVelocity();

	DirectX::SimpleMath::Quaternion q;

	if (key->GetLastState().Up) 
	{
		v.z -= 1.0f*elapsedTime;
	}
	if (key->GetLastState().Down)
	{
		v.z += 1.0f*elapsedTime;
	}
	if (key->GetLastState().Left)
	{
		v.x -= 1.0f*elapsedTime;
		q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(1.0f));
	}
	if (key->GetLastState().Right)
	{
		v.x += 1.0f*elapsedTime;
		q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-1.0f));
	}
	if (key->IsKeyPressed(DirectX::Keyboard::Z)) 
	{
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::ATTACK);
	}
	if (key->pressed.Space)
	{
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::JUMPING);
	}

	// 姿勢に回転を加える
	m_bat->SetQuaternion(m_bat->GetQuaternion() * q);

	if(v.Length()<=0.001f)
	{
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::IDLING);
	}
	v *= 0.96f;
	v.y += -0.8f * elapsedTime;

	m_bat->SetVelocity(v);

	m_bat->SetPosition(m_bat->GetPosition() + m_bat->GetVelocity());

}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::PostUpdate()
{
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatMoving::Render()
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
void BatMoving::Finalize()
{
}
