/**
 * @file   GemSelect.cpp
 *
 * @brief  宝石選択UIに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"GemSelect.h"
#include"../CaveDiving/Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
#include"Game/UI/GemSelectUIManager.h"
#include"Game/Common/Sound.h"
#include<set>
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] width
 * @param[in] height
 * @param[in] pUIManager
 */
GemSelect::GemSelect(int width, int height,const std::vector<int>& gemID, GemSelectUIManager* pUIManager)
    : m_menuIndex(0)
    , m_windowHeight(height)
    , m_windowWidth(width)
    , m_baseTexturePath(nullptr)
    ,m_pGemManager{GemManager::GetInstance()}
    ,m_pUIManager{pUIManager}
    ,m_pGems{}
    ,m_gemID{gemID}
{
    m_cursorSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::CURSOL_MOVE));
    m_decideSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::DECIDE));

}

/**
 * @brief デストラクタ
 */
GemSelect::~GemSelect()
{

}

void GemSelect::Initialize()
{

    //  背景となるウィンドウ画像を読み込む
    m_baseTexturePath = L"Resources/Textures/window.png";


    Randomize();

}

void GemSelect::Update()
{
    auto tracker = Graphics::GetInstance()->GetKeyboardTracker();

    if (m_userInterface.empty()) return;

    if (tracker->pressed.Right)
    {
        //  →キーを押したら、選択先を1つ進める
        m_menuIndex += 1;
        //  メニューアイテム数の最大値を超えないように制御
        m_menuIndex %= m_userInterface.size();

        m_cursorSound->Play(false);
    }
    if (tracker->pressed.Left)
    {
        //  ←キーを押したら、選択先を1つ戻す。
        //  ただし、選択先のオーバーを割り算の余りで補正するため、（アイテムの最大個数 - 1）を足して必ず余りで計算する形にしておく。
        m_menuIndex += static_cast<unsigned int>(m_userInterface.size()) - 1;
        m_menuIndex %= m_userInterface.size();
        m_cursorSound->Play(false);
    }

    //スペースキーを押したら
    if (tracker->pressed.Z) 
    {
        //「取得しない」ならUI削除
        if (m_menuIndex >= 3) 
        {
            m_pUIManager->RequestClearUI();
            m_pUIManager->SelectFinishNotice(-1);

            return;
        }


        //宝石を選択していたらスロットに空きがあるか確認
        for (int i = 0; i < m_gemID.size(); i++) 
        {
            if (m_gemID[i] == -1) 
            {
                //  m_menuIndexがm_pGemsの有効範囲内かどうかをチェックする
                if (m_menuIndex < _countof(m_pGems))
                {
                    m_decideSound->Play(false);
                    //プレイヤーの所持する宝石に登録
                    m_pUIManager->SetHoldGem(m_pGems[m_menuIndex]);
                    m_pUIManager->SelectFinishNotice(i);
                }

                break;
            }
            //空きがなかったら
            if (i == m_gemID.size() - 1) 
            {
                //空きがなかったら入れ替え確認UI生成
                m_pUIManager->RequestPushUI(GemSelectUIManager::UI::CHANGECOFIRM);

                //  m_menuIndexがm_pGemsの有効範囲内かどうかをチェックする
                if (m_menuIndex < _countof(m_pGems))
                {
                    m_pUIManager->SetHoldGem(m_pGems[m_menuIndex]);
                }

            }
        }
        //if (m_gemID[i]IsBlankSlot()) 
        //{
        //    //  m_menuIndexがm_pGemsの有効範囲内かどうかをチェックする
        //    if (m_menuIndex < _countof(m_pGems)) 
        //    {
        //        m_decideSound->Play(false);
        //        //プレイヤーの所持する宝石に登録
        //        m_pGemManager->SetHoldGem(m_pGems[m_menuIndex]);
        //        m_pUIManager->SelectFinishNotice();
        //    }
        //}
        //else
        //{
        //    //空きがなかったら入れ替え確認UI生成
        //    m_pUIManager->RequestPushUI(GemSelectUIManager::UI::CHANGECOFIRM);
        //   
        //    //  m_menuIndexがm_pGemsの有効範囲内かどうかをチェックする
        //    if (m_menuIndex < _countof(m_pGems)) 
        //    {
        //        m_pGemManager->SetReplacementGem(m_pGems[m_menuIndex]);
        //    }
        //}
        
    }

    //  各アイテムに表示する画像の初期サイズを設定する
    for (int i = 0; i < m_userInterface.size(); i++)
    {
        //m_base[i]->SetScale(m_base[i]->GetBaseScale());
        m_userInterface[i]->SetScale(m_userInterface[i]->GetBaseScale());
    }

    //  選択中の初期サイズを取得する
    DirectX::SimpleMath::Vector2 select = m_userInterface[m_menuIndex]->GetBaseScale();
    //  選択状態とするための変化用サイズを算出する
    DirectX::SimpleMath::Vector2 selectScale = DirectX::SimpleMath::Vector2::Lerp(m_userInterface[m_menuIndex]->GetBaseScale(), DirectX::SimpleMath::Vector2::One, 1);
    //  選択状態は初期状態＋30％の大きさとする
    select += selectScale * 0.3f;
    //  算出後のサイズを現在のサイズとして設定する
    m_userInterface[m_menuIndex]->SetScale(select);
    //  背景用のウィンドウ画像にも同じ割合の値を設定する
   // m_base[m_menuIndex]->SetScale(select);

    
}

