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
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] width
 * @param[in] height
 */
HoldGem::HoldGem(int width, int height)
    : m_menuIndex(0)
    , m_windowHeight(height)
    , m_windowWidth(width)
    ,m_pGemManager{GemManager::GetInstance()}
    ,m_position{80,680}
    ,m_scale{1.0f,1.0f}
    ,m_gemTexturePath{}
    ,m_pGems{}
{
   
}

HoldGem::~HoldGem()
{
}

void HoldGem::Initialize()
{
   
    m_gemTexturePath = L"minigem.png";

    m_base.reset();
    m_gemUI->reset();

    Add(L"slot.png",m_position ,m_scale, UserInterface::MIDDLE_CENTER);


    ChangeDrawGem();
}

void HoldGem::Update()
{
    ChangeDrawGem();
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

    //  
    std::unique_ptr<UserInterface> base = std::make_unique<UserInterface>();
    base->Create(
        path
        , position
        , scale
        , anchor
    );

    base->SetWindowSize(m_windowWidth, m_windowHeight);

    //  背景用のアイテムも新しく追加する
    m_base = std::move(base);

    for (int i = 0; i < 3; i++)
    {
        //  
        std::unique_ptr<UserInterface> gem = std::make_unique<UserInterface>();
        gem->Create(
            L"Gem/blankgem.png"
            , { position.x + GEM_POS_X[i] * scale.x,m_position.y }
            , GEM_SCALE * scale
            , anchor
        );

        gem->SetWindowSize(m_windowWidth, m_windowHeight);

        //  
        m_gemUI[i] = std::move(gem);


    }
    
}

void HoldGem::ChangePositon(const DirectX::SimpleMath::Vector2& pos)
{
    m_position = pos;

}

void HoldGem::ChangeScale(const DirectX::SimpleMath::Vector2& scale)
{
    m_scale = scale;

}

void HoldGem::ChangeDrawGem()
{
    const Gem* const* pGems = m_pGemManager->GetPlayerHoldGem();

    for (int i = 0; i < 3; i++)
    {
        if (pGems[i])
        {
            if (pGems[i]->GetAbility().type == "エメラルド") 
            {
                m_gemUI[i]->SetTexture(L"Gem/emerald.png");

            }
            else if (pGems[i]->GetAbility().type == "ルビー") 
            {
                m_gemUI[i]->SetTexture(L"Gem/ruby.png");

            }
            else if (pGems[i]->GetAbility().type == "サファイア") 
            {
                m_gemUI[i]->SetTexture(L"Gem/sapphire.png");

            }
            else if (pGems[i]->GetAbility().type == "トパーズ") 
            {
                m_gemUI[i]->SetTexture(L"Gem/topaz.png");

            }
            else if (pGems[i]->GetAbility().type == "アメジスト") 
            {
                m_gemUI[i]->SetTexture(L"Gem/amethyst.png");

            }
            else if (pGems[i]->GetAbility().type == "アクアマリン") 
            {
                m_gemUI[i]->SetTexture(L"Gem/ aquamarine.png");

            }
            else if (pGems[i]->GetAbility().type == "モルガナイト") 
            {
                m_gemUI[i]->SetTexture(L"Gem/morganite.png");

            }

            //switch (pGems[i]->GetAbility().type)
            //{
            //case "エメラルド":
            //    break;
            //case Gem::Type::STR:
            //    m_gemUI[i]->SetTexture(L"Gem/ruby.png");
            //    break;
            //case Gem::Type::DEF:
            //    m_gemUI[i]->SetTexture(L"Gem/sapphire.png");
            //    break;
            //case Gem::Type::UNIQUE:
            //    break;

            //}
        }
    }

}

