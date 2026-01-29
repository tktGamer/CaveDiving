/**
 * @file   PlayerIdling.h
 *
 * @brief  プレイヤーの待機状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/20
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef PLAYER_IDLING_DEFINED
#define PLAYER_IDLING_DEFINED
#include "Game/Interface/IState.h"
#include"Game/Motion/PlayerMotion/PlayerIdlingMotion.h"
// クラスの宣言 ===============================================================
class Player;

// クラスの定義 ===============================================================
/**
  * @brief 待機状態
  */
class PlayerIdling : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	PlayerIdling(Player* pPlayer);
	// デストラクタ
	~PlayerIdling();
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
	//待機状態モーション
	std::unique_ptr<Motion> m_idlingMotion;
};
#endif		// PLAYER_IDLING_DEFINED