/**
 * @file   TotalDamage.h
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
#include"Game/UI/Number/CountUpNumber.h"
#include "Game/UI/UserInterface.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief トータルダメージUI
  */
class TotalDamage :public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:


private:
	//描画座標
	DirectX::SimpleMath::Vector2 m_position;
	//トータルダメージ
	std::unique_ptr<NumberControl> m_totalDamageNumber;
	//「トータルダメージ」の文字
	std::unique_ptr<UserInterface> m_totalDamageTexture;

	//アイコンテクスチャの幅
	int m_iconTexureWidth;


	//現在の値
	int m_currentNumber;
	//目標値
	int m_targetNumber;
	//1fあたりの増加量
	int m_stepNumber;
//コンテキスト・デストラクタ
public:
	TotalDamage(const DirectX::SimpleMath::Vector2& pos,const int& targetNumber,const int& stepNumber);
	~TotalDamage();

//操作
public:
	void Initialize();
	void Update();
	void Render();
//取得・設定
public:
};
