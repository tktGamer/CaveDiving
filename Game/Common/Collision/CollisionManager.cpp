/**
 * @file   CollisionManager.cpp
 *
 * @brief  当たり判定管理に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/08/22
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "CollisionManager.h"

// クラスの静的メンバ変数の初期化
std::unique_ptr<CollisionManager> CollisionManager::s_collisionManager = nullptr;

// メンバ関数の定義 ===========================================================
/**
 * @brief インスタンスを取得する
 *
 * @param[in] なし
 *
 * @return 当たり判定管理クラスのポインタ
 */
CollisionManager* const CollisionManager::GetInstance()
{
	//一度も生成されていなかったら
	if (s_collisionManager == nullptr)
	{
		//ResourceManagerオブジェクトを生成し、そのポインタをs_collisionManagerに格納する
		s_collisionManager.reset(new CollisionManager());
	}
	return s_collisionManager.get();
}
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
CollisionManager::CollisionManager()
{

}



/**
 * @brief デストラクタ
 */
CollisionManager::~CollisionManager()
{

}






/**
 * @brief オブジェクトの登録
 *
 * @param[in] obj 登録するオブジェクト
 *
 * @return なし
 */
void CollisionManager::Register(GameObject* obj)
{
	m_objects.push_back(obj);
}

/**
 * @brief オブジェクトの解除
 *
 * @param[in] obj 解除するオブジェクトのポインタ
 *
 * @return なし
 */
void CollisionManager::UnRegister(GameObject* obj)
{
	m_objects.remove(obj);
}



/**
 * @brief 登録されているオブジェクトをすべて解除
 *
 * @param[in] center 中心座標
 *
 * @return なし
 */
void CollisionManager::AllRelease()
{
	m_objects.clear();
}


/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void CollisionManager::Update()
{

}

/**
 * @brief 当たり判定総チェック
 *
 * @param[in] なし
 *
 * @return なし
 */
void CollisionManager::CollisionCheck()
{
	// nullptrを削除
	//m_objects.erase(std::remove(m_objects.begin(), m_objects.end(),
	//	nullptr),
	//	m_objects.end());

	//if(!m_objects.empty())
	//m_objects.remove(nullptr);

	// 登録されたすべてのオブジェクトに対して当たり判定を行う
	for (std::list<GameObject*>::iterator it1 = m_objects.begin(); it1 != m_objects.end(); ++it1)
	{
		//当たり判定が有効ではなかったらスキップ
		if (!(*it1)->GetShape()->IsEnabled()) 
		{
			continue;
		}
		
		//it1より後ろのオブジェクトと当たり判定を行う
		for (std::list<GameObject*>::iterator it2 = std::next(it1); it2 != m_objects.end(); ++it2)
		{
			//当たり判定が有効ではなかったらスキップ
			if (!(*it2)->GetShape()->IsEnabled())
			{
				continue;
			}


			GameObject* obj1 = *it1;
			GameObject* obj2 = *it2;
			// オブジェクト同士の当たり判定を行う
			if (obj1->GetShape()->Intersects(obj2->GetShape())) 
			{
				// 当たり判定が発生した場合の処理
				obj1->CollisionResponce(obj2);
				obj2->CollisionResponce(obj1);
			}
		}
	}
}






/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void CollisionManager::Finalize()
{

}


/**
 * @brief 押し出し処理
 *
 * @param[in] shape1 当たり判定A (押し出される)
 * @param[in] shape2 当たり判定B (押し出す)
 *
 * @return 押し戻された球Aの位置
 */
DirectX::SimpleMath::Vector3 CollisionManager::PushOut(Shape* shape1, Shape* shape2)
{
	switch (shape1->GetShapeType())
	{
	case Shape::ShapeType::Box:
		switch (shape2->GetShapeType())
		{
		case Shape::ShapeType::Box:
		return BoxToBoxPushOut(
			dynamic_cast<Box*>(shape1),
			dynamic_cast<Box*>(shape2));

		case Shape::ShapeType::Sphere:
			Box* box = dynamic_cast<Box*>(shape1);
			Sphere* sphere = dynamic_cast<Sphere*>(shape2);
			return BoxToSpherePushOut(
				box,
				sphere);
		}
		break;

	case Shape::ShapeType::Sphere:
		switch (shape2->GetShapeType())
		{
		case Shape::ShapeType::Box:
			// 方向を入れ替える
			//return BoxToSpherePushOut(
			//	dynamic_cast<Box*>(shape2),
			//	dynamic_cast<Sphere*>(shape1));

		case Shape::ShapeType::Sphere:
			return SphereToSpherePushOut(
				dynamic_cast<Sphere*>(shape1),
				dynamic_cast<Sphere*>(shape2));
		}
		break;
	}

	return DirectX::SimpleMath::Vector3::Zero;
}

