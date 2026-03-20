/**
 * @file   ClearConditions.cpp
 *
 * @brief  クリア条件UIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/30
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ClearConditions.h"
#include"Game/Common/ResourceManager.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pos  描画座標（右端）
 */
ClearConditions::ClearConditions(const DirectX::SimpleMath::Vector2& pos)
    : 
    m_restEnemy{nullptr},
    m_enemyIcon{nullptr},
    m_position{pos}
{
}

/**
 * @brief デストラクタ
 */
ClearConditions::~ClearConditions()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] width　幅
 * @param[in] height 高さ
 *
 * @return なし
 */
void ClearConditions::Initialize()
{
    //アイコン生成
    m_enemyIcon = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::ENEMY_ICON, DirectX::SimpleMath::Vector2{ m_position.x + OFFSET_X,m_position.y },
        ICON_SIZE, UserInterface::ANCHOR::MIDDLE_CENTER);
    //数字生成
    NumberControl::NumberTextureData nTData;
    nTData.texturePath =TKTLib::WcharToString( ResourcePath::TEXTURE::UI::NUMBER);
    m_restEnemy = UIFactory::CreateNumberUI(nTData,m_position,NUMBER_SIZE,NUMBER_COLOR,0,NUMBER_DIGIT);    
}


/**
 * @brief 更新
 *
 * @param[in] drawNumber　表示する数字
 *
 * @return なし
 */
void ClearConditions::Update(const int& drawNumber)
{
    m_restEnemy->SetNumber(drawNumber);
}


/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void ClearConditions::Render()
{
    m_restEnemy->Render();
    m_enemyIcon->Render();
}

