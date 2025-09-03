/**
 * @file   Shape.cpp
 *
 * @brief  当たり判定の基底クラスに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2025/08/27
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Shape.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] type 形状の種類
 */
Shape::Shape(ShapeType type)
	:m_shapeType(type)
	,m_isEnabled(true)
{
}

/**
 * @brief デストラクタ
 */
Shape::~Shape()
{

}