/**
 * @brief 球同士の押し出し処理
 *
 * @param[in] sphereA 球A (押し出される球)
 * @param[in] sphereB 球B (押し出す球)
 *
 * @return 押し戻された球Aの位置
 */
DirectX::SimpleMath::Vector3 CollisionManager::SphereToSpherePushOut(Sphere* sphereA, Sphere* sphereB)
{
	// 中心間ベクトル
	DirectX::SimpleMath::Vector3 direction = sphereA->GetCenter() - sphereB->GetCenter();
	float distance = direction.Length();

	//球が重なっているか
	if (sphereA->GetRadius() + sphereB->GetRadius() > distance) 
	{
		
		direction.Normalize();
		// 押し出し距離
		float overlap = (sphereA->GetRadius() + sphereB->GetRadius()) - distance;
		// 押し出し処理
		DirectX::SimpleMath::Vector3 newPosition = sphereA->GetCenter() + direction * overlap;
		return newPosition;
	}
	
	return sphereA->GetCenter();
}

/**
 * @brief 球とAABBの押し出し処理
 *
 * @param[in] box AABB
 * @param[in] sphere 球(押し出される側)
 *
 * @return 押し出された球の中心位置
 */
DirectX::SimpleMath::Vector3 CollisionManager::BoxToSpherePushOut(Box* box, Sphere* sphere/*,DirectX::SimpleMath::Vector3 moveDir*/)
{
    DirectX::SimpleMath::Vector3 boxMin = box->GetCenter() - box->GetHalfSize();
    DirectX::SimpleMath::Vector3 boxMax = box->GetCenter() + box->GetHalfSize();
    DirectX::SimpleMath::Vector3 sphereCenter = sphere->GetCenter();

    // AABBの最も近い点を計算
    float closestX = std::max(boxMin.x, std::min(sphereCenter.x, boxMax.x));
    float closestY = std::max(boxMin.y, std::min(sphereCenter.y, boxMax.y));
    float closestZ = std::max(boxMin.z, std::min(sphereCenter.z, boxMax.z));

    // 球の中心と最も近い点のベクトルを計算
    DirectX::SimpleMath::Vector3 collisionVector = {
        sphereCenter.x - closestX,
        sphereCenter.y - closestY,
        sphereCenter.z - closestZ
    };

    // ベクトルの長さを計算
    float distance = sqrt(collisionVector.x * collisionVector.x +
        collisionVector.y * collisionVector.y +
        collisionVector.z * collisionVector.z);


	// 押し出し方向が移動ベクトルに対して逆向きであるか？
	collisionVector.Normalize();
	//moveDir.Normalize();

	//float dot = collisionVector.Dot( moveDir);
    float overlap = sphere->GetRadius() - distance;

	//if (dot < 0.0f) {
	//	// 押し出し方向が移動方向と逆 → 有効な押し出し
	//	sphereCenter += collisionVector * overlap;
	//}
	//else {
	//	// 押し出し方向が移動方向と同じか近い → 無視
	//	// すり抜け防止のため微修正するならここで対応
	//}

		sphereCenter += collisionVector * overlap;
	sphere->SetCenter(sphereCenter);
	return sphereCenter;
}

/**
 * @brief AABB同士の押し出し処理
 *
 * @param[in] box AABB1
 * @param[in] box2 AABB2 (押し出される側)
 *
 * @return 押し出されたAABB2の中心位置
 */
DirectX::SimpleMath::Vector3 CollisionManager::BoxToBoxPushOut(Box* box, Box* box2)
{
	using Vector3 = DirectX::SimpleMath::Vector3;

	// 中心と半サイズ
	Vector3 c1 = box->GetCenter();
	Vector3 e1 = box->GetHalfSize();
	Vector3 c2 = box2->GetCenter();
	Vector3 e2 = box2->GetHalfSize();

	// 中心差
	Vector3 delta = c2 - c1;

	// 各軸の重なり量
	float overlapX = (e1.x + e2.x) - std::abs(delta.x);
	float overlapY = (e1.y + e2.y) - std::abs(delta.y);
	float overlapZ = (e1.z + e2.z) - std::abs(delta.z);

	// 重なっていなければそのまま
	if (overlapX <= 0.0f || overlapY <= 0.0f || overlapZ <= 0.0f)
	{
		return c2;
	}

	// 押し出しベクトル（最小貫通軸）
	Vector3 pushOut = Vector3::Zero;

	if (overlapX <= overlapY && overlapX <= overlapZ)
	{
		pushOut.x = (delta.x >= 0.0f) ? overlapX : -overlapX;
	}
	else if (overlapY <= overlapX && overlapY <= overlapZ)
	{
		pushOut.y = (delta.y >= 0.0f) ? overlapY : -overlapY;
	}
	else
	{
		pushOut.z = (delta.z >= 0.0f) ? overlapZ : -overlapZ;
	}

	// box2 を押し出す
	return c2 + pushOut;
}


