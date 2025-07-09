/**
 * @file   Shape.cpp
 *
 * @brief  当たり判定の基底クラスに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2025/7/02
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Shape.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Shape::Shape(ShapeType type)
	:m_shapeType(type)
{
}

/**
 * @brief デストラクタ
 */
Shape::~Shape()
{

}


