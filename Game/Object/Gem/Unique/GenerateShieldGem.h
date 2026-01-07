/**
 * @file   GenerateShieldGem.h
 *
 * @brief  盾生成宝石に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/01/04
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

// データメンバの宣言 -----------------------------------------------
private:
	//盾生成間隔タイマー
	float m_generateIntervalTimer = 0.0f;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GenerateShieldGem(const GemAbility& ability,const GemImagePath& image);
	GenerateShieldGem(const GenerateShieldGem& other) = default;

	// デストラクタ
	~GenerateShieldGem();


//操作
public:
	//多態コピー
	std::unique_ptr<Gem> Clone()const override;

	//初期化
	void Initialize();
	//盾生成
	int GenerateShield();
	//終了
	void Finalize();
//取得・設定
public:
//内部操作
private:

};

