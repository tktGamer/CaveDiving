/**
 * @file   Buff.cpp
 *
 * @brief  適用中のバフ表示UIに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/10/10
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Buff.h"
#include"Game/Message/Messenger.h"

Buff::Buff(const float& time)
    :m_windowHeight{0}
    ,m_windowWidth{0}
    , m_baseTexturePath{ nullptr }
    , m_upType{nullptr}
    , m_frame{nullptr}
    , m_remainingTime{&time}
{
}

Buff::~Buff()
{
}

void Buff::Initialize(const wchar_t* path, int width, int height)
{

    m_windowWidth = width;
    m_windowHeight = height;
    
    m_baseTexturePath = L"UI/buff.png";


    Add(path
        , DirectX::SimpleMath::Vector2(15, 100)
        , DirectX::SimpleMath::Vector2(0.8f, 0.8f)
        , UserInterface::ANCHOR::MIDDLE_LEFT);

}

void Buff::Update()
{
}

void Buff::Render()
{
    m_frame->Draw();
    m_upType->Draw();
}

/**
 * @brief バフUIの追加
 *
 * @param[in] path
 * @param[in] position
 * @param[in] scale
 * @param[in] anchor
 *
 * @return なし
 */
void Buff::Add(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, UserInterface::ANCHOR anchor)
{

    m_frame = std::make_unique<UserInterface>();
    m_frame->Create(
        m_baseTexturePath
        , position
        , scale
        , anchor);
    m_frame->SetWindowSize(m_windowWidth, m_windowHeight);

    m_upType = std::make_unique<UserInterface>();
    m_upType->Create(
        path
        , position
        , scale
        , anchor);
    m_upType->SetWindowSize(m_windowWidth, m_windowHeight);



}

const float& Buff::GetRemainingTime()
{
    return *m_remainingTime;
}

void Buff::SetPosition(const DirectX::SimpleMath::Vector2& pos)
{
    m_frame->SetPosition(pos);
    m_upType->SetPosition(pos);
}


