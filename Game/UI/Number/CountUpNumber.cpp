/**
 * @file   CountUpNumber.cpp
 *
 * @brief  数字が増加する機能をもつUIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/11/27
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
    :m_currentNumber{currentNumber}
    ,m_targetNumber{targetNumber}
    ,m_stepNumber{stepNumber}
    ,m_numberUI{}
    ,m_infoTextureUI{}
    ,m_infoTexureWidth{}
    ,m_infoTexureHeight{}
    ,m_countTime{}
    ,m_stepTime{1.0f / stepNumber}
{
}

CountUpNumber::~CountUpNumber()
{
}

void CountUpNumber::Initialize()
{    
}

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

void CountUpNumber::SetCurrentNumber(const int& currentNumber)
{
    m_currentNumber = currentNumber;
    m_numberUI->SetNumber(m_currentNumber);
}

int CountUpNumber::GetCurrentNumber() const
{
    return m_currentNumber;
}

void CountUpNumber::SetTargetNumber(const int& targetNumber)
{
    m_targetNumber = targetNumber;
}

int CountUpNumber::GetTargetNumber() const
{
    return m_targetNumber;
}

void CountUpNumber::SetStepNumber(const int& stepNumber)
{
    m_stepNumber = stepNumber;
}

int CountUpNumber::GetStepNumber() const
{
    return m_stepNumber;
}

void CountUpNumber::SetInfoTextureWidth(const int& width)
{
    m_infoTexureWidth = width;
}

int CountUpNumber::GetInfoTextureWidth() const
{
    return m_infoTexureWidth;
}

void CountUpNumber::SetInfoTextureHeight(const int& height)
{
    m_infoTexureHeight = height;
}

int CountUpNumber::GetInfoTextureHeight() const
{
    return m_infoTexureHeight;
}

bool CountUpNumber::IsFinish()
{
    return (m_currentNumber == m_targetNumber);
}

void CountUpNumber::CreateNumberUI(std::unique_ptr<NumberControl> numberUI)
{
    m_numberUI.reset();
    m_numberUI = std::move(numberUI);
}

void CountUpNumber::CreateInfoTextureUI(std::unique_ptr<UserInterface> infoUI)
{
    m_infoTextureUI.reset();
    m_infoTextureUI = std::move(infoUI);
}

