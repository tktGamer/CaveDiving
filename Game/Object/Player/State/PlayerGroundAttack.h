/**
 * @file   PlayerGroundAttack.h
 *
 * @brief  プレイヤーの攻撃状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2025/
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef PLAYER_GOURND_ATTACK_DEFINED
#define PLAYER_GROUND_ATTACK_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
#include"Game/Object/Player/Hand.h"
#include"Game/Motion/PlayerMotion/PlayerFirstAttackMotion.h"
#include"Game/Motion/PlayerMotion/PlayerSecondAttackMotion.h"
#include"Game/Motion/PlayerMotion/PlayerThirdAttackMotion.h"
// クラスの宣言 ===============================================================
class Player;

// クラスの定義 ===============================================================
/**
  * @brief 攻撃状態
  */
class PlayerGroundAttack : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:
	// プレイヤー
	Player* m_player;

	//モーションさせる手
	Hand* m_pHand;

	//現在の攻撃
	int m_currentAttack;
	//地上での攻撃
	std::vector<std::unique_ptr<Motion>> m_groundCombo;
	//コンボ攻撃入力待機時間
	float m_inputTime;
	//次の攻撃をするかどうか
	bool m_isNextAttack; 

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	PlayerGroundAttack(Player* player,Hand* hand);
	// デストラクタ
	~PlayerGroundAttack();


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
