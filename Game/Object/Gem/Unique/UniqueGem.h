/**
 * @file   UniqueGem.h
 *
 * @brief  特殊効果宝石の基底に関するヘッダファイル
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
  * @brief 特殊効果宝石の基底
  */
class UniqueGem :public Gem
{
// クラス定数の宣言 -------------------------------------------------
public:
	enum class UniqueType
	{
		// HP自動回復
		HPAutoRecovery = 0,
		//全攻撃回転攻撃化
		AllRotatingAttack,
		//HP満タンで攻撃力が上がる
		FullHPAttackUp,
	};


// データメンバの宣言 -----------------------------------------------
private:
	UniqueType m_type;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	UniqueGem(const UniqueType& uniqeuType, const GemAbility& ability, const GemImagePath& image);
	UniqueGem(const UniqueGem& other) = default;

	// デストラクタ
	~UniqueGem();


//操作
public:
	//多態コピー
	std::unique_ptr<Gem> Clone()const override;

	void Initialize();

	virtual void ApplyEffect();

	void Finalize();
//取得・設定
public:

//内部操作
private:

};

