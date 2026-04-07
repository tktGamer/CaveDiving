/**
 * @file   BatAttackPreparing.h
 *
 * @brief  コウモリの攻撃準備状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef BAT_ATTACK_PREPARING_DEFINED
#define BAT_ATTACK_PREPARING_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
// クラスの宣言 ===============================================================
class Bat;
class Motion;
// クラスの定義 ===============================================================
/**
  * @brief コウモリの攻撃状態
  */
class BatAttackPreparing : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	BatAttackPreparing(Bat* bat, Wing* pRightWing, Wing* pLeftWing);
	// デストラクタ
	~BatAttackPreparing();
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

// データメンバの宣言 -----------------------------------------------
private:
	// コウモリのポインタ
	Bat* m_bat;
	//攻撃準備モーション
	std::unique_ptr<Motion> m_attackPreparingMotion;
};
#endif		// BAT_ATTACK_PREPARING_DEFINED