/**
 * @file   PlayerAvoidance.h
 *
 * @brief  プレイヤーの回避状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/07
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
private:
	//回避スピード
	static constexpr float DODGE_SPEED = 1.0f;
	//回避時間
	static constexpr float DOOGE_TIME = 0.05f;
public:

// データメンバの宣言 -----------------------------------------------
private:
	// プレイヤーのポインタ
	Player* m_pPlayer;

	//回避方向
	DirectX::SimpleMath::Vector3 m_dodgeDirection;
	//回避時間
	float m_dodgeTime = 0;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//コンストラクタ
	PlayerAvoidance(Player* pPlayer);
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
//　取得・設定
public:

//　内部操作
private:

};
#endif		// PLAYER_AVOID_DEFINED
