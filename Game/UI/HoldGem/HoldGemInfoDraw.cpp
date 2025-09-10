/**
 * @file   HoldGemInfoDraw.cpp
 *
 * @brief  所持している宝石の内1つの情報を表示するUIに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"HoldGemInfoDraw.h"
#include"../CaveDiving/Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
HoldGemInfoDraw::HoldGemInfoDraw(int width, int height)
    : m_menuIndex(0)
    , m_windowHeight(height)
    , m_windowWidth(width)
    , m_pGemManager{ GemManager::GetInstance() }
    , m_position{ 80,680 }
    , m_scale{ 1.0f,1.0f }
    , m_gemTexturePath{}
{

}

HoldGemInfoDraw::~HoldGemInfoDraw()
{
}

void HoldGemInfoDraw::Initialize()
{

    m_gemTexturePath = L"minigem.png";

    m_holdGem = std::make_unique<HoldGem>(m_windowWidth, m_windowHeight);
    m_holdGem->ChangePositon({ 650.0f,450.0f });
    m_holdGem->ChangeScale({ 2.0f, 2.0f });
    m_holdGem->Initialize();

    m_cursol = std::make_unique<UserInterface>();
    m_cursol->SetWindowSize(m_windowWidth, m_windowHeight);
    m_cursol->Create(L"UI/cursol.png", { 650.0f,450.0f }, { 2.0f,2.0f }, UserInterface::ANCHOR::MIDDLE_CENTER);

    m_candidateGemUI = std::make_unique<UserInterface>();
    m_candidateGemUI->SetWindowSize(m_windowWidth, m_windowHeight);
    m_candidateGemUI->Create(GemManager::GetInstance()->GetPlayerHoldGem()[m_menuIndex]->GetImagePath().panel, {350.0f,200.0f}, {1.0f,1.0f}, UserInterface::MIDDLE_CENTER);

}

void HoldGemInfoDraw::Update()
{
    m_holdGem->Update();

    auto tracker = Graphics::GetInstance()->GetKeyboardTracker();



    if (tracker->pressed.Right)
    {
        //  →キーを押したら、選択先を1つ進める
        m_menuIndex += 1;
        //  メニューアイテム数の最大値を超えないように制御
        m_menuIndex %= GemManager::PLAYER_HOLD_GEM_NUM;
    }
    if (tracker->pressed.Left)
    {
        //  ←キーを押したら、選択先を1つ戻す。
        //  ただし、選択先のオーバーを割り算の余りで補正するため、（アイテムの最大個数 - 1）を足して必ず余りで計算する形にしておく。
        //  以下の式は、例えばメニューが4つあったら、現在値に3を足すという事。
        //  例）選択中のメニューが0～3まである内の2番目だった場合、
        //  (2 + (4 - 1)) % 4 = 1 ← 選択中の番号が1つ減った
        //  ということ
        m_menuIndex += static_cast<unsigned int>(GemManager::PLAYER_HOLD_GEM_NUM) - 1;
        m_menuIndex %= GemManager::PLAYER_HOLD_GEM_NUM;
    }

    m_candidateGemUI->SetTexture(GemManager::GetInstance()->GetPlayerHoldGem()[m_menuIndex]->GetImagePath().panel);

    m_cursol->SetPosition({ 650.0f + HoldGem::GEM_POS_X[m_menuIndex]*2.0f ,450.0f });
}

void HoldGemInfoDraw::Render()
{
    m_holdGem->Render();
    //表示している宝石を選ぶカーソル
    m_cursol->Draw();
    //選ばれている宝石を表示
    m_candidateGemUI->Draw();
}

void HoldGemInfoDraw::Add(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, UserInterface::ANCHOR anchor)
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


    //  

}

void HoldGemInfoDraw::ChangePositon(const DirectX::SimpleMath::Vector2& pos)
{
    m_position = pos;

}

void HoldGemInfoDraw::ChangeScale(const DirectX::SimpleMath::Vector2& scale)
{
    m_scale = scale;

}


