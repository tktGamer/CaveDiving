/**
 * @file   FullHPStatusUpGem.h
 *
 * @brief  HP満タンでステータスが上がる宝石に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/01/04
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../StatusUp/StatusUpGem.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief HP満タンでステータスが上がる宝石
  */
class FullHPStatusUpGem :public StatusUpGem
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	// 宝石の種類と効果値を指定して初期化
	FullHPStatusUpGem(const GemAbility& ability,const GemImagePath& image);

	FullHPStatusUpGem(const FullHPStatusUpGem& other) = default;

	// デストラクタ
	~FullHPStatusUpGem();


//操作
public:
	//多態コピー
	std::unique_ptr<Gem> Clone()const override;

	//初期化
	void Initialize();
	//効果を適用するか
	const bool IsApplicable(const int& currentHP, const int& maxHP) const;
	//終了
	void Finalize();
//取得・設定
public:
//内部操作
private:

};

