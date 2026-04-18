/**
 * @file   IGameObject.h
 *
 * @brief  オブジェクトのインターフェイスの定義に関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2026/03/03
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef OBJECT_DEFINED
#define OBJECT_DEFINED
// ヘッダファイルの読み込み ===================================================
#include"Game/Interface/IObserver.h"
#include <SimpleMath.h>
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief コンポーネントインターフェイスを定義する
  */
class IGameObject :public IObserver
{
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
// 仮想デストラクタ
	virtual ~IGameObject() = default;
// 操作
public:
	// 初期化する 
	virtual void Initialize() = 0;
	// 処理を実行する
	virtual void Update() = 0;
	// テクスチャを描画する
	virtual void Draw() = 0;
	// 後始末をする
	virtual void Finalize() = 0;
};

#endif // OBJECT_DEFINED
