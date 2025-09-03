/**
 * @file   Sphere.h
 *
 * @brief  球状当たり判定に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/08/27
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "../Collision/Shape.h"
// クラスの宣言 ===============================================================
class Box;
// クラスの定義 ===============================================================
/**
  * @brief 球状の当たり判定
  */
class Sphere :public Shape
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:
	// 中心座標
	DirectX::SimpleMath::Vector3 m_center; 
	// 半径
	float m_radius; 
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Sphere(DirectX::SimpleMath::Vector3 center,float radius);

	// デストラクタ
	~Sphere();


// 操作
public:
	//衝突判定
	bool Intersects(Shape* other) override;

//　取得・設定
public:
	//当たり判定描画クラスに追加
	void AddDisplayCollision(Ito::DisplayCollision* dC);

	// 中心座標を設定する
	void SetCenter(const DirectX::SimpleMath::Vector3& center);
	// 中心座標を取得する
	DirectX::SimpleMath::Vector3 GetCenter() const;
	//半径を設定する
	void SetRadius(float radius);
	// 半径を取得する
	float GetRadius() const;
//　内部操作
private:
	//球との衝突判定
	bool IntersectSphere(Sphere* other) const;
	//AABBとの衝突判定
	bool IntersectBox(Box* other) const;
};

