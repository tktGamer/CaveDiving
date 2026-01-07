/**
 * @file   GolemChasing.h
 *
 * @brief  ゴーレムの移動状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef GOLEM_CHASING_DEFINED
#define GOLEM_CHASING_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
// クラスの宣言 ===============================================================
class Golem;
class GameObject;
// クラスの定義 ===============================================================
/**
  * @brief ゴーレムの追跡状態
  */
class GolemChasing : public IState
{
// クラス定数の宣言 -------------------------------------------------
private:
	//追跡速度
	static constexpr  float CHASE_SPPED = 0.5f;
	//攻撃範囲
	static constexpr  float ATTACK_RANGE = 6.5f;

public:
// データメンバの宣言 -----------------------------------------------
private:
	// ゴーレム
	Golem* m_golem;

	//プレイヤーオブジェクトのポインタ
	const GameObject* m_pPlayer;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GolemChasing(Golem* golem);
	// デストラクタ
	~GolemChasing();
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
#endif		// GOLEM_CHASING_DEFINED
