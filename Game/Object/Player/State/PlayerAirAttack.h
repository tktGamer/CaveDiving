/**
 * @file   PlayerAirAttack.h
 *
 * @brief  プレイヤーの空中攻撃状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2025/
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef PLAYER_AIR_ATTACK_DEFINED
#define PLAYER_AIR_ATTACK_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
#include"Game/Object/Player/Hand.h"
#include"Game/Motion/PlayerMotion/PlayerSlamAttackMotion.h"
// クラスの宣言 ===============================================================
class Player;

// クラスの定義 ===============================================================
/**
  * @brief 攻撃状態
  */
class PlayerAirAttack : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:
	// プレイヤー
	Player* m_player;
	// グラフィックス
	Graphics* m_graphics;

	//モーションさせる手
	Hand* m_pHand;
	//


	//現在の攻撃
	int m_currentAttack;
	//空中での攻撃
	std::unique_ptr<Motion> m_airAttack;

	//次の攻撃をするかどうか
	bool m_isNextAttack; 

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



};

#endif		// PLAYER_IDLING_DEFINED
