/**
 * @file   FullHPStatusUpGem.h
 *
 * @brief  HP満タンでステータスが上がる宝石に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/01/19
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


// メンバ関数の宣言 -------------------------------------------------
//取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	// 宝石の種類と効果値を指定して初期化
	FullHPStatusUpGem(const GemAbility& ability,const GemImagePath& image);
	//コピー用
	FullHPStatusUpGem(const FullHPStatusUpGem& other) = default;
	// デストラクタ
	~FullHPStatusUpGem();
//操作
	//多態コピー
	std::unique_ptr<Gem> Clone()const override;
	//初期化
	void Initialize();
	//効果を適用するか
	const bool IsApplicable(const int& currentHP, const int& maxHP) const;
	//終了
	void Finalize();
//内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
};