/**
 * @file   ScoreUIManager.h
 *
 * @brief  スコアUI管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/02/01
 */
// 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Common/SceneManager.h"
#include"Game/GameData.h"
#include"Game/Interface/IUI.h"
#include"Game/UI/Result/Score/Score.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
 * @brief スコアUI管理
 */
class ScoreUIManager
{
// クラス定数の宣言 -------------------------------------------------
public:
	//現在の状況
	enum State 
	{
		NONE,
		TOTALDAMGE, //トータルダメージを更新中
		CURRENTHP, //残りHPを更新中
		TOTALTIME,     //経過時間を更新中
		TOTALSCORE,//スコアを更新中
		END,//終了
	};
	//HP1に対するポイント
	static constexpr int HP_PER_POINT = 70;
	//１秒あたりの増加量
	static constexpr int HP_STEP_SECOND = 40;
	//スコアがでるまでの時間
	static constexpr int TIME_LIMIT = 300;
	static constexpr int TIME_PER_POINT = 10;
	//数字の色
	static constexpr DirectX::SimpleMath::Vector4 NUMBER_COLOR = { 0.0f,0.0f,0.0f,1.0f };
	//各スコアの桁
	static constexpr int SCORE_DIGIT = 5;
// メンバ関数の宣言 -------------------------------------------------
// 取得/設定
public:
	//処理状態の取得
	const State& GetState() const { return m_state; };
// コンストラクタ/デストラクタ
	// コンストラクタ
	ScoreUIManager(const GameData::ScoreInfo& scoreInfo);
	// デストラクタ
	~ScoreUIManager();
// 操作
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();
// 内部実装
private:
	//次に更新するUIを設定
	void SetNextUpdateUI();
	//スコアを計算
	int CalculationScore();
	//ダメージスコアを計算
	int TotalDamageScore() const;
	//残りHPスコアを計算
	int HPScore() const;
	//タイムスコアを計算
	int TimeScore();
// データメンバの宣言 -----------------------------------------------
private:
	//スコアに必要な情報
	GameData::ScoreInfo m_scoreInfo;
	Score* m_updateUI;
	//トータルダメージ表示
	std::unique_ptr<Score> m_totalDamageScoreUI;
	//HPスコアUI
	std::unique_ptr<Score> m_hpScoreUI;
	//タイムスコアUI
	std::unique_ptr<Score> m_timeScoreUI;
	//合計スコア
	std::unique_ptr<Score> m_scoreUI;

	//現在更新しているUI
	State m_state;
};
