/**
 * @file   PlayerAvoidance.h
 *
 * @brief  プレイヤーの回避状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2025/
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef PLAYER_AVOID_DEFINED
#define PLAYER_AVOID_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"

// クラスの宣言 ===============================================================
class Player;

// クラスの定義 ===============================================================
/**
  * @brief プレイヤーの回避状態
  */
class PlayerAvoidance : public IState
{
	// クラス定数の宣言 -------------------------------------------------
public:
	//回避スピード
	static constexpr float DODGE_SPEED = 1.0f;

	// データメンバの宣言 -----------------------------------------------
private:
	// プレイヤー
	Player* m_player;

	//回避方向
	DirectX::SimpleMath::Vector3 m_dodgeDirection;
	//回避時間
	float m_dodgeTime = 0;
	//最大回避時間
	float m_maxDodgeDuration;
	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:
	PlayerAvoidance(Player* soldier);
	// デストラクタ
	~PlayerAvoidance();
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
