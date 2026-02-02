/**
 * @file   CountUpNumber.cpp
 *
 * @brief  数字が増加する機能をもつUIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/30
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "CountUpNumber.h"
#include"Game/Common/ResourceManager.h"
#include"Game/Factory/UIFactory.h"
#include"Game/Message/Messenger.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pos  描画座標（右端）
 * @param[in] currentNumber  
 * @param[in] targetNumber 
 * @param[in] stepNumber 
 */
CountUpNumber::CountUpNumber(const int& currentNumber, const int& targetNumber, const int& stepNumber)
    :
    m_currentNumber{currentNumber},
    m_targetNumber{targetNumber},
    m_stepNumber{stepNumber},
    m_numberUI{},
    m_infoTextureUI{},
    m_infoTexureWidth{},
    m_infoTexureHeight{},
    m_countTime{},
    m_stepTime{1.0f / stepNumber}
{
}

CountUpNumber::~CountUpNumber()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in]なし
 *
 * @return なし
 */
void CountUpNumber::Initialize()
{    
}

/**
 * @brief 更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void CountUpNumber::Update()
{
    m_countTime += Messenger::GetInstance()->GetElapsedTime();

    if (IsFinish())
    {
        return;
    }
    // 増減方向を決定
    int direction = (m_targetNumber > m_currentNumber) ? 1 : -1;

    while (m_countTime > m_stepTime)
    {
        m_currentNumber += direction;
        m_countTime -= m_stepTime;
    }

    // 行き過ぎ防止
    if ((direction > 0 && m_currentNumber >= m_targetNumber) ||
        (direction < 0 && m_currentNumber <= m_targetNumber))
    {
        m_currentNumber = m_targetNumber;
    }

    m_numberUI->SetNumber(m_currentNumber);


}

/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void CountUpNumber::Render()
{
    m_numberUI->Render();
    ////数字を描画し、最上位桁の描画位置から数字一つ分ずらした位置を取得
    //DirectX::SimpleMath::Vector2 drawPos = m_numberUI->Draw();
    ////スケールを考慮して、情報UIのサイズの半分、左に位置をずらす
    //drawPos.x -=static_cast<float>(m_infoTexureWidth) / 2 * m_infoTextureUI->GetScale().x;
    ////計算した位置で情報UIを描画する
    //m_infoTextureUI->SetPosition(drawPos);
    m_infoTextureUI->Render();
}

/**
 * @brief 現在の数字を設定
 *
 * @param[in] currentNumber 現在の数字
 *
 * @return なし
 */
void CountUpNumber::SetCurrentNumber(const int& currentNumber)
{
    m_currentNumber = currentNumber;
    m_numberUI->SetNumber(m_currentNumber);
}

/**
 * @brief 現在の数字を取得
 *
 * @param[in] なし
 *
 * @return 現在の数字
 */
int CountUpNumber::GetCurrentNumber() const
{
    return m_currentNumber;
}

/**
 * @brief 目標の数字を設定
 *
 * @param[in] targetNumber 目標の数字
 *
 * @return なし
 */
void CountUpNumber::SetTargetNumber(const int& targetNumber)
{
    m_targetNumber = targetNumber;
}

/**
 * @brief 目標の数字を取得
 *
 * @param[in] なし
 *
 * @return 目標の数字
 */
int CountUpNumber::GetTargetNumber() const
{
    return m_targetNumber;
}

/**
 * @brief 増加する量を設定
 *
 * @param[in] stepNumber 増加する量
 *
 * @return なし
 */
void CountUpNumber::SetStepNumber(const int& stepNumber)
{
    m_stepNumber = stepNumber;
}

/**
 * @brief 増加する量を取得
 *
 * @param[in] なし
 *
 * @return 増加する量
 */
int CountUpNumber::GetStepNumber() const
{
    return m_stepNumber;
}

/**
 * @brief 情報UI画像の幅を設定
 *
 * @param[in] width 幅
 *
 * @return なし
 */
void CountUpNumber::SetInfoTextureWidth(const int& width)
{
    m_infoTexureWidth = width;
}

/**
 * @brief 情報UI画像の幅を取得
 *
 * @param[in] なし
 *
 * @return 幅
 */
int CountUpNumber::GetInfoTextureWidth() const
{
    return m_infoTexureWidth;
}

/**
 * @brief 情報UI画像の高さを設定
 *
 * @param[in] height 高さ
 *
 * @return なし
 */
void CountUpNumber::SetInfoTextureHeight(const int& height)
{
    m_infoTexureHeight = height;
}

/**
 * @brief 情報UI画像の高さを取得
 *
 * @param[in] なし
 *
 * @return 高さ
 */
int CountUpNumber::GetInfoTextureHeight() const
{
    return m_infoTexureHeight;
}

/**
 * @brief 終了したか
 *
 * @param[in] なし
 *
 * @return 終了していればtrue、そうでなければfalse
 */
bool CountUpNumber::IsFinish() const
{
    return (m_currentNumber == m_targetNumber);
}

/**
 * @brief 数字UI生成
 *
 * @param[in] numberUI 数字UI
 *
 * @return なし
 */
void CountUpNumber::CreateNumberUI(std::unique_ptr<NumberControl> numberUI)
{
    m_numberUI.reset();
    m_numberUI = std::move(numberUI);
}

/**
 * @brief 数字の情報を表すUI
 *
 * @param[in] infoUI 数字の情報を表すUI
 *
 * @return なし
 */
void CountUpNumber::CreateInfoTextureUI(std::unique_ptr<UserInterface> infoUI)
{
    m_infoTextureUI.reset();
    m_infoTextureUI = std::move(infoUI);
}