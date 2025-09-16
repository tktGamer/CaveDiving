/**
 * @file   SaveConfirm.cpp
 *
 * @brief  宝石保存確認UIに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"SaveConfirm.h"
#include"../CaveDiving/Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
#include"Game/UI/GemSelectUIManager.h"
#include"Game/Fuctory/UIFactory.h"
SaveConfirm::SaveConfirm(int width, int height)
    :  m_windowHeight(height)
    , m_windowWidth(width)
    , m_saveMessage{}
    ,m_menu{}

{
}

SaveConfirm::~SaveConfirm()
{
}

void SaveConfirm::Initialize()
{
    //m_changeMessage = std::make_unique<UserInterface>();
    //m_changeMessage->SetWindowSize(m_windowWidth, m_windowHeight);
    //m_changeMessage->Create(L"UI/changemessage.png", { 650.0f,200.0f }, { 1.0f,1.0f }, UserInterface::MIDDLE_CENTER);


    //m_menu = std::make_unique<Menu>(m_windowWidth, m_windowHeight);
    //m_menu->Initialize();
    //m_menu->Add(L"UI/yesfont.png", { 350.0f,500.0f }, { 1.0f,1.0f }, UserInterface::ANCHOR::MIDDLE_CENTER);
    //m_menu->Add(L"UI/nofont.png", { 950.0f,500.0f }, { 1.0f,1.0f }, UserInterface::ANCHOR::MIDDLE_CENTER);


    m_saveMessage = UIFactory::CreateUserInterface(L"UI/savemessage.png", { 650.0f,200.0f }, { 1.0f,1.0f }, UserInterface::MIDDLE_CENTER);


    m_menu = UIFactory::CreateMenu();
    m_menu->Add(L"UI/yesfont.png", { 350.0f,500.0f }, { 1.0f,1.0f }, UserInterface::ANCHOR::MIDDLE_CENTER);
    m_menu->Add(L"UI/nofont.png", { 950.0f,500.0f }, { 1.0f,1.0f }, UserInterface::ANCHOR::MIDDLE_CENTER);

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
            
            break;
        //「いいえ」の場合
        case 1:
            

            break;
        }
    }
}

void SaveConfirm::Render()
{
    m_menu->Render();
}

