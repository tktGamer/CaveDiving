/**
 * @file   GolemAttack.h
 *
 * @brief  ゴーレムの攻撃状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef GOLEM_ATTACK_DEFINED
#define GOLEM_ATTACK_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
#include"Game/Motion/GolemMotion/GolemPunchMotion.h"
#include"Game/Motion/GolemMotion/GolemSlammedDownMotion.h"
// クラスの宣言 ===============================================================
class Golem;
class GolemHand;
// クラスの定義 ===============================================================
/**
  * @brief ゴーレムの攻撃状態
  */
class GolemAttack : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	GolemAttack(Golem* golem);
	// デストラクタ
	~GolemAttack();
//　操作
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
	//攻撃方法を決める
	void DecideMotion();

// データメンバの宣言 -----------------------------------------------
private:
	// ゴーレムのポインタ
	Golem* m_golem;
	//攻撃モーション
	std::unique_ptr<AttackMotion> m_attackMotion;
};
#endif		// GOLEM_ATTACK_DEFINED