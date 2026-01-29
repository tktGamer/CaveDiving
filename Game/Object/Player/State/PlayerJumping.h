/**
 * @file   PlayerJumping.h
 *
 * @brief  プレイヤーのジャンプ状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/20
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef PLAYER_JUMPING_DEFINED
#define PLAYER_JUMPING_DEFINED
#include "Game/Interface/IState.h"
#include"Game/Common/Sound.h"
// クラスの宣言 ===============================================================
class Player;
// クラスの定義 ===============================================================
/**
  * @brief ジャンプ状態
  */
class PlayerJumping : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//ジャンプ力
	static constexpr float JUMP_POWER = 0.3f;

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//コンストラクタ
	PlayerJumping(Player* pPlayer);
	// デストラクタ
	~PlayerJumping();
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
	//ジャンプ音
	std::unique_ptr<Sound> m_jumpSound;
};
#endif		// PLAYER_JUMPING_DEFINED