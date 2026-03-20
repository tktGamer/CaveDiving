/**
 * @file   GemSelect.cpp
 *
 * @brief  宝石選択UIに関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2026/03/05
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"GemSelect.h"
#include"../CaveDiving/Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
#include"Game/UI/GemSelectUIManager.h"
#include"Game/Common/Sound.h"
#include"Game/Factory/UIFactory.h"
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
    : 
    m_menuIndex(0),
    m_windowHeight(height),
    m_windowWidth(width),
    m_pUIManager{pUIManager},
    m_pGems{},
    m_gemID{gemID}
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

/**
 * @brief 初期化処理
 *
 * @param[in]なし
 *
 * @return なし
 */
void GemSelect::Initialize()
{
    Randomize();
}

/**
 * @brief 更新
 *
 * @param[in] なし
 *
 * @return なし
 */
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
    
}

/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
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

/**
 * @brief UI追加
 *
 * @param[in] gemImagePath  表示する宝石のパス
 * @param[in] position  描画位置
 * @param[in] scale  　大きさ
 * @param[in] anchor  アンカー位置
 *
 * @return なし
 */
void GemSelect::Add(const Gem::GemImagePath& gemImagePath,const DirectX::SimpleMath::Vector2& position,
    const DirectX::SimpleMath::Vector2& scale,const UserInterface::ANCHOR& anchor)
{
    //表示するUIを追加する
    std::unique_ptr<UserInterface> base = UIFactory::CreateUserInterface(gemImagePath.panel,position,scale,anchor);
    m_userInterface.push_back(std::move(base));
}

/**
 * @brief 宝石選出処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemSelect::Randomize()
{
    m_userInterface.clear();
    m_base.clear();
    //重複させないため
    std::set<const Gem*> selectedGems;
    //試行回数
    int tryCount = 0;
    //３つの宝石を選出する  iが毎回増えるわけではないので念のためループに制限
    for (int i = 0; i < GEM_ELECTION_NUM && tryCount < MAX_TRY;)
    {
        const Gem* gem = GemManager::GetInstance()->RandomSelection();
        //まだ選ばれていない宝石なら
        if (selectedGems.insert(gem).second)
        {
            m_pGems[i] = gem;
            //UI生成
            Gem::GemImagePath imagePath = gem->GetImagePath();
            Add(imagePath,
                { PANNEL_X_POS + PANNEL_X_POS * i, PANNEL_Y_POS },
                GEM_SIZE,
                UserInterface::ANCHOR::MIDDLE_CENTER);

            //次に進む
            i++;
        }
        
    }
    //試行回数が限度に達したときのため 
    for (int i = 0; i < GEM_ELECTION_NUM; i++) 
    {
        //空のとき
        if (!m_pGems[i]) 
        {
            //一番の宝石を入れておく
            m_pGems[i] = GemManager::GetInstance()->GetIDNumberedGem(1);
        }

    }

    // 取得しないメニュー
    std::unique_ptr<UserInterface> base = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::NOT_CHOOSE_MESSAGE,
        NOT_GET_MESSAGE_POSITION,NOT_GET_MESSAGE_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER);
    m_userInterface.push_back(std::move(base));
}