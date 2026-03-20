/**
 * @file   ChangeGem.cpp
 *
 * @brief  宝石入れ替えUIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/05
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
    :  
    m_windowHeight{height},
    m_windowWidth{width},
    m_arrow{},
    m_menu{},
    m_gemID{gemID},
    m_pReplacementGem{nullptr},
    m_pUIManager{pUIManager}
{
}

/**
 * @brief デストラクタ
 */
ChangeGem::~ChangeGem()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in]なし
 *
 * @return なし
 */
void ChangeGem::Initialize()
{
    m_pReplacementGem = m_pUIManager->GetHoldGem();
    m_arrow = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::ARROW,ARROW_POSITION,ARROW_SCALE, UserInterface::MIDDLE_CENTER);


    //選択肢生成
    std::vector<Menu::MunuUIInfo> info;
    info.push_back(Menu::MunuUIInfo{ ResourcePath::TEXTURE::UI::CHANGE, CHANGE_MESSAGE_POSITION, CHANGE_MESSAGE_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER });
    info.push_back(Menu::MunuUIInfo{ ResourcePath::TEXTURE::UI::RETURN, RETURN_MESSAGE_POSITION, RETURN_MESSAGE_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER });
    m_menu = UIFactory::CreateMenu(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::CURSOL_MOVE), info);
    //入れ替え先の宝石UI生成
    m_replacementGemUI = UIFactory::CreateUserInterface(m_pReplacementGem->GetImagePath().panel,REPLACE_GEM_UI_POSITION,REPLACE_GEM_UI_SCALE, 
                                                        UserInterface::ANCHOR::MIDDLE_CENTER);
    //所持宝石の内の１つの情報を表示するUIの生成
    m_holdGemInfo = UIFactory::CreateHoldGemInfoDraw(m_gemID);

    m_curremtUI = m_holdGemInfo.get();
}

/**
 * @brief 更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void ChangeGem::Update()
{
    auto tracker = Graphics::GetInstance()->GetKeyboardTracker();
    //宝石を選択
    if (tracker->pressed.Up) 
    {
        m_curremtUI = m_holdGemInfo.get();
    }
    //入れ替えるかの選択
    if (tracker->pressed.Down) 
    {
        m_curremtUI = m_menu.get();
    }

    if (m_curremtUI == m_menu.get())
    {
        //決定キーが押されたら
        if (tracker->pressed.Z)
        {
            int menuIndex = m_menu->GetMenuIndex();

            switch (menuIndex)
            {
                //「入れ替える」の場合
            case IS_CHANGI_MENU:
                m_pUIManager->SetHoldGem(m_pReplacementGem);
                m_pUIManager->SelectFinishNotice(m_holdGemInfo->GetMunuIndex());
                break;
                //「入れ替えない」の場合
            case HOLDGEM:
                m_pUIManager->RequestPopUI();
                break;
            }
        }

    }

    m_curremtUI->Update();
}

/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
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