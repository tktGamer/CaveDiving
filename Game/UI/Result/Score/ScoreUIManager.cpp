/**
 * @file   ScoreUIManager.cpp
 *
 * @brief  スコアUIの管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/10
 */
// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ScoreUIManager.h"
#include "Game/Common/ResourceManager.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
ScoreUIManager::ScoreUIManager(const GameData::ScoreInfo& scoreInfo)
	:m_scoreInfo{scoreInfo}
	,m_state{State::NONE}
	,m_updateUI{}
{
}

/**
 * @brief デストラクタ
 */
ScoreUIManager::~ScoreUIManager()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ScoreUIManager::Initialize()
{
	CalculationScore();
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);
	NumberControl::NumberTextureData nTData;
	nTData.texturePath = TKTLib::WcharToString(ResourcePath::TEXTURE::UI::NUMBER);


	//総合スコア＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	//スコアUIデータ
	Score::UIInfo score;
	score.ntData = nTData;
	score.pos = DirectX::SimpleMath::Vector2{ 1100,420 };
	score.color = NUMBER_COLOR;
	score.infoOffset = DirectX::SimpleMath::Vector2{ 400,0 };
	score.infoTexturePath = ResourcePath::TEXTURE::UI::SCORE;
	score.initNumber = TKTLib::INT_ZERO;
	score.finishNumber = CalculationScore();
	score.stepNumber = 5000;
	score.minDigit = SCORE_DIGIT;
	m_scoreUI = UIFactory::CreateScoreUI(score);

	//情報UIデータ
	Score::UIInfo referenceUI;
	referenceUI.ntData = nTData;
	referenceUI.pos				= DirectX::SimpleMath::Vector2{ 600,220 };
	referenceUI.color			= NUMBER_COLOR;
	referenceUI.infoOffset		= DirectX::SimpleMath::Vector2{ 400,0 };
	referenceUI.infoTexturePath = ResourcePath::TEXTURE::UI::CURRENT_HP;
	referenceUI.initNumber		= m_scoreInfo.playerCurrentHp;
	referenceUI.finishNumber	= TKTLib::INT_ZERO;
	referenceUI.stepNumber		= HP_STEP_SECOND;
	referenceUI.minDigit		= 3;

	//スコアUIデータ
	Score::UIInfo scoreUI;
	scoreUI.ntData = nTData;
	scoreUI.pos = DirectX::SimpleMath::Vector2{ 1100,220 };
	scoreUI.color = NUMBER_COLOR;
	scoreUI.infoOffset = DirectX::SimpleMath::Vector2{ 400,0 };
	scoreUI.infoTexturePath = ResourcePath::TEXTURE::UI::COLON;
	scoreUI.initNumber = TKTLib::INT_ZERO;
	scoreUI.finishNumber = HPScore();
	scoreUI.stepNumber = HP_STEP_SECOND*HP_PER_POINT;
	scoreUI.minDigit = 5;

	m_hpScoreUI = UIFactory::CreateScoreUI(scoreUI, referenceUI);
	m_hpScoreUI->Initialize();

	//スコアUIデータ
	scoreUI.ntData				= nTData;
	scoreUI.pos					= DirectX::SimpleMath::Vector2{ 1100,120 };
	scoreUI.color				= NUMBER_COLOR;
	scoreUI.infoOffset			= DirectX::SimpleMath::Vector2{ 500,0 };
	scoreUI.infoTexturePath		= ResourcePath::TEXTURE::UI::TOTAL_DAMAGE;
	scoreUI.initNumber			= TKTLib::INT_ZERO;
	scoreUI.finishNumber		= TotalDamageScore();
	scoreUI.stepNumber			= 300;
	scoreUI.minDigit			= SCORE_DIGIT;

	m_totalDamageScoreUI = UIFactory::CreateScoreUI(scoreUI);
	m_totalDamageScoreUI->Initialize();

	//情報UIデータ
	referenceUI.ntData = nTData;
	referenceUI.pos				= DirectX::SimpleMath::Vector2{ 600,320 };
	referenceUI.color			= NUMBER_COLOR;
	referenceUI.infoOffset		= DirectX::SimpleMath::Vector2{ 400,0 };
	referenceUI.infoTexturePath = ResourcePath::TEXTURE::UI::TOTAL_TIME;
	referenceUI.initNumber		= static_cast<int>(m_scoreInfo.totalTime);
	referenceUI.finishNumber	= static_cast<int>(m_scoreInfo.totalTime);
	referenceUI.stepNumber		= HP_STEP_SECOND;
	referenceUI.minDigit		= 3;

	//スコアUIデータ
	scoreUI.ntData				= nTData;
	scoreUI.pos					= DirectX::SimpleMath::Vector2{ 1100,320 };
	scoreUI.color				= NUMBER_COLOR;
	scoreUI.infoOffset			= DirectX::SimpleMath::Vector2{ 400,0 };
	scoreUI.infoTexturePath		= ResourcePath::TEXTURE::UI::COLON;
	scoreUI.initNumber			= TKTLib::INT_ZERO;
	scoreUI.finishNumber		= TimeScore();
	scoreUI.stepNumber			= 100*TIME_PER_POINT;
	scoreUI.minDigit			= SCORE_DIGIT;

	m_timeScoreUI = UIFactory::CreateScoreUI(scoreUI, referenceUI);
	m_timeScoreUI->Initialize();

	SetNextUpdateUI();
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ScoreUIManager::Update()
{
	//終了状態なら処理しない
	if (m_state == State::END) 
	{
		return;
	}

	auto traker = Graphics::GetInstance()->GetKeyboardTracker();
	//現在のUIが更新し終えたら
	if (m_updateUI->IsFinish()) 
	{
		//次のUIをセットする
		SetNextUpdateUI();
	}

	//キーを押したら次の処理へいく
	if (traker->IsKeyPressed(DirectX::Keyboard::Keys::Z)) 
	{
		m_updateUI->SkipDirection();
	}

	//現在更新中のUI
	m_updateUI->Update();

}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ScoreUIManager::Render()
{

	m_totalDamageScoreUI->Render();
	m_hpScoreUI->Render();
	m_timeScoreUI->Render();

	m_scoreUI->Render();
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ScoreUIManager::Finalize()
{
}


/**
 * @brief 次に更新するUIを設定
 *
 * @param[in] なし
 *
 * @return なし
 */
void ScoreUIManager::SetNextUpdateUI()
{
	//次の状態に進める
    m_state = static_cast<State>(static_cast<int>(m_state) + static_cast<int>(TKTLib::INT_ONE));

	switch (m_state)
	{
	case ScoreUIManager::NONE:
		break;
	case ScoreUIManager::TOTALDAMGE:
		m_updateUI = m_totalDamageScoreUI.get();
		break;
	case ScoreUIManager::CURRENTHP:
		m_updateUI = m_hpScoreUI.get();
		break;
	case ScoreUIManager::TOTALTIME:
		m_updateUI = m_timeScoreUI.get();
		break;
	case ScoreUIManager::TOTALSCORE:
		m_updateUI = m_scoreUI.get();
		break;
	case ScoreUIManager::END:
		break;
	default:
		break;
	}
}


 /**
  * @brief 合計スコアを計算
  *
  * @param[in] なし
  *
  * @return 合計スコア
  */
int ScoreUIManager::CalculationScore()
{
	int totalScore{};
	//トータルダメージ
	totalScore += TotalDamageScore();
	//HP
	totalScore += HPScore();
	//時間
	totalScore += TimeScore();

	return totalScore;
}


/**
 * @brief トータルダメージスコアを計算
 *
 * @param[in] なし
 *
 * @return トータルダメージスコア
 */
int ScoreUIManager::TotalDamageScore() const
{
	return m_scoreInfo.totalDamage;
}


/**
 * @brief HPスコア計算
 *
 * @param[in] なし
 *
 * @return HPスコア
 */
int ScoreUIManager::HPScore() const
{
	return m_scoreInfo.playerCurrentHp * HP_PER_POINT;
}


/**
 * @brief タイムスコアを計算
 *
 * @param[in] なし
 *
 * @return タイムスコア
 */
int ScoreUIManager::TimeScore()
{
	return std::max(TIME_LIMIT - static_cast<int>(m_scoreInfo.totalTime),0)  * TIME_PER_POINT;
}