void GemSelect::Render()
{
       for (int i = 0; i < m_base.size(); i++)
        {
            //  アイテム用ウィンドウ背景を表示
            m_base[i]->Render();
        }
       for (int i = 0; i < m_userInterface.size(); i++)
        {
            //  実際に表示したいアイテム画像を表示
            m_userInterface[i]->Render();
        }
}

void GemSelect::Add(Gem::GemImagePath gemImagePath, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, UserInterface::ANCHOR anchor)
{

    //  背景用のウィンドウ画像も追加する
    std::unique_ptr<UserInterface> base = std::make_unique<UserInterface>();
    base->Create(
         gemImagePath.panel
        , position
		, { 1.0f, 1.0f }
        , anchor
        );

    base->SetWindowSize(m_windowWidth, m_windowHeight);

    //  背景用のアイテムも新しく追加する
    m_userInterface.push_back(std::move(base));

}

void GemSelect::Randomize()
{
    m_userInterface.clear();
    m_base.clear();
    //重複させないため
    std::set<const Gem*> selectedGems;
    //試行回数
    int tryCount = 0;
    //３つの宝石を選出する  iが毎回増えるわけではないので念のためループに制限
    for (int i = 0; i < 3 && tryCount < MAX_TRY;)
    {
        const Gem* gem = m_pGemManager->RandomSelection();
        //まだ選ばれていない宝石なら
        if (selectedGems.insert(gem).second)
        {
            m_pGems[i] = gem;
            //UI生成
            Gem::GemImagePath imagePath = gem->GetImagePath();
            Add(imagePath,
                { PANNEL_X + PANNEL_X * i, 310.0f },
                { 0.35f, 0.35f },
                UserInterface::ANCHOR::MIDDLE_CENTER);

            //次に進む
            i++;
        }
        
    }


    //試行回数が限度に達したときのため 
    for (int i = 0; i < 3; i++) 
    {
        //空のとき
        if (!m_pGems[i]) 
        {
            //一番の宝石を入れておく
            m_pGems[i] = GemManager::GetInstance()->GetIDNumberedGem(1);
        }

    }


    // 取得しないメニュー
    std::unique_ptr<UserInterface> base = std::make_unique<UserInterface>();
    base->Create(
        L"UI/notacquiredframe.png"
        , { 650.0f,625.0f }
        , { 1.0f, 1.0f }
        , UserInterface::ANCHOR::MIDDLE_CENTER
    );

    base->SetWindowSize(m_windowWidth, m_windowHeight);
    //  背景用のアイテムも新しく追加する
    m_userInterface.push_back(std::move(base));
}


