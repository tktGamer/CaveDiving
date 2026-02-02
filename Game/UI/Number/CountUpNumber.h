/**
 * @file   CountUpNumber.h
 *
 * @brief  数字が増加する機能をもつUIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/30
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

// メンバ関数の宣言 -------------------------------------------------
//取得・設定
public:
	//現在の数字を設定
	void SetCurrentNumber(const int& currentNumber);
	//現在の数字を取得
	int GetCurrentNumber() const;
	//目標の数字を設定
	void SetTargetNumber(const int& targetNumber);
	//目標の数字を取得
	int GetTargetNumber() const;
	//増加する量を設定
	void SetStepNumber(const int& stepNumber);
	//増加する量を設定
	int GetStepNumber() const;

	//情報UI画像の幅を設定
	void SetInfoTextureWidth(const int& width);
	//情報UI画像の幅を取得
	int  GetInfoTextureWidth() const;
	//情報UI画像の高さを設定
	void SetInfoTextureHeight(const int& height);
	//情報UI画像の高さを取得
	int  GetInfoTextureHeight() const;

	//終了したか
	bool IsFinish() const;
//コンテキスト・デストラクタ
	//コンストラクタ
	CountUpNumber(const int& currentNumber,const int& targetNumber,const int& stepNumber);
	//デストラクタ
	~CountUpNumber();

//操作
	//初期化
	void Initialize();
	//更新
	virtual void Update();
	//描画
	virtual void Render();
	//数字UI生成
	void CreateNumberUI(std::unique_ptr<NumberControl> numberUI);
	//数字の情報を表すUI
	void CreateInfoTextureUI(std::unique_ptr<UserInterface> infoUI);
//内部処理
private:

// データメンバの宣言 -----------------------------------------------
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
};
