/**
 * @file   GenerateShieldGem.h
 *
 * @brief  盾生成宝石に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/19
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Gem.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 盾生成宝石
  */
class GenerateShieldGem :public Gem
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	GenerateShieldGem(const GemAbility& ability,const GemImagePath& image);
	//コピー用
	GenerateShieldGem(const GenerateShieldGem& other) = default;
	// デストラクタ
	~GenerateShieldGem();
//操作
	//多態コピー
	std::unique_ptr<Gem> Clone()const override;
	//初期化
	void Initialize();
	//盾生成
	int GenerateShield();
	//終了
	void Finalize();
//内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	//盾生成間隔タイマー
	float m_generateIntervalTimer = 0.0f;
};