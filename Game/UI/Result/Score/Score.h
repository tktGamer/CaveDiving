/**
 * @file   Score.h
 *
 * @brief  スコアUIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/02/01
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Interface/IUI.h"
#include "Game/UI/UserInterface.h"
#include"Game/UI/Number/CountUpNumber.h"
// クラスの宣言 ===============================================================
class ScoreUIManager;
// クラスの定義 ===============================================================
/**
  * @brief UI
  */
class Score :public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:
	//UIデータ
	struct UIInfo
	{
		//数字テクスチャデータ
		NumberControl::NumberTextureData ntData;
		//数字の描画座標
		DirectX::SimpleMath::Vector2 pos;
		//数字の色
		DirectX::SimpleMath::Vector4 color;
		//数字の情報の座標　数字座標を基準に
		DirectX::SimpleMath::Vector2 infoOffset;
		//数字の情報のテクスチャ
		const wchar_t* infoTexturePath = nullptr;
		//初期数字
		int initNumber;
		//最終の数字
		int finishNumber;
		//１秒当たりの増加量
		int stepNumber;
		//最低表示桁数
		int minDigit;
	};

// データメンバの宣言 -----------------------------------------------
private:
	//数字の情報UI
	std::unique_ptr<CountUpNumber> m_referenceUI;
	//数字UI
	std::unique_ptr<CountUpNumber> m_scoreUI;
// メンバ関数の宣言 -------------------------------------------------
//取得・設定
public:
	//終了したか
	bool IsFinish();
//コンテキスト・デストラクタ
	//コンテキスト
	Score(const UIInfo& score, const UIInfo& referenceData = UIInfo{});
	//デストラクタ
	~Score();
//操作
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Render();
	//演出スキップ
	void SkipDirection();
//内部処理
private:
	//生成
	std::unique_ptr<CountUpNumber> CreateUI(const UIInfo& info);
};
