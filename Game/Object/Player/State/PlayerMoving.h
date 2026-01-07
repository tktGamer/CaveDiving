/**
 * @file   PlayerMoving.h
 *
 * @brief  プレイヤーの移動状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/08
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef PLAYER_MOVING_DEFINED
#define PLAYER_MOVING_DEFINED
#include "Game/Interface/IState.h"

// クラスの宣言 ===============================================================
class Player;

// クラスの定義 ===============================================================
/**
  * @brief PlayerMoving
  */
class PlayerMoving : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:
	// プレイヤー
	Player* m_pPlayer;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	PlayerMoving(Player* pPlayer);
	// デストラクタ
	~PlayerMoving();

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
#endif		// PLAYER_MOVING_DEFINED
