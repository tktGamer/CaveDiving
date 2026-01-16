/**
 * @file   ChangeGem.cpp
 *
 * @brief  宝石入れ替えUIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/09
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"ChangeGem.h"
#include"../CaveDiving/Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
#include"Game/Object/Gem/Gem.h"
#include"Game/UI/GemSelectUIManager.h"
#include"../HoldGem/HoldGem.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] width
 * @param[in] height
 * @param[in] pReplacementGem
 * @param[in] pUIManager
 */
ChangeGem::ChangeGem(int width, int height, const std::vector<int>& gemID,GemSelectUIManager* pUIManager)
    :  m_windowHeight(height)
    , m_windowWidth(width)
    , m_arrow{}
    ,m_menu{}
    ,m_gemID{gemID}
    ,m_pReplacementGem{nullptr}
    ,m_pUIManager{pUIManager}
{
}

/**
 * @brief デストラクタ
 */
ChangeGem::~ChangeGem()
{
}

void ChangeGem::Initialize()
{
    m_pReplacementGem = m_pUIManager->GetHoldGem();
    m_arrow = UIFactory::CreateUserInterface(L"arrow.png", { 650.0f,200.0f }, { 1.0f,1.0f }, UserInterface::MIDDLE_CENTER);
    //m_arrow->SetWindowSize(m_windowWidth, m_windowHeight);
    //m_arrow->Create(L"arrow.png", { 650.0f,200.0f }, { 1.0f,1.0f }, UserInterface::MIDDLE_CENTER);


    m_menu =UIFactory::CreateMenu(ResourceManager::GetInstance()->RequestSound("cursormove.wav"));
    m_menu->Add(L"UI/changefont.png", { 500.0f,600.0f }, { 0.8f,0.8f }, UserInterface::ANCHOR::MIDDLE_CENTER);
    m_menu->Add(L"UI/returnfont.png", { 850.0f,600.0f }, { 0.8f,0.8f }, UserInterface::ANCHOR::MIDDLE_CENTER);


    m_replacementGemUI = std::make_unique<UserInterface>();
    m_replacementGemUI->SetWindowSize(m_windowWidth, m_windowHeight);
    m_replacementGemUI->Create(m_pReplacementGem->GetImagePath().panel, { 950.0f,200.0f }, { 1.0f,1.0f }, UserInterface::MIDDLE_CENTER);

    m_holdGemInfo = std::make_unique<HoldGemInfoDraw>(m_windowWidth, m_windowHeight,m_gemID);
    m_holdGemInfo->Initialize();

    m_curremtUI = m_holdGemInfo.get();
}

void ChangeGem::Update()
{
    auto tracker = Graphics::GetInstance()->GetKeyboardTracker();

    if (tracker->pressed.Up) 
    {
        m_curremtUI = m_holdGemInfo.get();
    }
    if (tracker->pressed.Down) 
    {
        m_curremtUI = m_menu.get();
    }



    if (m_curremtUI == m_menu.get())
    {

        if (tracker->pressed.Z)
        {
            int menuIndex = m_menu->GetMenuIndex();

            switch (menuIndex)
            {
                //「入れ替える」の場合
            case 0:
                m_pUIManager->SetHoldGem(m_pReplacementGem);
                m_pUIManager->SelectFinishNotice(m_holdGemInfo->GetMunuIndex());
                break;
                //「入れ替えない」の場合
            case 1:
                m_pUIManager->RequestPopUI();
                break;
            }
        }

    }

    
   
    m_curremtUI->Update();

}

void ChangeGem::Render()
{

    //入れ替える・入れ替えない選択肢
    m_menu->Render();

    //所持している宝石の中の入れ替え候補を表示
    m_holdGemInfo->Render();
    //矢印画像
    m_arrow->Render();
    //入れ替え先の宝石を表示
    m_replacementGemUI->Render();
}

