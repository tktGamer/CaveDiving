/**
 * @file   PlayerSlamAttackMotion.h
 *
 * @brief  プレイヤーの叩きつけ攻撃のモーションに関するヘッダファイル
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
#include"Game/Object/Player/Player.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief プレイヤーの叩きつけ攻撃のモーション
  */
class PlayerSlamAttackMotion : public Motion
{
	// クラス定数の宣言 -------------------------------------------------
public:


	// データメンバの宣言 -----------------------------------------------
private:
	//プレイヤーのポインタ
	Player* m_pPlayer;
	//右手のポインタ
	Hand* m_pRightHand; 
	//左手のポインタ
	Hand* m_pLeftHand;  


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
	public:
		// コンストラクタ
		PlayerSlamAttackMotion(Player* pPlayer, Hand* pRightHand,Hand* pLeftHand);

		// デストラクタ
		~PlayerSlamAttackMotion();


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

