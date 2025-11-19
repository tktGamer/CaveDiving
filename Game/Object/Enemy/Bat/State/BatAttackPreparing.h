/**
 * @file   BatAttackPreparing.h
 *
 * @brief  コウモリの攻撃準備状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/09/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef BAT_ATTACK_PREPARING_DEFINED
#define BAT_ATTACK_PREPARING_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"

#include"Game/Motion/BatMotion/BatAttackPreparingMotion.h"
// クラスの宣言 ===============================================================
class Bat;

// クラスの定義 ===============================================================
/**
  * @brief コウモリの攻撃状態
  */
class BatAttackPreparing : public IState
{
	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	BatAttackPreparing(Bat* bat, Wing* pRightWing, Wing* pLeftWing);
	// デストラクタ
	~BatAttackPreparing();
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
	Bat* m_bat;
	// グラフィックス
	Graphics* m_graphics;
	//攻撃準備モーション
	std::unique_ptr<Motion> m_attackPreparingMotion;

};

#endif		// SOLDIER_IDLING_DEFINED
