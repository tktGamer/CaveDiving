/**
 * @file   Sphere.h
 *
 * @brief  球状当たり判定に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/18
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

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
	// 中心座標を設定する
	void SetCenter(const DirectX::SimpleMath::Vector3& center);
	// 中心座標を取得する
	const DirectX::SimpleMath::Vector3& GetCenter() const;
	//半径を設定する
	void SetRadius(const float& radius);
	// 半径を取得する
	const float& GetRadius() const;
// コンストラクタ/デストラクタ
	// コンストラクタ
	Sphere(const DirectX::SimpleMath::Vector3& center,const float& radius);
	// デストラクタ
	~Sphere();
// 操作
	//衝突判定
	bool Intersects(Shape* other) override;
	bool Contains(Shape* other) override;
	//当たり判定描画クラスに追加
	void AddDisplayCollision(Ito::DisplayCollision* dC);
//　内部操作
private:
	//球との衝突判定
	bool IntersectSphere(const Sphere* other) const;
	//AABBとの衝突判定
	bool IntersectBox(const Box* other) const;
	//球との内包判定
	bool ContainsSphere(const Sphere* other) const;
	//AABBとの内包判定
	bool ContainsBox(const Box* other) const;

// データメンバの宣言 -----------------------------------------------
private:
	// 中心座標
	DirectX::SimpleMath::Vector3 m_center; 
	// 半径
	float m_radius; 
};

