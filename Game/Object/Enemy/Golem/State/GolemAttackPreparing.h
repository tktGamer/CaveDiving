/**
 * @file   GolemAttackPreparing.h
 *
 * @brief  コウモリの攻撃準備状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/09/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef GOLEM_ATTACK_PREPARING_DEFINED
#define GOLEM_ATTACK_PREPARING_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"

//#include"Game/Motion/GolemMotion/GolemAttackPreparingMotion.h"
// クラスの宣言 ===============================================================
class Golem;

// クラスの定義 ===============================================================
/**
  * @brief コウモリの攻撃状態
  */
class GolemAttackPreparing : public IState
{
public:
	// コンストラクタ
	GolemAttackPreparing(Golem* golem);
	// デストラクタ
	~GolemAttackPreparing();
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



private:
	// プレイヤー
	Golem* m_golem;
	// グラフィックス
	Graphics* m_graphics;
	//攻撃準備モーション
	//std::unique_ptr<Motion> m_attackPreparingMotion;

};

#endif		// SOLDIER_IDLING_DEFINED
