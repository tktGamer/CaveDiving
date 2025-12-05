/**
 * @file   TotalDamage.cpp
 *
 * @brief  トータルダメージUIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/11/27
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "TotalDamage.h"
#include"Game/Common/ResourceManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pos  描画座標（右端）
 */
TotalDamage::TotalDamage(const DirectX::SimpleMath::Vector2& pos)
    : m_windowHeight(0)
    , m_windowWidth(0)
    , m_totalDamageNumber{}
    ,m_totalDamageTexture{}
    ,m_position{pos}
    ,m_iconTexureWidth{}
{
}

TotalDamage::~TotalDamage()
{
}

void TotalDamage::Initialize(int width, int height,int totalDamage)
{

    m_windowWidth = width;
    m_windowHeight = height;


    m_totalDamageTexture = std::make_unique<UserInterface>();
    m_totalDamageTexture->Create(
        L"UI/totaldamage.png"
        ,DirectX::SimpleMath::Vector2{ 500,100 }
        ,DirectX::SimpleMath::Vector2{ 0.6f,0.6f }
        ,UserInterface::ANCHOR::MIDDLE_CENTER);
    m_totalDamageTexture->SetWindowSize(width, height);
    int texHeight;
    ResourceManager::GetInstance()->GetTextureSize(L"UI/totaldamage.png", m_iconTexureWidth, texHeight);

    NumberControl::NumberTextureData nTData;
    nTData.texturePath = "number.png";
    nTData.col = 10;
    nTData.raw = 1;

    m_totalDamageNumber = std::make_unique<NumberControl>(nTData,m_position,DirectX::SimpleMath::Vector4(1,0,0,1));
    m_totalDamageNumber->Initialize();
    m_totalDamageNumber->SetScale(DirectX::SimpleMath::Vector2(0.5f, 0.5f));
    m_totalDamageNumber->SetDrawMinDigit(5);
    m_totalDamageNumber->SetNumber(totalDamage);

}

void TotalDamage::Update(const int& drawNumber)
{

    m_totalDamageNumber->SetNumber(drawNumber);
    //float ratio = m_gauge->GetRenderRatio();


}

void TotalDamage::Render()
{
    DirectX::SimpleMath::Vector2 drawPos = m_totalDamageNumber->Draw();
    drawPos.x -= m_iconTexureWidth/2 * m_totalDamageTexture->GetScale().x;
    m_totalDamageTexture->SetPosition(drawPos);
    m_totalDamageTexture->Draw();
}

