/**
 * @file   PlayerDamaged.h
 *
 * @brief  プレイヤーのダメージをくらった状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/20
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef PLAYER_DAMAGED_DEFINED
#define PLAYER_DAMAGED_DEFINED
#include "Game/Interface/IState.h"
// クラスの宣言 ===============================================================
class Player;
// クラスの定義 ===============================================================
/**
  * @brief ダメージをくらった状態
  */
class PlayerDamaged : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//ノックバックの力
	static constexpr float KNOCKBACK_POWER = 20.0f;
	//ノックバックの時間
	static constexpr float KNOCKBACK_TIME = 0.5f;

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	PlayerDamaged(Player* pPlayer);
	// デストラクタ
	~PlayerDamaged();
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
	//ノックバック時間
	float m_knockbackTime = 0.0f;
};
#endif		// PLAYER_DAMAGED_DEFINED