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
HoldGem::HoldGem(int width, int height, const std::vector<int>& gemID)
    : 
    m_menuIndex(0),
    m_windowHeight(height),
    m_windowWidth(width),
    m_position{80,680},
    m_scale{1.0f,1.0f},
    m_gemTexturePath{},
    m_gemUI{}
{
}

HoldGem::~HoldGem()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in]なし
 *
 * @return なし
 */
void HoldGem::Initialize()
{
   
    m_gemTexturePath = L"minigem.png";

    m_base.reset();
    m_gemUI->reset();

    Add(L"slot.png",m_position ,m_scale, UserInterface::MIDDLE_CENTER);


}

/**
 * @brief 更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void HoldGem::Update()
{
}

/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void HoldGem::Render()
{
    m_base->Render();
     
    for (int i = 0; i < 3; i++)
    {
         //  実際に表示したいアイテム画像を表示
         m_gemUI[i]->Render();
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

void HoldGem::ChangeDrawGem(const std::vector<int>& gemID)
{
    for (int i = 0; i < gemID.size(); i++)
    {
        const Gem* pGem = GemManager::GetInstance()->GetIDNumberedGem(gemID[i]);
        if (pGem)
        {
            if (pGem->GetAbility().type == "エメラルド")
            {
                m_gemUI[i]->SetTexture(L"Gem/emerald.png");

            }
            else if (pGem->GetAbility().type == "ルビー")
            {
                m_gemUI[i]->SetTexture(L"Gem/ruby.png");

            }
            else if (pGem->GetAbility().type == "サファイア")
            {
                m_gemUI[i]->SetTexture(L"Gem/sapphire.png");

            }
            else if (pGem->GetAbility().type == "トパーズ")
            {
                m_gemUI[i]->SetTexture(L"Gem/topaz.png");

            }
            else if (pGem->GetAbility().type == "アメジスト")
            {
                m_gemUI[i]->SetTexture(L"Gem/amethyst.png");

            }
            else if (pGem->GetAbility().type == "アクアマリン")
            {
                m_gemUI[i]->SetTexture(L"Gem/Aquamarine.png");

            }
            else if (pGem->GetAbility().type == "モルガナイト")
            {
                m_gemUI[i]->SetTexture(L"Gem/morganite.png");

            }
            else if (pGem->GetAbility().type == "スピネル")
            {
                m_gemUI[i]->SetTexture(L"Gem/Spinel.png");

            }

        }
    }

}

void HoldGem::ChangeDrawGem(const std::vector<Gem*>& gems)
{

    for (int i = 0; i < 3; i++)
    {
        if (gems[i])
        {
            if (gems[i]->GetAbility().type == "エメラルド")
            {
                m_gemUI[i]->SetTexture(L"Gem/emerald.png");

            }
            else if (gems[i]->GetAbility().type == "ルビー")
            {
                m_gemUI[i]->SetTexture(L"Gem/ruby.png");

            }
            else if (gems[i]->GetAbility().type == "サファイア")
            {
                m_gemUI[i]->SetTexture(L"Gem/sapphire.png");

            }
            else if (gems[i]->GetAbility().type == "トパーズ")
            {
                m_gemUI[i]->SetTexture(L"Gem/topaz.png");

            }
            else if (gems[i]->GetAbility().type == "アメジスト")
            {
                m_gemUI[i]->SetTexture(L"Gem/amethyst.png");

            }
            else if (gems[i]->GetAbility().type == "アクアマリン")
            {
                m_gemUI[i]->SetTexture(L"Gem/ aquamarine.png");

            }
            else if (gems[i]->GetAbility().type == "モルガナイト")
            {
                m_gemUI[i]->SetTexture(L"Gem/morganite.png");

            }
        }
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

