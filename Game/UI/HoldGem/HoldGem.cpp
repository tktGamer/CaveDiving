/**
 * @file   HoldGem.cpp
 *
 * @brief  所持している宝石を表示するUIに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"HoldGem.h"
#include"../CaveDiving/Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
HoldGem::HoldGem()
    : m_menuIndex(0)
    , m_windowHeight(0)
    , m_windowWidth(0)
    ,m_pGemManager{GemManager::GetInstance()}
    ,m_position{}
{
   
}

HoldGem::~HoldGem()
{
}

void HoldGem::Initialize(int width,int height)
{
    m_windowWidth = width;
    m_windowHeight = height;
    m_position = {80,680};
    m_gemTexturePath = L"minigem.png";

    Add(L"slot.png",m_position , { 1.0f,1.0f }, UserInterface::MIDDLE_CENTER);

}

void HoldGem::Update()
{
    const Gem*const* pGems = m_pGemManager->GetPlayerHoldGem();

    for (int i = 0; i < 3; i++)
    {
        if (pGems[i]) 
        {
            switch (pGems[i]->GetAbility().m_type)
            {
            case Gem::Type::HP:
                m_gemUI[i]->SetTexture(L"Gem/emerald.png");
                break;
            case Gem::Type::STR:
                m_gemUI[i]->SetTexture(L"Gem/ruby.png");
                break;
            case Gem::Type::DEF:
                m_gemUI[i]->SetTexture(L"Gem/sapphire.png");
                break;
            case Gem::Type::UNIQUE:
                break;

            }
        }
    }
}

void HoldGem::Render()
{
    m_base->Draw();
     
    for (int i = 0; i < 3; i++)
    {
         //  実際に表示したいアイテム画像を表示
         m_gemUI[i]->Draw();
    }
}

void HoldGem::Add(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, UserInterface::ANCHOR anchor)
{

    //  背景用のウィンドウ画像も追加する
    std::unique_ptr<UserInterface> base = std::make_unique<UserInterface>();
    base->Create(
        path
        , position
        , { 1.0f, 1.0f }
        , anchor
    );

    base->SetWindowSize(m_windowWidth, m_windowHeight);

    //  背景用のアイテムも新しく追加する
    m_base = std::move(base);


    //  背景用のウィンドウ画像も追加する
    std::unique_ptr<UserInterface> gem = std::make_unique<UserInterface>();
    gem->Create(
        L"Gem/blankgem.png"
        , {position.x + GEM_POS_X[0],m_position.y}
		, GEM_SCALE
        , anchor
        );

    gem->SetWindowSize(m_windowWidth, m_windowHeight);

    //  背景用のアイテムも新しく追加する
    m_gemUI[0] = std::move(gem);

    //  背景用のウィンドウ画像も追加する
     gem = std::make_unique<UserInterface>();
    gem->Create(
         L"Gem/blankgem.png"
        , { position.x + GEM_POS_X[1],m_position.y }
        , GEM_SCALE
        , anchor
        );

    gem->SetWindowSize(m_windowWidth, m_windowHeight);

    //  背景用のアイテムも新しく追加する
    m_gemUI[1] = std::move(gem);

    //  背景用のウィンドウ画像も追加する
     gem = std::make_unique<UserInterface>();
    gem->Create(
         L"Gem/blankgem.png"
        , { position.x + GEM_POS_X[2],m_position.y }
        , GEM_SCALE
        , anchor
        );

    gem->SetWindowSize(m_windowWidth, m_windowHeight);

    //  背景用のアイテムも新しく追加する
    m_gemUI[2] = std::move(gem);

    
}

