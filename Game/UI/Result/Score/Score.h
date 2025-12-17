/**
 * @file   Score.h
 *
 * @brief  UIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/17
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

private:

	ScoreUIManager* m_pScoreUIManager;

	//アイコンテクスチャの幅
	int m_iconTexureWidth;


	std::unique_ptr<CountUpNumber> m_referenceUI;
	std::unique_ptr<CountUpNumber> m_scoreUI;

//コンテキスト・デストラクタ
public:
	Score(ScoreUIManager* pManager, const UIInfo& score, const UIInfo& referenceData = UIInfo{});
	~Score();

//操作
public:
	void Initialize();
	void Update();
	void Render();

	//演出スキップ
	void SkipDirection();
//取得・設定
public:
	//終了したか
	bool IsFinish();
private:
	//生成
	std::unique_ptr<CountUpNumber> CreateUI(const UIInfo& info);
};
