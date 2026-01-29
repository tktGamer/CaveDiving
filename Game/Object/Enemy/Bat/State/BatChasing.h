/**
 * @file   BatChasing.h
 *
 * @brief  コウモリの追跡状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef BAT_CHASING_DEFINED
#define BAT_CHASING_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
// クラスの宣言 ===============================================================
class Bat;
class GameObject;
// クラスの定義 ===============================================================
/**
  * @brief コウモリの追跡状態
  */
class BatChasing : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//攻撃範囲
	static constexpr  float ATTACK_RANGE = 4.5f;
	//追跡速度
	static constexpr  float CHASE_SPPED = 0.7f;

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	BatChasing(Bat* bat);
	// デストラクタ
	~BatChasing();
//  操作
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
	//移動
	void Movement();
	//状態遷移判定
	void CheckStateTransition();
// データメンバの宣言 -----------------------------------------------
private:
	// コウモリのポインタ
	Bat* m_bat;
	//プレイヤーのポインタ
	const GameObject* m_pPlayer;
};
#endif		// BAT_CHASING_DEFINED