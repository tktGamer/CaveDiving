/**
 * @file   IState.h
 *
 * @brief  ステートのインターフェイスの定義に関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2025/09/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef STATE_DEFINED
#define STATE_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "StepTimer.h"
#include <Keyboard.h>
#include"Game/Interface/IObserver.h"
#include"Game/Common/Graphics.h"


// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief IStateインターフェイスを定義する
  */
class IState
{
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
// 仮想デストラクタ
	virtual ~IState() = default;
// 操作
public:
	// 初期化する 
	virtual void Initialize() = 0;
	// 事前更新する
	virtual void PreUpdate() = 0;
	// 処理を実行する
	virtual void Update(const float& elapsedTime) = 0;
	// 事後更新する
	virtual void PostUpdate() = 0;
	// テクスチャを描画する
	virtual void Render() = 0;
	// 後始末をする
	virtual void Finalize() = 0;
};

#endif // STATE_DEFINED
