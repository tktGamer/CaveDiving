/**
 * @file   UniquGem.h
 *
 * @brief  特殊効果宝石に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/010/27
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#include <string>

// ヘッダファイルの読み込み ===================================================
#include"../Gem.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 宝石
  */
class UniquGem :public Gem
{
// クラス定数の宣言 -------------------------------------------------
public:
	enum class UniqueType
	{
		// HP自動回復
		HPAutoRecovery = 0,
		//全攻撃回転攻撃化
		AllRotatingAttack,
	};


// データメンバの宣言 -----------------------------------------------
private:

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	UniquGem();
	// 宝石の種類と効果値を指定して初期化
	UniquGem(UniqueType uniqeuType, GemAbility ability,GemImagePath image);

	// デストラクタ
	~UniquGem();


//操作
public:
	void Initialize();

	virtual void ApplyEffect();

	void Finalize();
//取得・設定
public:

//内部操作
private:

};

