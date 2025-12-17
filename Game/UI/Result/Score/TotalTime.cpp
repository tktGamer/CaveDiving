/**
 * @file   TotalTime.cpp
 *
 * @brief  トータルダメージUIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/11/27
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "TotalTime.h"
#include"Game/Common/ResourceManager.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pos  描画座標（右端）
 */
TotalTime::TotalTime(const DirectX::SimpleMath::Vector2& pos,const int& time, const int& targetNumber)
    : m_totalTimeNumberUI{}
    , m_totalTimeTextureUI{}
    , m_position{ pos }
    , m_iconTexureWidth{}
    ,m_timeNumber{time}
    ,m_targetNumber{targetNumber}
    ,m_currentNumber{}
{
}

/**
 * @brief デストラクタ
 */
TotalTime::~TotalTime()
{
}

void TotalTime::Initialize()
{

    int w, h;
    Graphics::GetInstance()->GetScreenSize(w, h);


    m_totalTimeTextureUI = std::make_unique<UserInterface>();
    m_totalTimeTextureUI->Create(
        L"UI/totaltime.png"
        , DirectX::SimpleMath::Vector2{ 500,100 }
        , DirectX::SimpleMath::Vector2{ 0.4f,0.4f }
    , UserInterface::ANCHOR::MIDDLE_CENTER);
    m_totalTimeTextureUI->SetWindowSize(w, h);
    int texHeight;
    ResourceManager::GetInstance()->GetTextureSize(L"UI/totaltime.png", m_iconTexureWidth, texHeight);

    NumberControl::NumberTextureData nTData;
    nTData.texturePath = "number.png";
    nTData.col = 10;
    nTData.raw = 1;

    m_totalTimeNumberUI = std::make_unique<NumberControl>(nTData, DirectX::SimpleMath::Vector2{ 600,320 }, DirectX::SimpleMath::Vector4(0, 0, 0, 1));
    m_totalTimeNumberUI->Initialize();
    m_totalTimeNumberUI->SetScale(DirectX::SimpleMath::Vector2(0.4f, 0.4f));
    m_totalTimeNumberUI->SetDrawMinDigit(3);
    m_totalTimeNumberUI->SetNumber(m_timeNumber);


    m_score = std::make_unique<NumberControl>(nTData, m_position, DirectX::SimpleMath::Vector4(0, 0, 0, 1));
    m_score->Initialize();
    m_score->SetScale(DirectX::SimpleMath::Vector2(0.4f, 0.4f));
    m_score->SetDrawMinDigit(5);
    m_score->SetNumber(0);




    std::unique_ptr<NumberControl> ncUI =
        UIFactory::CreateNumberUI(
            nTData,
            DirectX::SimpleMath::Vector2{ 600,320 },
            DirectX::SimpleMath::Vector2{ 0.4f,0.4f },
            DirectX::SimpleMath::Vector4{ 0,0,0,1 }, 0, 5
        );

    std::unique_ptr<UserInterface> ui =
        UIFactory::CreateUserInterface(
            L"UI/totaltime.png",
            DirectX::SimpleMath::Vector2{ 200,320 },
            DirectX::SimpleMath::Vector2{ 0.4f,0.4f },
            UserInterface::ANCHOR::MIDDLE_CENTER
        );

    m_totalTimeUI = UIFactory::CreateCountUpNumberUI(std::move(ncUI), std::move(ui), m_timeNumber, m_timeNumber,1);

    ncUI =
        UIFactory::CreateNumberUI(
            nTData,
            DirectX::SimpleMath::Vector2{ 1100,320 },
            DirectX::SimpleMath::Vector2{ 0.4f,0.4f },
            DirectX::SimpleMath::Vector4{ 0,0,0,1 }, 0, 5
        );

    ui =
        UIFactory::CreateUserInterface(
            L"UI/colon.png",
            DirectX::SimpleMath::Vector2{ 700,320 },
            DirectX::SimpleMath::Vector2{ 0.4f,0.4f },
            UserInterface::ANCHOR::MIDDLE_CENTER
        );

    m_timeScoreUI = UIFactory::CreateCountUpNumberUI(std::move(ncUI), std::move(ui), 0, m_targetNumber, 130);

}

void TotalTime::Update()
{

    m_currentNumber += 10;
    if (m_currentNumber > m_targetNumber)
    {
        m_currentNumber = m_targetNumber;
    }
    m_score->SetNumber(m_currentNumber);


    m_totalTimeUI->Update();
    m_timeScoreUI->Update();
}

void TotalTime::Render()
{
    //m_totalTimeNumberUI->Render();
    ////DirectX::SimpleMath::Vector2 drawPos =;
    ////drawPos.x -= m_iconTexureWidth / 2 * m_totalTimeTextureUI->GetScale().x;
    ////m_totalTimeTextureUI->SetPosition(drawPos);
    //m_totalTimeTextureUI->Render();

    //m_score->Render();

    m_totalTimeUI->Render();
    m_timeScoreUI->Render();
}

