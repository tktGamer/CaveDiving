/**
 * @file   Buff.cpp
 *
 * @brief  適用中のバフ表示UIに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/30
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Buff.h"
#include"Game/Message/Messenger.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] time バフの残り時間
 * @param[in] path バフUIの画像パス
 * @param[in] position バフUIの位置
 * @param[in] scale バフUIのスケール
 */
Buff::Buff(const float& time, const wchar_t* path,
    const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale, const UserInterface::ANCHOR& anchor)
	:
	GameObject2D{ Tag::ObjectType::UI,nullptr,position,scale },
    m_remainingTime{ &time },
    m_upType{}
{
    m_upType = UIFactory::CreateUserInterface(path, position, scale, anchor);
}

/**
 * @brief デストラクタ
 */
Buff::~Buff()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Buff::Initialize()
{
}

/**
 * @brief 更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void Buff::Update()
{
}

/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void Buff::Draw()
{
    m_upType->Draw();
}

/**
 * @brief バフUIの追加
 *
 * @param[in] なし
 *
 * @return なし
 */
const float& Buff::GetRemainingTime()
{
    return *m_remainingTime;
}

/**
 * @brief バフUIの位置設定
 *
 * @param[in] pos バフUIの位置
 *
 * @return なし
 */
void Buff::SetPosition(const DirectX::SimpleMath::Vector2& pos)
{
    m_upType->SetPosition(pos);
}


