/**
 * @file   Shape.h
 *
 * @brief  当たり判定の基底クラスに関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2025/7/02
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
		Capsule,    ///< カプセル
	};

// データメンバの宣言 -----------------------------------------------
private:
	ShapeType m_shapeType; ///< 形状の種類
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Shape(ShapeType type);

	// デストラクタ
	~Shape();


// 操作
public:
	virtual bool Intersects(Shape* other) = 0;

	virtual void AddDisplayCollision(Ito::DisplayCollision* dC)=0;
//　取得・設定
public:
	ShapeType GetShapeType() const { return m_shapeType; }
//　内部操作
private:

};

