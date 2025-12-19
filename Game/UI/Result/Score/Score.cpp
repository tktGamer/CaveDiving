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
Score::Score(const UIInfo& score, const UIInfo& referenceData)
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


/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Score::Initialize()
{
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Score::Update()
{
    m_scoreUI->Update();
    if (m_referenceUI) 
    {
        m_referenceUI->Update();
    }
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Score::Render()
{
    m_scoreUI->Render();
    if (m_referenceUI) 
    {
        m_referenceUI->Render();
    }
}

/**
 * @brief 更新演出スキップ
 *
 * @param[in] なし
 *
 * @return なし
 */
void Score::SkipDirection()
{
    m_scoreUI->SetCurrentNumber(m_scoreUI->GetTargetNumber());
    if (m_referenceUI) 
    {
        m_referenceUI->SetCurrentNumber(m_referenceUI->GetTargetNumber());
    }
}


/**
 * @brief 数字の増加が終了したか
 *
 * @param[in] なし
 *
 * @return true   終了
 *         false　未了
 */
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

/**
 * @brief UIを生成
 *
 * @param[in] 生成に必要な情報
 *
 * @return 生成したUI
 */
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

