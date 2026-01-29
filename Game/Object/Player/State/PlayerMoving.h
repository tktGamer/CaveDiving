/**
 * @file   PlayerMoving.h
 *
 * @brief  プレイヤーの移動状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/20
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
  * @brief 移動状態
  */
class PlayerMoving : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//コンストラクタ
	PlayerMoving(Player* pPlayer);
	// デストラクタ
	~PlayerMoving();
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
};
#endif		// PLAYER_MOVING_DEFINED