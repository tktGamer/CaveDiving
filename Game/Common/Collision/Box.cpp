/**
 * @file   Box.cpp
 *
 * @brief  AABBの当たり判定に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付 2025/7/02
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Box.h"


#include "../Collision/Sphere.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] center 中心座標
 * @param[in] halfSize 半分のサイズ
 * 
 */
Box::Box(DirectX::SimpleMath::Vector3 center, DirectX::SimpleMath::Vector3 halfSize)
	:Shape(ShapeType::Box)
	, m_center(center)
	, m_halfSize(halfSize)
{
}

/**
 * @brief デストラクタ
 */
Box::~Box()
{

}




/**
 * @brief 他の形状と衝突判定を行う
 *
 * @param[in] other 衝突判定を行う他の形状
 *
 * @return 衝突しているかどうか
 */
bool Box::Intersects(Shape* other)
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




void Box::AddDisplayCollision(Ito::DisplayCollision* dC)
{
	DirectX::BoundingBox bb{ m_center,m_halfSize };
	dC->AddBoundingVolume(bb);
}

/**
 * @brief 中心座標を設定する
 *
 * @param[in] center 中心座標
 *
 * @return なし
 */
void Box::SetCenter(const DirectX::SimpleMath::Vector3& center)
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
DirectX::SimpleMath::Vector3 Box::GetCenter() const
{
	return m_center;
}

/**
 * @brief 半分のサイズを設定する
 *
 * @param[in] halfSize 半分のサイズ
 *
 * @return なし
 */
void Box::SetHalfSize(const DirectX::SimpleMath::Vector3& halfSize)
{
	m_halfSize = halfSize;
}


/**
 * @brief 半分のサイズを取得する
 *
 * @param[in] なし
 *
 * @return 半分のサイズ
 */
DirectX::SimpleMath::Vector3 Box::GetHalfSize() const
{
	return m_halfSize;
}

/**
 * @brief 他のAABBと衝突判定を行う
 *
 * @param[in] other 衝突判定を行う他のAABB
 *
 * @return 衝突しているかどうか
 */
bool Box::IntersectBox(Box* other)
{
	DirectX::SimpleMath::Vector3 thiMin = m_center - m_halfSize;
	DirectX::SimpleMath::Vector3 thiMax = m_center + m_halfSize;
	DirectX::SimpleMath::Vector3 otherMin = other->GetCenter() - other->GetHalfSize();
	DirectX::SimpleMath::Vector3 otherMax = other->GetCenter() + other->GetHalfSize();
	// AABBの衝突判定を行う

	if (thiMin.x > otherMax.x || thiMax.x < otherMin.x ||
		thiMin.y > otherMax.y || thiMax.y < otherMin.y ||
		thiMin.z > otherMax.z || thiMax.z < otherMin.z)
	{
		return false; // 衝突していない
	}

	return true;
}

/**
 * @brief 球と衝突判定を行う
 *
 * @param[in] other 衝突判定を行う球
 *
 * @return 衝突しているかどうか
 */
bool Box::IntersectSphere(Sphere* other) const
{
	//球とAABB
	DirectX::SimpleMath::Vector3 boxMin = m_center - m_halfSize;
	DirectX::SimpleMath::Vector3 boxMax = m_center + m_halfSize;
	DirectX::SimpleMath::Vector3 sphereCenter = other->GetCenter();
	// AABBの最も近い点を計算
	float x = std::max(boxMin.x, std::min(sphereCenter.x, boxMax.x));
	float y = std::max(boxMin.y, std::min(sphereCenter.y, boxMax.y));
	float z = std::max(boxMin.z, std::min(sphereCenter.z, boxMax.z));

	// 球の中心と最も近い点との距離の二乗を計算
	float distanceSquared = (x - sphereCenter.x) * (x - sphereCenter.x) +
							(y - sphereCenter.y) * (y - sphereCenter.y) +
							(z - sphereCenter.z) * (z - sphereCenter.z);

	// 距離の二乗が球の半径の二乗以下であれば当たり
	return distanceSquared <= (other->GetRadius() * other->GetRadius());

}
