/**
 * @file   PlayerGroundAttack.h
 *
 * @brief  プレイヤーの地上攻撃状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/20
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef PLAYER_GOURND_ATTACK_DEFINED
#define PLAYER_GROUND_ATTACK_DEFINED
#include "Game/Interface/IState.h"
#include"Game/Motion/PlayerMotion/PlayerFirstAttackMotion.h"
#include"Game/Motion/PlayerMotion/PlayerSecondAttackMotion.h"
#include"Game/Motion/PlayerMotion/PlayerThirdAttackMotion.h"
// クラスの宣言 ===============================================================
class Player;
class Hand;
// クラスの定義 ===============================================================
/**
  * @brief 地上攻撃状態
  */
class PlayerGroundAttack : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//入力受付時間
	static constexpr float INPUT_TIME = 0.3f;
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	PlayerGroundAttack(Player* pPlayer,Hand* pRightHand, Hand* pLeftHand);
	// デストラクタ
	~PlayerGroundAttack();
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
	//右手のポインタ
	Hand* m_pRightHand;  
	//左手のポインタ
	Hand* m_pLeftHand;  
	//現在の攻撃
	int m_currentAttack = 0;
	//地上での攻撃
	std::vector<std::unique_ptr<AttackMotion>> m_groundCombo;
	//コンボ攻撃入力待機時間
	float m_inputTime = 0.0f;
};
#endif		// PLAYER_GOURND_ATTACK_DEFINED