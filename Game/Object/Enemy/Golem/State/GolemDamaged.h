/**
 * @file   GolemDamaged.h
 *
 * @brief  ゴーレムのダメージをくらった状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/11/15
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef GOLEM_DAMAGED_DEFINED
#define GOLEM_DAMAGED_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
// クラスの宣言 ===============================================================
class Golem;

// クラスの定義 ===============================================================
/**
  * @brief ゴーレムの待機状態
  */
class GolemDamaged : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:
// データメンバの宣言 -----------------------------------------------
private:
	//ゴーレム
	Golem* m_golem;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GolemDamaged(Golem* golem);
	// デストラクタ
	~GolemDamaged();
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

#endif		// SOLDIER_IDLING_DEFINED
