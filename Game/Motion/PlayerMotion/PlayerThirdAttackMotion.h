/**
 * @file   PlayerThirdAttackMotion.h
 *
 * @brief  プレイヤーの第三攻撃のモーションに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
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
class PlayerThirdAttackMotion : public Motion
{
	// クラス定数の宣言 -------------------------------------------------
public:


	// データメンバの宣言 -----------------------------------------------
private:

	Hand* m_pRightHand;  //右手のポインタ
	Hand* m_pLeftHand;  //左手のポインタ

	bool m_isNextAttack; //次の攻撃をするかどうか

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	PlayerThirdAttackMotion(Hand* pRightHand);

	// デストラクタ
	~PlayerThirdAttackMotion();


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

