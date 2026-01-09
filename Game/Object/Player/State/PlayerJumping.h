/**
 * @file   PlayerJumping.h
 *
 * @brief  プレイヤーのジャンプ状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/08
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef PLAYER_JUMPING_DEFINED
#define PLAYER_JUMPING_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"

// クラスの宣言 ===============================================================
class Player;

// クラスの定義 ===============================================================
/**
  * @brief PlayerJumping
  */
class PlayerJumping : public IState
{
// クラス定数の宣言 -------------------------------------------------
private:
	//ジャンプ力
	static constexpr float JUMP_POWER = 0.3f;
public:

// データメンバの宣言 -----------------------------------------------
private:
	// プレイヤー
	Player* m_pPlayer;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	PlayerJumping(Player* pPlayer);
	// デストラクタ
	~PlayerJumping();

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
#endif		// PLAYER_JUMPING_DEFINED
