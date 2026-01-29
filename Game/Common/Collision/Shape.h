/**
 * @file   Shape.h
 *
 * @brief  当たり判定の基底クラスに関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/15
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Collision/DisplayCollision.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 当たり判定の基底クラス
  */
class Shape
{
// クラス定数の宣言 -------------------------------------------------
public:
	//形状の種類
	enum class ShapeType 
	{
		Box,        ///< ボックス
		Sphere,     ///< 球
		//Capsule,    ///< カプセル
	};

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//形状の種類を取得
	ShapeType GetShapeType() const { return m_shapeType; }
	//当たり判定が有効かを取得
	bool IsEnabled() const { return m_isEnabled; }
	//当たり判定が有効かを設定
	void SetEnabled(bool enable) { m_isEnabled = enable; }
// コンストラクタ/デストラクタ
	// コンストラクタ
	Shape(ShapeType type);
	// デストラクタ
	~Shape();
// 操作
	//衝突しているか
	virtual bool Intersects(Shape* other) = 0;
	virtual bool Contains(Shape* other)=0;
	//当たり判定描画クラスに登録
	virtual void AddDisplayCollision(Ito::DisplayCollision* dC)=0;
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	// 形状の種類
	ShapeType m_shapeType; 
	//当たり判定が有効か
	bool m_isEnabled;
};

