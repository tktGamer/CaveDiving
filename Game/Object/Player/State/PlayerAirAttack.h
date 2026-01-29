/**
 * @file   PlayerAirAttack.h
 *
 * @brief  プレイヤーの空中攻撃状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/20
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
public:
//非公開定数
private:
	//攻撃を変化させるために必要な宝石
	static constexpr int SPIN_ATTACK_GEM_NUM = 2;

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	PlayerAirAttack(Player* pPlayer, Hand* pRightHand, Hand* pLeftHand);
	// デストラクタ
	~PlayerAirAttack();
// 操作
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
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	// プレイヤー
	Player* m_pPlayer;
	//空中での攻撃
	std::unique_ptr<AttackMotion> m_airAttack;
};
#endif		// PLAYER_AIR_ATTACK_DEFINED