/**
 * @file   BatAttack.h
 *
 * @brief  コウモリの移動状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/09/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef BAT_ATTACK_DEFINED
#define BAT_ATTACK_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"

#include"Game/Motion/BatMotion/BatAttackMotion.h"
// クラスの宣言 ===============================================================
class Bat;

// クラスの定義 ===============================================================
/**
  * @brief コウモリの攻撃状態
  */
class BatAttack : public IState
{
public:
	// コンストラクタ
	BatAttack(Bat* bat, Wing* pRightWing, Wing* pLeftWing);
	// デストラクタ
	~BatAttack();
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
	//攻撃モーション
	std::unique_ptr<Motion> m_attackMotion;

};

#endif		// SOLDIER_IDLING_DEFINED
