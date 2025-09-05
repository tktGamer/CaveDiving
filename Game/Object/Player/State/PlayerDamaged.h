/**
 * @file   PlayerDamaged.h
 *
 * @brief  プレイヤーのダメージをくらった状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2025/
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef PLAYER_DAMAGED_DEFINED
#define PLAYER_DAMAGED_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
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


// データメンバの宣言 -----------------------------------------------
private:
	// プレイヤー
	Player* m_player;
	// グラフィックス
	Graphics* m_graphics;
	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	PlayerDamaged(Player* soldier);
	// デストラクタ
	~PlayerDamaged();
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
