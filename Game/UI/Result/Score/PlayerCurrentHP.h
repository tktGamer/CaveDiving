/**
 * @file   PlayerCurrentHP.h
 *
 * @brief  プレイヤーの残りHPUIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/11/27
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/UI/UserInterface.h"
#include"Game/UI/Number/CountUpNumber.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief プレイヤーの残りHPUI
  */
class PlayerCurrentHP : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:


private:
	//描画座標
	DirectX::SimpleMath::Vector2 m_position;
	//残りHP
	std::unique_ptr<NumberControl> m_currentHPNumberUI;
	//「残りHP」の文字
	std::unique_ptr<UserInterface> m_currentHPTexture;

	//スコア
	std::unique_ptr<NumberControl> m_score;

	//アイコンテクスチャの幅
	int m_iconTexureWidth;

	//HPの値
	int m_hpNumber;
	//現在の値
	int m_currentNumber;
	//目標値
	int m_targetNumber;
	//1秒あたりHP減少量
	int m_stepHP;
	//カウント
	float m_countTime;

	//値を減らす経過時間ライン
	float m_stepTime;

	std::unique_ptr<CountUpNumber> m_hpNumberUI;
	std::unique_ptr<CountUpNumber> m_hpScoreUI;

//コンテキスト・デストラクタ
public:
	PlayerCurrentHP(const DirectX::SimpleMath::Vector2& pos,const int& currentHP,const int& targetScore);
	~PlayerCurrentHP();

//操作
public:
	void Initialize();
	void Update();
	void Render();

//内部処理
private:
	int StepHPToScore();
};
