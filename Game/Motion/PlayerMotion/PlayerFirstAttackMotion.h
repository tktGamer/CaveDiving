/**
 * @file   PlayerFirstAttackMotion.h
 *
 * @brief  プレイヤーの第一攻撃のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/05
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Motion.h"
#include"Game/Object/Player/Hand.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief プレイヤーの攻撃のモーション
  */
class PlayerFirstAttackMotion : public Motion
{
	// クラス定数の宣言 -------------------------------------------------
public:


	// データメンバの宣言 -----------------------------------------------
private:

	Hand* m_pRightHand;  //右手のポインタ
	Hand* m_pLeftHand;  //左手のポインタ

	bool m_isNextAttack; //次の攻撃をするかどうか

	//次の攻撃への入力時間
	float m_inputTime;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	PlayerFirstAttackMotion(Hand* pRightHand,Hand* pLeftHand);

	// デストラクタ
	~PlayerFirstAttackMotion();


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

