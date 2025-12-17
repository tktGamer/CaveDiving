/**
 * @file   CountUpNumber.h
 *
 * @brief  数字が増加する機能をもつUIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/15
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Interface/IUI.h"
#include "Game/UI/UserInterface.h"
#include"Game/UI/Number/NumberControl.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 数字が増加する機能をもつUI
  */
class CountUpNumber :public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:


private:
	//数字UI
	std::unique_ptr<NumberControl> m_numberUI;
	//数字の情報を表すUI
	std::unique_ptr<UserInterface> m_infoTextureUI;

	//情報テクスチャの大きさ
	int m_infoTexureWidth;
	int m_infoTexureHeight;

	DirectX::SimpleMath::Vector2 m_infoTexPosOffset;

	//現在の値
	int m_currentNumber;
	//目標値
	int m_targetNumber;
	//1秒あたりの増加量
	int m_stepNumber;

	//カウント
	float m_countTime;
	//値を減らす経過時間ライン
	float m_stepTime;

//コンテキスト・デストラクタ
public:
	CountUpNumber(const int& currentNumber,const int& targetNumber,const int& stepNumber);
	~CountUpNumber();

//操作
public:
	void Initialize();
	virtual void Update();
	virtual void Render();

//取得・設定
public:
	void SetCurrentNumber(const int& currentNumber);
	int GetCurrentNumber() const;

	void SetTargetNumber(const int& targetNumber);
	int GetTargetNumber() const;
	
	void SetStepNumber(const int& stepNumber);
	int GetStepNumber() const;
	
	void SetInfoTextureWidth(const int& width);
	int  GetInfoTextureWidth() const;
	
	void SetInfoTextureHeight(const int& height);
	int  GetInfoTextureHeight() const;



	bool IsFinish();

	//数字UI生成
	void CreateNumberUI(std::unique_ptr<NumberControl> numberUI);

	//数字の情報を表すUI
	void CreateInfoTextureUI(std::unique_ptr<UserInterface> infoUI);
//内部処理
private:

protected:
};
