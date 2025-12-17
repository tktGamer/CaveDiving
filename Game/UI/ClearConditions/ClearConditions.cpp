/**
 * @file   ClearConditions.cpp
 *
 * @brief  クリア条件UIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/10/31
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ClearConditions.h"
#include"Game/Common/ResourceManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pos  描画座標（右端）
 */
ClearConditions::ClearConditions(const DirectX::SimpleMath::Vector2& pos)
    : m_windowHeight(0)
    , m_windowWidth(0)
    , m_restEnemy(nullptr)
    , m_enemyIcon(nullptr)
    ,m_position{pos}
    ,m_iconTexureWidth{}
{
}

/**
 * @brief デストラクタ
 */
ClearConditions::~ClearConditions()
{
}

void ClearConditions::Initialize(int width, int height)
{

    m_windowWidth = width;
    m_windowHeight = height;


    m_enemyIcon = std::make_unique<UserInterface>();
    m_enemyIcon->Create(
        L"enemyIcon.png"
        ,DirectX::SimpleMath::Vector2{ m_position.x -100,150 }
        ,DirectX::SimpleMath::Vector2{ 0.05f,0.05f }
        ,UserInterface::ANCHOR::MIDDLE_CENTER);
    m_enemyIcon->SetWindowSize(width, height);
    int texHeight;
    ResourceManager::GetInstance()->GetTextureSize(L"enemyIcon.png", m_iconTexureWidth, texHeight);

    NumberControl::NumberTextureData nTData;
    nTData.texturePath = "number.png";
    nTData.col = 10;
    nTData.raw = 1;

    m_restEnemy = std::make_unique<NumberControl>(nTData,m_position,DirectX::SimpleMath::Vector4(1,1,1,1));
    m_restEnemy->Initialize();
    m_restEnemy->SetScale(DirectX::SimpleMath::Vector2(0.3f, 0.3f));
    m_restEnemy->SetDrawMinDigit(2);
    
}

void ClearConditions::Update(const int& drawNumber)
{

    m_restEnemy->SetNumber(drawNumber);
    //float ratio = m_gauge->GetRenderRatio();


}

void ClearConditions::Render()
{
    m_restEnemy->Render();
    //DirectX::SimpleMath::Vector2 drawPos = ;
    //drawPos.x -= m_iconTexureWidth * m_enemyIcon->GetScale().x;
    //m_enemyIcon->SetPosition(drawPos);
    m_enemyIcon->Render();
}

