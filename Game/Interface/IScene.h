/**
 * @file   IScene.h
 *
 * @brief  シーンのインターフェイス定義に関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/03/14
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef ISCENE_DEFINED
#define ISCENE_DEFINED
// ヘッダファイルの読み込み ===================================================

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief シーンクラスを定義
  */
class IScene
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
public:
	// デストラクタ
	virtual ~IScene() = default;
	//操作
	// 初期化
	virtual void Initialize() = 0;
	//更新前準備
	virtual void PreUpdate() = 0;
	// 更新
	virtual void Update(float elapsedTime) = 0;
	// 描画
	virtual void Render() = 0;
	// 終了処理
	virtual void Finalize() = 0;
};

#endif	// ISCENE_DEFINED