/**
 * @brief 球同士の押し戻し処理
 *
 * @param[in] sphereA 球A (小さい球)
 * @param[in] sphereB 球B (大きい球)
 *
 * @return 押し戻された球Aの位置
 */
DirectX::SimpleMath::Vector3 CollisionManager::PushBack(Sphere* sphereA, Sphere* sphereB)
{

	// 中心間ベクトル
	DirectX::SimpleMath::Vector3 direction = sphereA->GetCenter() - sphereB->GetCenter();
	float distance = direction.Length();


	//direction = direction.Normalize();

	// 球AがBの外に出ているなら
	if (distance + sphereA->GetRadius() > sphereB->GetRadius())
	{
		// A を B の内側ギリギリまで押し戻す
		float targetDistance = sphereB->GetRadius() - sphereA->GetRadius();
		float pushBackDistance = distance - targetDistance;

		DirectX::SimpleMath::Vector3 correction = direction;
		correction.Normalize();
		correction *= -pushBackDistance;
		
		return sphereA->GetCenter() + correction;
	}

	return sphereA->GetCenter();
}


/**
 * @brief 当たり判定の接触点（中間地点）の取得
 *
 * @param[in] shapeA 当たり判定A 
 * @param[in] shapeB 当たり判定B 
 *
 * @return 中間点
 */
DirectX::SimpleMath::Vector3 CollisionManager::CheckContactPoint(Shape* shapeA, Shape* shapeB)
{
	Shape::ShapeType shapeTypeA = shapeA->GetShapeType();
	Shape::ShapeType shapeTypeB = shapeB->GetShapeType();

	if (shapeTypeA == Shape::ShapeType::Sphere) 
	{
		if (shapeTypeB == Shape::ShapeType::Sphere) 
		{
			return ContactPointSphereToSphere(dynamic_cast<Sphere*>(shapeA), dynamic_cast<Sphere*>(shapeB));
		}
		else if (shapeTypeB == Shape::ShapeType::Box) 
		{
			return ContactPointSphereToBox(dynamic_cast<Sphere*>(shapeA), dynamic_cast<Box*>(shapeB));

		}
	}
	else if (shapeTypeA == Shape::ShapeType::Box) 
	{
		if (shapeTypeB == Shape::ShapeType::Sphere) 
		{
			return ContactPointSphereToBox(dynamic_cast<Sphere*>(shapeB), dynamic_cast<Box*>(shapeA));
		}
		else if (shapeTypeB == Shape::ShapeType::Box) 
		{
			//return ContactPointBoxToBox(dynamic_cast<Box*>(shapeB), dynamic_cast<Box*>(shapeA));
		}
	}
	//どこにも属さなかった
	return { 0,0,0 };
}


/**
 * @brief 球同士の接触点（中間地点）の取得
 *
 * @param[in] sphereA 球A
 * @param[in] sphereB 球B
 *
 * @return 球Aと球Bの中間点
 */
DirectX::SimpleMath::Vector3 CollisionManager::ContactPointSphereToSphere(Sphere* sphereA, Sphere* sphereB)
{
	DirectX::SimpleMath::Vector3 diff = sphereB->GetCenter() - sphereA->GetCenter();
	//距離を求める
	float dist = diff.Length();
	float sumR = sphereA->GetRadius() + sphereB->GetRadius();

	//if (dist >= sumR)
	//	return false; // 接触していない

	DirectX::SimpleMath::Vector3 n = diff / dist; // 正規化方向ベクトル
	DirectX::SimpleMath::Vector3 pa = sphereA->GetCenter() + n * sphereA->GetRadius(); // 球Aの表面
	DirectX::SimpleMath::Vector3 pb = sphereB->GetCenter() - n * sphereB->GetRadius(); // 球Bの表面
	return (pa + pb) * 0.5f;  // 中点を接触点とする
}

DirectX::SimpleMath::Vector3 CollisionManager::ContactPointSphereToBox(Sphere* sphere, Box* box)
{

	DirectX::SimpleMath::Vector3 sphereCenter = sphere->GetCenter();
	DirectX::SimpleMath::Vector3 boxCenter = box->GetCenter();
	DirectX::SimpleMath::Vector3 halfSize = box->GetHalfSize();

	// AABB の最小・最大
	DirectX::SimpleMath::Vector3 boxMin = boxCenter - halfSize;
	DirectX::SimpleMath::Vector3 boxMax = boxCenter + halfSize;

	// 球中心を AABB にクランプした点が接触点
	DirectX::SimpleMath::Vector3 contactPoint;
	contactPoint.x = TKTLib::Clamp(sphereCenter.x, boxMin.x, boxMax.x);
	contactPoint.y = TKTLib::Clamp(sphereCenter.y, boxMin.y, boxMax.y);
	contactPoint.z = TKTLib::Clamp(sphereCenter.z, boxMin.z, boxMax.z);

	return contactPoint;
}
