/**
 * @file   PlayerSecondAttackMotion.h
 *
 * @brief  プレイヤーの第二攻撃のモーションに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../AttackMotion.h"
#include"Game/Object/Player/Hand.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief プレイヤーの攻撃のモーション
  */
class PlayerSecondAttackMotion : public AttackMotion
{
	// クラス定数の宣言 -------------------------------------------------
public:
	enum Attack
	{
		COMBO1,		// コンボ1
		COMBO2,		// コンボ2
		COMBO3,		// コンボ3
		JUMP,		// ジャンプ攻撃
	};


	// データメンバの宣言 -----------------------------------------------
private:

	Hand* m_pRightHand;  //右手のポインタ
	Hand* m_pLeftHand;  //左手のポインタ

	bool m_isNextAttack; //次の攻撃をするかどうか
	
	//効果音
	std::unique_ptr<Sound> m_sound;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	PlayerSecondAttackMotion(Hand* pRightHand, Hand* pLeftHand);

	// デストラクタ
	~PlayerSecondAttackMotion();


// 操作
public:
	void Initialize();

	bool Update();


	void Reset();

//　取得・設定
public:
	void SetIsNextAttack(bool isNext);
//　内部操作
private:

};

