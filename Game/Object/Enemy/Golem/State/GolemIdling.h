/**
 * @file   GolemIdling.h
 *
 * @brief  ゴーレムの移動状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/09/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef GOLEM_IDLING_DEFINED
#define GOLEM_IDLING_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
// クラスの宣言 ===============================================================
class Golem;

// クラスの定義 ===============================================================
/**
  * @brief ゴーレムの待機状態
  */
class GolemIdling : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:
// データメンバの宣言 -----------------------------------------------
private:
	// ゴーレム
	Golem* m_golem;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GolemIdling(Golem* golem);
	// デストラクタ
	~GolemIdling();
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
