/**
 * @file   AllSpenningAttackGem.h
 *
 * @brief  攻撃を回転攻撃にする宝石に関するヘッダファイル
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
  * @brief 攻撃を回転攻撃にする宝石
  */
class AllSpenningAttackGem:public Gem
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	AllSpenningAttackGem(const GemAbility& ability, const GemImagePath& image);
	//コピー用
	AllSpenningAttackGem(const AllSpenningAttackGem& other) = default;
	// デストラクタ
	~AllSpenningAttackGem();
//操作
	//多態コピー
	std::unique_ptr<Gem> Clone()const override;
	//初期化
	void Initialize();
	//終了
	void Finalize();
//内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
};

