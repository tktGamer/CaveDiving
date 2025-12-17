/**
 * @file   BuffUIControl.cpp
 *
 * @brief  入れ替え確認UIに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"BuffUIControl.h"
#include"../CaveDiving/Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
#include"Game/UI/GemSelectUIManager.h"
#include"Game/Common/Sound.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] width
 * @param[in] height
 */
BuffUIControl::BuffUIControl(int width, int height)
    : m_windowHeight{height}
    , m_windowWidth{ width }
    ,m_nowBuff{}
{

}

/**
 * @brief デストラクタ
 */
BuffUIControl::~BuffUIControl()
{
}

void BuffUIControl::Initialize()
{


}

void BuffUIControl::Update()
{

    for (std::unique_ptr<Buff>& buffUI : m_buffUIs) 
    {
        buffUI->Update();
    }

    //残り時間がなくなったバフの表示を消す
    m_buffUIs.remove_if([&](auto&  buff) {return buff->GetRemainingTime() <= 0.0f; });

    //消されたか
    if (m_nowBuff != m_buffUIs.size()) 
    {
        int num = 0;
        //再配置
        for (std::list<std::unique_ptr<Buff>>::iterator it = m_buffUIs.begin(); it != m_buffUIs.end(); ++it) 
        {
            DirectX::SimpleMath::Vector2 buffPos = FIRST_BUFF_UI_POS;
            int row = num % ROW_NUM;
            int col = num / ROW_NUM;

            buffPos.x += row * 105;
            buffPos.y += col * 110;
            (*it)->SetPosition(buffPos);
        }

        m_nowBuff =static_cast<int>( m_buffUIs.size());
    }
}

void BuffUIControl::Render()
{
    //バフの描画
    for (std::unique_ptr<Buff>& buffUI : m_buffUIs)
    {
        buffUI->Render();
    }
}

void BuffUIControl::AddUI(const Item::EffectType& upStatus, const float& buffTime)
{
    m_buffUIs.emplace_back(std::make_unique<Buff>(buffTime));

    const wchar_t* texturePath{};

    switch (upStatus)
    {
    case Item::EffectType::Attack:
        texturePath = L"UI/attackup001A-01.png";
        break;
    case Item::EffectType::Diffece:
        texturePath = L"UI/defense-up01-1-64x64.png";
        break;
    case Item::EffectType::Outline:
        texturePath = L"UI/outlineicon.png";
        break;
    default:
        break;
    }
    m_buffUIs.back()->Initialize(texturePath, m_windowWidth, m_windowHeight);

    DirectX::SimpleMath::Vector2 buffPos = FIRST_BUFF_UI_POS;
    int row = m_nowBuff % ROW_NUM;
    int col = m_nowBuff / ROW_NUM;

    buffPos.x += row * 100;
    buffPos.y += col * 110;

    m_buffUIs.back()->SetPosition(buffPos);
    m_nowBuff++;
}

