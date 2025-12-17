/**
 * @file   TotalTime.h
 *
 * @brief  トータルダメージUIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/11/27
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Interface/IUI.h"
#include "Game/UI/UserInterface.h"
#include"Game/UI/Number/CountUpNumber.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief トータルダメージUI
  */
class TotalTime :public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:


private:
	//描画座標
	DirectX::SimpleMath::Vector2 m_position;
	//所要時間表示UI
	std::unique_ptr<NumberControl> m_totalTimeNumberUI;
	//「経過時間」の文字
	std::unique_ptr<UserInterface> m_totalTimeTextureUI;

	std::unique_ptr<NumberControl> m_score;

	//アイコンテクスチャの幅
	int m_iconTexureWidth;

	//現在の値
	int m_currentNumber;
	//目標値
	int m_targetNumber;

	int m_timeNumber;

	std::unique_ptr<CountUpNumber> m_totalTimeUI;
	std::unique_ptr<CountUpNumber> m_timeScoreUI;

//コンテキスト・デストラクタ
public:
	TotalTime(const DirectX::SimpleMath::Vector2& pos, const int& time, const int& targetNumber);
	~TotalTime();

//操作
public:
	void Initialize();
	void Update();
	void Render();

};
