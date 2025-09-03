/**
 * @file   BatAttack.cpp
 *
 * @brief  プレイヤーの攻撃状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Bat/State/BatAttack.h"
#include "Game/Object/Enemy/Bat/Bat.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] bat コウモリのポインタ
 */
BatAttack::BatAttack(Bat* bat)
	:m_bat(bat)
	,m_graphics{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
}
/**
 * @brief デストラクタ
 */
BatAttack::~BatAttack()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttack::Initialize()
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
void BatAttack::PreUpdate()
{
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// キーボードステートを取得する
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();

	m_bat->SetVelocity(m_bat->GetVelocity()*0.8f);

		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::IDLING);
	m_bat->SetPosition(m_bat->GetPosition() + m_bat->GetVelocity());

}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttack::PostUpdate()
{
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttack::Render()
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
void BatAttack::Finalize()
{
}

