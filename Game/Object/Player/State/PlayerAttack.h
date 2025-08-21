/**
 * @file   PlayerAttack.h
 *
 * @brief  プレイヤーの攻撃状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2025/
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef PLAYER_ATTACK_DEFINED
#define PLAYER_ATTACK_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
#include"Game/Object/Player/Hand.h"
#include"../State/AttackMotion/AttackMotion.h"
// クラスの宣言 ===============================================================
class Player;

// クラスの定義 ===============================================================
/**
  * @brief 攻撃状態
  */
class PlayerAttack : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:
	// プレイヤー
	Player* m_player;
	// グラフィックス
	Graphics* m_graphics;
	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;

	//モーションさせる手
	Hand* m_pHand;
	//
	float m_motionLerp;

	AttackMotion m_attackMotion;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	PlayerAttack(Player* player,Hand* hand);
	// デストラクタ
	~PlayerAttack();
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


	bool Motion();
	bool Motion2();
	bool Motion3();

};

#endif		// PLAYER_IDLING_DEFINED
