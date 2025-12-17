/**
 * @file   TotalDamage.cpp
 *
 * @brief  トータルダメージUIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/16
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "TotalDamage.h"
#include"Game/Common/ResourceManager.h"
#include "Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pos  描画座標（右端）
 */
TotalDamage::TotalDamage(const DirectX::SimpleMath::Vector2& pos, const int& targetNumber, const int& stepNumber)
    :m_stepNumber{stepNumber}
    ,m_targetNumber{targetNumber}
    ,m_totalDamageNumber{}
    ,m_totalDamageTexture{}
    ,m_position{pos}
    ,m_iconTexureWidth{}
    ,m_currentNumber{}
{
}

/**
 * @brief デストラクタ
 */
TotalDamage::~TotalDamage()
{
}

void TotalDamage::Initialize()
{    
    //m_totalDamageTexture = std::make_unique<UserInterface>();
    //m_totalDamageTexture->Create(
    //    L"UI/totaldamage.png"
    //    ,DirectX::SimpleMath::Vector2{ 500,100 }
    //    ,
    //    ,);
    ////m_totalDamageTexture->SetWindowSize(w, h);
    //int texHeight;
    //ResourceManager::GetInstance()->GetTextureSize(, m_iconTexureWidth, texHeight);

    //NumberControl::NumberTextureData nTData;
    //nTData.texturePath = "number.png";
    //nTData.col = 10;
    //nTData.raw = 1;

    ////m_totalDamageNumber = std::make_unique<NumberControl>(nTData,m_position,DirectX::SimpleMath::Vector4(0,0,0,1));
    ////m_totalDamageNumber->Initialize();
    ////m_totalDamageNumber->SetScale();
    ////m_totalDamageNumber->SetDrawMinDigit(5);
    ////m_totalDamageNumber->SetNumber(0);


    //CreateNumberUI(UIFactory::CreateNumberUI(nTData, m_position, DirectX::SimpleMath::Vector2{ 0.4f, 0.4f }, DirectX::SimpleMath::Vector4{ 0, 0, 0, 1 }, 5, 1));
    //CreateInfoTextureUI(UIFactory::CreateUserInterface(L"UI/totaldamage.png",m_position,DirectX::SimpleMath::Vector2{ 0.4f,0.4f },UserInterface::ANCHOR::MIDDLE_CENTER));
    //
    //int texWidth = 0, texHeight = 0;
    //ResourceManager::GetInstance()->GetTextureSize(L"UI/totaldamage.png", texWidth, texHeight);

    //SetInfoTextureWidth(texWidth);
    //SetInfoTextureHeight(texHeight);
}

void TotalDamage::Update()
{
    
    m_currentNumber += m_stepNumber;
    if (m_currentNumber > m_targetNumber) 
    {
        m_currentNumber = m_targetNumber;
    }
    m_totalDamageNumber->SetNumber(m_currentNumber);
    //float ratio = m_gauge->GetRenderRatio();


}

void TotalDamage::Render()
{
    //DirectX::SimpleMath::Vector2 drawPos = m_totalDamageNumber->Draw();
    //drawPos.x -= m_iconTexureWidth/2 * m_totalDamageTexture->GetScale().x;
    //m_totalDamageTexture->SetPosition(drawPos);
    //m_totalDamageTexture->Render();
}
