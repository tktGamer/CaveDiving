/**
 * @file   SaveConfirm.cpp
 *
 * @brief  宝石保存確認UIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/17
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"SaveConfirm.h"
#include"../CaveDiving/Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
#include"Game/UI/GemSelectUIManager.h"
#include"Game/Factory/UIFactory.h"
SaveConfirm::SaveConfirm(int width, int height)
    :  m_windowHeight(height)
    , m_windowWidth(width)
    , m_saveMessage{}
    ,m_menu{}
    ,m_isDecide{false}
{
}

SaveConfirm::~SaveConfirm()
{
}

void SaveConfirm::Initialize()
{

    m_saveMessage = UIFactory::CreateUserInterface(L"UI/savemessage.png", { 650.0f,200.0f }, { 1.0f,1.0f }, UserInterface::MIDDLE_CENTER);


    m_menu = UIFactory::CreateMenu(ResourceManager::GetInstance()->RequestSound("cursormove.wav"));
    m_menu->Add(L"UI/yesfont.png", { 350.0f,650.0f }, { 1.0f,1.0f }, UserInterface::ANCHOR::MIDDLE_CENTER);
    m_menu->Add(L"UI/nofont.png", { 950.0f,650.0f }, { 1.0f,1.0f }, UserInterface::ANCHOR::MIDDLE_CENTER);

}

void SaveConfirm::Update()
{
    auto tracker = Graphics::GetInstance()->GetKeyboardTracker();

    m_menu->Update();

    if (tracker->pressed.Space) 
    {
        int menuIndex = m_menu->GetMenuIndex();

        switch (menuIndex) 
        {
            //「はい」の場合
        case 0:
            //所持宝石を保存
            GemManager::GetInstance()->SavePlayerHoldGem();

            break;
        //「いいえ」の場合
        case 1:
           
            break;
        }
        m_isDecide = true;
    }
}

void SaveConfirm::Render()
{
    m_saveMessage->Render();
    m_menu->Render();
}

bool SaveConfirm::IsDecide() const
{
    return m_isDecide;
}

