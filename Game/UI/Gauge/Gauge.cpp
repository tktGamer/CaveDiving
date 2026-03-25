/**
 * @file   Gauge.cpp
 *
 * @brief  ゲージUIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/30
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Gauge.h"
#include"Game/ResourcePath.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] position  描画座標（右端）
 * @param[in] scale  拡大率
 * @param[in] anchor  アンカー
 */
Gauge::Gauge(const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale, const UserInterface::ANCHOR& anchor)
    :
    m_gauge{nullptr},
    m_frame{nullptr},
    m_currentValue{},
    m_maxValue{}
{
    m_frame = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::HPGAUGE_FRAME, position, scale, anchor);
    m_gauge = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::HPGAUGE, position + OFFSET, scale, anchor);
}

/**
 * @brief デストラクタ
 */
Gauge::~Gauge()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in]  なし
 *
 * @return なし
 */
void Gauge::Initialize()
{
}

/**
 * @brief 更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void Gauge::Update()
{
    //割合を計算
    float ratioX =(float)*m_currentValue / (float)m_maxValue;
    ratioX = TKTLib::Clamp(ratioX, MIN_RATIO, MAX_RATIO);
   
    //ゲージの大きさを設定
    m_gauge->SetScale(DirectX::SimpleMath::Vector2{ ratioX ,MAX_RATIO});
}


/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void Gauge::Render()
{
    m_frame->Render();
    m_gauge->Render();
}

/**
 * @brief ゲージの参照する値
 *
 * @param[in] current 変化する値
 *
 * @return なし
 */
void Gauge::SetCurrentValue(const int& current)
{
    m_currentValue = &current;
}
/**
 * @brief ゲージの参照する値
 *
 * @param[in] max     最大値
 *
 * @return なし
 */
void Gauge::SetMaxValue(const int max)
{
    m_maxValue = max;
}
