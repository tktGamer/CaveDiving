/**
 * @file   PlayerCurrentHP.cpp
 *
 * @brief  プレイヤーの残りHPUIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/17
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PlayerCurrentHP.h"
#include"Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
#include"Game/UI/Result/Score/ScoreUIManager.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pos  描画座標（右端）
 */
PlayerCurrentHP::PlayerCurrentHP(const DirectX::SimpleMath::Vector2& pos, const int& currentHP, const int& targetScore)
    :m_currentHPNumberUI{}
    ,m_currentHPTexture{}
    ,m_position{pos}
    ,m_iconTexureWidth{}
    ,m_currentNumber{}
    ,m_targetNumber{targetScore}
    ,m_stepHP{60}
    , m_hpNumber{ currentHP }
    ,m_countTime{}
{
}

/**
 * @brief デストラクタ
 */
PlayerCurrentHP::~PlayerCurrentHP()
{
}

void PlayerCurrentHP::Initialize()
{

    //int w, h;
    //Graphics::GetInstance()->GetScreenSize(w, h);


    //m_currentHPTexture = std::make_unique<UserInterface>();
    //m_currentHPTexture->Create(
    //    L"UI/currenthp.png"
    //    ,DirectX::SimpleMath::Vector2{ 300,100 }
    //    ,DirectX::SimpleMath::Vector2{ 0.4f,0.4f }
    //    ,UserInterface::ANCHOR::MIDDLE_CENTER);
    //m_currentHPTexture->SetWindowSize(w, h);
    //int texHeight;
    //ResourceManager::GetInstance()->GetTextureSize(L"UI/currenthp.png", m_iconTexureWidth, texHeight);

    NumberControl::NumberTextureData nTData;
    nTData.texturePath = "number.png";
    nTData.col = 10;
    nTData.raw = 1;

    //m_currentHPNumberUI = std::make_unique<NumberControl>(nTData,DirectX::SimpleMath::Vector2{600,220}, DirectX::SimpleMath::Vector4(0, 1, 0, 1));
    //m_currentHPNumberUI->Initialize();
    //m_currentHPNumberUI->SetScale(DirectX::SimpleMath::Vector2(0.4f, 0.4f));
    //m_currentHPNumberUI->SetDrawMinDigit(3);
    //m_currentHPNumberUI->SetNumber(m_hpNumber);


    std::unique_ptr<NumberControl> ncUI =
        UIFactory::CreateNumberUI(
            nTData,
            DirectX::SimpleMath::Vector2{ 600,220 },
            DirectX::SimpleMath::Vector2{ 0.4f,0.4f },
            DirectX::SimpleMath::Vector4{ 0,0,0,1 }, 0, 5
        );

    std::unique_ptr<UserInterface> ui =
        UIFactory::CreateUserInterface(
            L"UI/currenthp.png",
            DirectX::SimpleMath::Vector2{ 200,220 },
            DirectX::SimpleMath::Vector2{ 0.4f,0.4f },
            UserInterface::ANCHOR::MIDDLE_CENTER
        );

    m_hpNumberUI = UIFactory::CreateCountUpNumberUI(std::move(ncUI), std::move(ui), m_hpNumber, 0, 40);

    ncUI =
        UIFactory::CreateNumberUI(
            nTData,
            DirectX::SimpleMath::Vector2{ 1100,220 },
            DirectX::SimpleMath::Vector2{ 0.4f,0.4f },
            DirectX::SimpleMath::Vector4{ 0,0,0,1 }, 0, 5
        );

     ui =
        UIFactory::CreateUserInterface(
            L"UI/colon.png",
            DirectX::SimpleMath::Vector2{ 700,220 },
            DirectX::SimpleMath::Vector2{ 0.4f,0.4f },
            UserInterface::ANCHOR::MIDDLE_CENTER
        );

    m_hpScoreUI = UIFactory::CreateCountUpNumberUI(std::move(ncUI), std::move(ui), 0, m_targetNumber, 40*70);



    //m_score = std::make_unique<NumberControl>(nTData,m_position,DirectX::SimpleMath::Vector4(0,0,0,1));
    //m_score->Initialize();
    //m_score->SetScale(DirectX::SimpleMath::Vector2(0.4f, 0.4f));
    //m_score->SetDrawMinDigit(5);
    //m_score->SetNumber(TKTLib::INT_ZERO);


    //NumberControl::NumberTextureData nTData;
    //nTData.texturePath = "number.png";
    //nTData.col = 10;
    //nTData.raw = 1;


    //CreateNumberUI(UIFactory::CreateNumberUI(nTData, m_position, DirectX::SimpleMath::Vector2{ 0.4f, 0.4f }, DirectX::SimpleMath::Vector4{ 0, 0, 0, 1 }, 5, 1));
    //CreateInfoTextureUI(UIFactory::CreateUserInterface(L"UI/currenthp.png", m_position, DirectX::SimpleMath::Vector2{ 0.4f,0.4f }, UserInterface::ANCHOR::MIDDLE_CENTER));

    //int texWidth = 0, texHeight = 0;
    //ResourceManager::GetInstance()->GetTextureSize(L"UI/currenthp.png", texWidth, texHeight);

    //SetInfoTextureWidth(texWidth);
    //SetInfoTextureHeight(texHeight);

    m_stepTime = 1.0f / m_stepHP;
}

void PlayerCurrentHP::Update()
{
    //m_countTime += Messenger::GetInstance()->GetElapsedTime();

    //if (m_currentNumber >= m_targetNumber)
    //{
    //    m_currentNumber = m_targetNumber;
    //    return;
    //}
    //
    //while (m_countTime > m_stepTime)
    //{
    //    m_hpNumber -= 1;
    //    m_currentNumber += 70;

    //    m_countTime = TKTLib::FLOAT_ZERO;

    //    m_countTime -= m_stepTime;
    //}

    //m_currentHPNumberUI->SetNumber(m_hpNumber);
    //m_score->SetNumber(m_currentNumber);


    m_hpNumberUI->Update();
    m_hpScoreUI->Update();
}

void PlayerCurrentHP::Render()
{
    //m_currentHPNumberUI->Render();

    ////DirectX::SimpleMath::Vector2 drawPos = m_currentHPNumberUI->Render();
    ////drawPos.x -= m_iconTexureWidth/2 * m_currentHPTexture->GetScale().x;
    ////m_currentHPTexture->SetPosition(drawPos);
    //m_currentHPTexture->Render();

    //m_score->Render();

    m_hpNumberUI->Render();
    m_hpScoreUI->Render();
}

int PlayerCurrentHP::StepHPToScore()
{

    m_hpNumber - m_stepHP;
    return 0;
}

