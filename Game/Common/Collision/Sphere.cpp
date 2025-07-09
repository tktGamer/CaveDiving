/**
 * @file   Sphere.cpp
 *
 * @brief  球状の当たり判定に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付 2025/7/02
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Sphere.h"
#include "../Collision/Box.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] center 中心座標
 * @param[in] radius 半径
 */
Sphere::Sphere(DirectX::SimpleMath::Vector3 center, float radius)
	: Shape(ShapeType::Sphere)
	, m_center(center)
	, m_radius(radius)
{
}

/**
 * @brief デストラクタ
 */
Sphere::~Sphere()
{

}




/**
 * @brief 他の形状と衝突判定を行う
 *
 * @param[in] other 衝突判定を行う他の形状
 *
 * @return 衝突しているかどうか
 */
bool Sphere::Intersects(Shape* other)
{

	if (other == nullptr)
	{
		return false;
	}

	//形状の種類を確認
	switch (other->GetShapeType())
	{
	case ShapeType::Box:
		return IntersectBox(static_cast<Box*>(other));
		break;
	case ShapeType::Sphere:
		return IntersectSphere(static_cast<Sphere*>(other));
		break;
	default:
		break;
	}


	return false;
}


/**
 * @brief 当たり判定描画クラスに追加
 *
 * @param[in] dC 当たり判定描画クラス
 *
 * @return なし
 */
void Sphere::AddDisplayCollision(Ito::DisplayCollision* dC)
{
	DirectX::BoundingSphere bs{ m_center,m_radius };
	dC->AddBoundingVolume(bs);
}

/**
 * @brief 中心座標を設定する
 *
 * @param[in] center 中心座標
 *
 * @return なし
 */
void Sphere::SetCenter(const DirectX::SimpleMath::Vector3& center)
{
	m_center = center;
}

/**
 * @brief 中心座標を取得する
 * 
 * @param[in] なし
 *
 * @return 中心座標
 */
DirectX::SimpleMath::Vector3 Sphere::GetCenter() const
{
	return m_center;
}

/**
 * @brief 半径を設定する
 *
 * @param[in] radius 半径
 *
 * @return なし
 */
void Sphere::SetRadius(float radius)
{
	m_radius = radius;
}

/**
 * @brief 半径を取得する
 * 
 * @param[in] なし
 * 
 * @return 半径
 */
float Sphere::GetRadius() const
{
	return m_radius;
}

/**
 * @brief 球状とAABBの衝突判定を行う
 *
 * @param[in] other 衝突判定を行うAABB
 *
 * @return 衝突しているかどうか
 */
bool Sphere::IntersectBox(Box* other) const
{
	//球とAABB
	DirectX::SimpleMath::Vector3 boxMin = other->GetCenter() - other->GetHalfSize();
	DirectX::SimpleMath::Vector3 boxMax = other->GetCenter() + other->GetHalfSize();

	// AABBの最も近い点を計算
	float x = std::max(boxMin.x, std::min(m_center.x, boxMax.x));
	float y = std::max(boxMin.y, std::min(m_center.y, boxMax.y));
	float z = std::max(boxMin.z, std::min(m_center.z, boxMax.z));

	// 球の中心と最も近い点との距離の二乗を計算
	float distanceSquared = (x - m_center.x) * (x - m_center.x) +
							(y - m_center.y) * (y - m_center.y) +
							(z - m_center.z) * (z - m_center.z);

	// 距離の二乗が球の半径の二乗以下であれば当たり
	return distanceSquared <= (m_radius * m_radius);

}


/**
 * @brief 球状と衝突判定を行う
 *
 * @param[in] other 衝突判定を行う球状
 *
 * @return 衝突しているかどうか
 */
bool Sphere::IntersectSphere(Sphere* other) const
{
	//球と球の当たり判定
	DirectX::SimpleMath::Vector3 distance = m_center - other->GetCenter();
	
	float radiusSum = m_radius + other->GetRadius();
	if (distance.LengthSquared() <= radiusSum * radiusSum)
	{
		return true;
	}
	return false;
}
