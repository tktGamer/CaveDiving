/**
 * @file   Gauge.cpp
 *
 * @brief  ゲージUIに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Gauge.h"


Gauge::Gauge()
    :m_windowHeight(0)
    ,m_windowWidth(0)
    ,m_baseTexturePath(nullptr)
    ,m_gauge(nullptr)
    ,m_frame(nullptr)
    ,m_currentValue{}
    ,m_maxValue{}
{
}

Gauge::~Gauge()
{
}

void Gauge::Initialize(int width,int height)
{

    m_windowWidth = width;
    m_windowHeight = height;

    m_baseTexturePath = L"hpgaugeframe.png";


    Add(L"hpgauge.png"
        , DirectX::SimpleMath::Vector2(5, 30)
        , DirectX::SimpleMath::Vector2(1.0f,1.0f)
        ,UserInterface::ANCHOR::MIDDLE_LEFT);

}

void Gauge::Update()
{


    //float ratio = m_gauge->GetRenderRatio();

    float ratio =(float)*m_currentValue / (float)*m_maxValue;

    ratio = TKTLib::Clamp(ratio, 0.0f, 1.0f);
   

    m_gauge->SetScale({ ratio ,1.0f});

}

void Gauge::Render()
{
    m_frame->Draw();
    m_gauge->Draw();
}

void Gauge::Add(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale,UserInterface::ANCHOR anchor)
{


    m_gauge = std::make_unique<UserInterface>();
    m_gauge->Create(
          path
        , position
        , scale
        , anchor);
    m_gauge->SetWindowSize(m_windowWidth, m_windowHeight);

    m_frame = std::make_unique<UserInterface>();
    m_frame->Create(
          m_baseTexturePath
        , position
        , scale
        , anchor);
    m_frame->SetWindowSize(m_windowWidth, m_windowHeight);
   // m_frame->SetRenderRatioOffset(0.3f);


}

/**
 * @brief ゲージの参照する値
 *
 * @param[in] current 変化する値
 * @param[in] max     最大値
 *
 * @return なし
 */
void Gauge::SetValue(const int& current, const int& max)
{
    m_currentValue = &current;
    m_maxValue = &max;
}


