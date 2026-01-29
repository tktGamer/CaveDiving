/**
 * @file   BatMoving.h
 *
 * @brief  コウモリの移動状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef BAT_MOVING_DEFINED
#define BAT_MOVING_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
// クラスの宣言 ===============================================================
class Bat;
// クラスの定義 ===============================================================
/**
  * @brief コウモリの移動状態
  */
class BatMoving : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//移動速度
	static constexpr float MOVING_SPEED = 5.0f;
	//遷移までの時間
	static constexpr float CHANGE_IDLING_TIME = 2.0f;
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	BatMoving(Bat* bat);
	// デストラクタ
	~BatMoving();
//  操作
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
};
#endif		// BAT_MOVING_DEFINED