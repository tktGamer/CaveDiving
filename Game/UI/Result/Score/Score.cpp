/**
 * @file   Score.cpp
 *
 * @brief  スコアUIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/17
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Score.h"
#include"Game/Factory/UIFactory.h"
#include"Game/UI/Result/Score/ScoreUIManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pManager  管理クラスのポインタ
 * @param[in] score  スコアUIのデータ
 * @param[in] referenceData  情報UIのデータ
 */
Score::Score(ScoreUIManager* pManager, const UIInfo& score, const UIInfo& referenceData)
    :m_referenceUI{}
    ,m_scoreUI{}
{
    m_scoreUI = std::move(CreateUI(score));
    //入っていないといけない値が入っているか
    if (referenceData.minDigit > 0) 
    {
        m_referenceUI = std::move(CreateUI(referenceData));
    }
}

/**
 * @brief デストラクタ
 */
Score::~Score()
{
}

void Score::Initialize()
{
}

void Score::Update()
{
    m_scoreUI->Update();
    if (m_referenceUI) 
    {
        m_referenceUI->Update();
    }
}

void Score::Render()
{
    m_scoreUI->Render();
    if (m_referenceUI) 
    {
        m_referenceUI->Render();
    }
}

void Score::SkipDirection()
{
    m_scoreUI->SetCurrentNumber(m_scoreUI->GetTargetNumber());
    if (m_referenceUI) 
    {
        m_referenceUI->SetCurrentNumber(m_referenceUI->GetTargetNumber());
    }
}

bool Score::IsFinish() 
{

    //まだ増加が終了していなかったらfalseを返す
    if (!m_scoreUI->IsFinish()) 
    {
        return false;
    }
    if (m_referenceUI && !m_referenceUI->IsFinish()) 
    {
        return false;
    }

    //終了した
    return true;
}

std::unique_ptr<CountUpNumber> Score::CreateUI(const UIInfo& info)
{
    //数字UIを生成する
    std::unique_ptr<NumberControl> ncUI =
        UIFactory::CreateNumberUI(
            info.ntData,
            info.pos,
            DirectX::SimpleMath::Vector2{ 0.4f,0.4f },
            info.color,
            info.initNumber,
            info.minDigit
        );
    //数字が表す情報のUIを生成する
    std::unique_ptr<UserInterface> ui =
        UIFactory::CreateUserInterface(
            info.infoTexturePath,
            info.pos - info.infoOffset,
            DirectX::SimpleMath::Vector2{ 0.4f,0.4f },
            UserInterface::ANCHOR::MIDDLE_CENTER
        );

    //生成して返す
    return UIFactory::CreateCountUpNumberUI(std::move(ncUI), std::move(ui), info.initNumber, info.finishNumber, info.stepNumber);

}

