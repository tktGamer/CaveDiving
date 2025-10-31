/**
 * @file   GolemMoving.h
 *
 * @brief  コウモリの移動状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/09/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef BAT_MOVING_DEFINED
#define BAT_MOVING_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
// クラスの宣言 ===============================================================
class Golem;

// クラスの定義 ===============================================================
/**
  * @brief コウモリの移動状態
  */
class GolemMoving : public IState
{
public:
	// コンストラクタ
	GolemMoving(Golem* golem);
	// デストラクタ
	~GolemMoving();
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
};
#endif		// BAT_IDLING_DEFINED
