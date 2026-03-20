/**
 * @file   ChangeConfirm.cpp
 *
 * @brief  入れ替え確認UIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/30
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"ChangeConfirm.h"
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
 * @param[in] pUIManager
 */
ChangeConfirm::ChangeConfirm(int width, int height, GemSelectUIManager* pUIManager)
    : 
    m_windowHeight(height),
    m_windowWidth(width),
    m_changeMessage{},
    m_menu{},
    m_pUIManager{ pUIManager }
{
    //音生成
    m_showUISound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::SHOW_CONFIRM));
    m_cursorSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::CURSOL_MOVE));
}

/**
 * @brief デストラクタ
 */
ChangeConfirm::~ChangeConfirm()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in]なし
 *
 * @return なし
 */
void ChangeConfirm::Initialize()
{
    m_showUISound->Play(false);
    //入れ替えるかのメッセージUIの生成
    m_changeMessage = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::CHANGE_MESSAGE,
                                                     CHANGE_MESSAGE_POSITION,CHANGE_MESSAGE_SCALE,UserInterface::MIDDLE_CENTER);
    //選択肢生成
    std::vector<Menu::MunuUIInfo> info;
    info.push_back(Menu::MunuUIInfo{ ResourcePath::TEXTURE::UI::YES, YES_MESSAGE_POSITION, YES_MESSAGE_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER });
    info.push_back(Menu::MunuUIInfo{ ResourcePath::TEXTURE::UI::NO, NO_MESSAGE_POSITION, NO_MESSAGE_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER });
    m_menu = UIFactory::CreateMenu(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::CURSOL_MOVE),info);
}

/**
 * @brief 更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void ChangeConfirm::Update()
{
    auto tracker = Graphics::GetInstance()->GetKeyboardTracker();

    m_menu->Update();

    if (tracker->pressed.Z) 
    {
        int menuIndex = m_menu->GetMenuIndex();

        switch (menuIndex) 
        {
            //「はい」の場合
        case 0:
            m_pUIManager->RequestPopUI();
            m_pUIManager->RequestPushUI(GemSelectUIManager::UI::CHANGEGEM,true);
            break;
        //「いいえ」の場合
        case 1:
            m_pUIManager->RequestPopUI();

            break;
        }
    }
}


/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void ChangeConfirm::Render()
{
    m_changeMessage->Render();
    m_menu->Render();
}