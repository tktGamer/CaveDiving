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
GemSelect::GemSelect()
    : m_menuIndex(0)
    , m_windowHeight(0)
    , m_windowWidth(0)
    , m_baseTexturePath(nullptr)
    ,m_pGemManager{GemManager::GetInstance()}
{
   
}

GemSelect::~GemSelect()
{
}

void GemSelect::Initialize(int width,int height)
{
    m_windowWidth = width;
    m_windowHeight = height;

    //  背景となるウィンドウ画像を読み込む
    m_baseTexturePath = L"Resources/Textures/window.png";


}

void GemSelect::Update()
{
    auto tracker = Graphics::GetInstance()->GetKeyboardTracker();

    if (tracker->pressed.Right)
    {
        //  →キーを押したら、選択先を1つ進める
        m_menuIndex += 1;
        //  メニューアイテム数の最大値を超えないように制御
        m_menuIndex %= m_userInterface.size();
    }
    if (tracker->pressed.Left)
    {
        //  ←キーを押したら、選択先を1つ戻す。
        //  ただし、選択先のオーバーを割り算の余りで補正するため、（アイテムの最大個数 - 1）を足して必ず余りで計算する形にしておく。
        //  以下の式は、例えばメニューが4つあったら、現在値に3を足すという事。
        //  例）選択中のメニューが0～3まである内の2番目だった場合、
        //  (2 + (4 - 1)) % 4 = 1 ← 選択中の番号が1つ減った
        //  ということ
        m_menuIndex += static_cast<unsigned int>(m_userInterface.size()) - 1;
        m_menuIndex %= m_userInterface.size();
    }

    //スペースキーを押したら
    if (tracker->pressed.Space) 
    {
        auto p= Messenger::GetInstance()->GetObject(-1);
        
        m_pGems[m_menuIndex];
        m_pGemManager->RandomSelection();
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
            m_base[i]->Draw();
        }
       for (int i = 0; i < m_userInterface.size(); i++)
        {
            //  実際に表示したいアイテム画像を表示
            m_userInterface[i]->Draw();
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
    for (int i = 0; i < 3; i++)
    {
        m_pGems[i] = m_pGemManager->RandomSelection();
        Gem::GemAbility ability = m_pGems[i]->GetAbility();
        Gem::GemImagePath imagePath = m_pGems[i]->GetImagePath();
        Add(imagePath, { PANNEL_X+PANNEL_X*i,310.0f }, { 0.35f,0.35f }, UserInterface::ANCHOR::MIDDLE_CENTER);
    }
}


