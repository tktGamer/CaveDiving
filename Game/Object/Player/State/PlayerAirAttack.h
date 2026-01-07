/**
 * @file   PlayerAirAttack.h
 *
 * @brief  プレイヤーの空中攻撃状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2025/01/07
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef PLAYER_AIR_ATTACK_DEFINED
#define PLAYER_AIR_ATTACK_DEFINED
#include "Game/Interface/IState.h"
#include"Game/Motion/PlayerMotion/PlayerSlamAttackMotion.h"
// クラスの宣言 ===============================================================
class Player;
class Hand;
// クラスの定義 ===============================================================
/**
  * @brief 攻撃状態
  */
class PlayerAirAttack : public IState
{
// クラス定数の宣言 -------------------------------------------------
private:
	//攻撃を変化させるために必要な宝石
	static constexpr int SPIN_ATTACK_GEM_NUM = 2;
public:
// データメンバの宣言 -----------------------------------------------
private:
	// プレイヤー
	Player* m_pPlayer;
	//空中での攻撃
	std::unique_ptr<AttackMotion> m_airAttack;


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	PlayerAirAttack(Player* pPlayer, Hand* pRightHand, Hand* pLeftHand);
	// デストラクタ
	~PlayerAirAttack();


// 操作
public:
	// 初期化する
	void Initialize();
	// 事前更新する
	void PreUpdate();
	// 更新する
	void Update(const float& elapsedTime);
	// 事後更新する
	void PostUpdate();
	// 描画する
	void Render();
	// 後処理を行う
	void Finalize();


//　取得・設定
public:

//　内部操作
private:

};

#endif		// PLAYER_AIR_ATTACK_DEFINED
