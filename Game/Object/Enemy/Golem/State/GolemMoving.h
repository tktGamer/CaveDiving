/**
 * @file   GolemMoving.h
 *
 * @brief  ゴーレムの移動状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef GOLEM_MOVING_DEFINED
#define GOLEM_MOVING_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
// クラスの宣言 ===============================================================
class Golem;
// クラスの定義 ===============================================================
/**
  * @brief ゴーレムの移動状態
  */
class GolemMoving : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//遷移までの時間
	static constexpr float CHANGE_IDLING_TIME = 2.0f;
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	GolemMoving(Golem* golem);
	// デストラクタ
	~GolemMoving();
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
	// ゴーレム
	Golem* m_golem;
};
#endif		// GOLEM_MOVING_DEFINED