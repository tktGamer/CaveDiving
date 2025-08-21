/**
 * @file   Box.h
 *
 * @brief  AABB当たり判定に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/07/02
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "../Collision/Shape.h"
// クラスの宣言 ===============================================================
class Sphere;
// クラスの定義 ===============================================================
/**
  * @brief AABB
  */
class Box :public Shape
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:
	// 中心座標
	DirectX::SimpleMath::Vector3 m_center; 
	// 半分のサイズ
	DirectX::SimpleMath::Vector3 m_halfSize; 

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Box(DirectX::SimpleMath::Vector3 center,DirectX::SimpleMath::Vector3 halfSize);

	// デストラクタ
	~Box();


// 操作
public:
	//当たり判定
	bool Intersects(Shape* other) override;

//　取得・設定
public:
	//当たり判定描画クラスに追加
	void AddDisplayCollision(Ito::DisplayCollision* dC);

	// 中心座標を設定する
	void SetCenter(const DirectX::SimpleMath::Vector3& center);
	// 中心座標を取得する
	DirectX::SimpleMath::Vector3 GetCenter() const;
	// 半分のサイズを設定する
	void SetHalfSize(const DirectX::SimpleMath::Vector3& halfSize);
	// 半分のサイズを取得する
	DirectX::SimpleMath::Vector3 GetHalfSize() const;
//　内部操作
private:
	//AABBとの当たり判定
	bool IntersectBox(Box* other);
	//球との当たり判定
	bool IntersectSphere(Sphere* other) const;

};

