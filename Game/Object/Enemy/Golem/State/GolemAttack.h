/**
 * @file   GolemAttack.h
 *
 * @brief  ゴーレムの攻撃状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/09/15
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef GOLEM_ATTACK_DEFINED
#define GOLEM_ATTACK_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"

#include"Game/Motion/GolemMotion/GolemPunchMotion.h"
#include"Game/Motion/GolemMotion/GolemSlammedDownMotion.h"
#include"Game/Object/Enemy/Golem/GolemHand.h"

// クラスの宣言 ===============================================================
class Golem;

// クラスの定義 ===============================================================
/**
  * @brief ゴーレムの攻撃状態
  */
class GolemAttack : public IState
{
public:
	// コンストラクタ
	GolemAttack(Golem* golem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand);
	// デストラクタ
	~GolemAttack();
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


	//攻撃方法を決める
	void DecideMotion();

private:
	// ゴーレム
	Golem* m_golem;
	GolemHand* m_pRightHand;
	GolemHand* m_pLeftHand;

	// グラフィックス
	Graphics* m_graphics;
	//攻撃モーション
	std::unique_ptr<Motion> m_attackMotion;

};

#endif		// SOLDIER_IDLING_DEFINED
