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
 * @brief 球とAABBの押し出し処理
 *
 * @param[in] box AABB
 * @param[in] sphere 球(押し出される側)
 *
 * @return 押し出された球の中心位置
 */
DirectX::SimpleMath::Vector3 CollisionManager::PushOut(Box* box, Sphere* sphere,DirectX::SimpleMath::Vector3 moveDir)
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

  //  // 押し出し処理
  //  if (distance > 0.0f) {
  //      float overlap = sphere->GetRadius() - distance;
		//collisionVector.Normalize();

  //      sphereCenter.x += collisionVector.x * overlap;
  //      sphereCenter.y += collisionVector.y * overlap;
  //      sphereCenter.z += collisionVector.z * overlap;
  //  }

	// 押し出し方向が移動ベクトルに対して逆向きであるか？
	collisionVector.Normalize();
	moveDir.Normalize();

	float dot = collisionVector.Dot( moveDir);
    float overlap = sphere->GetRadius() - distance;

	if (dot < 0.0f) {
		// 押し出し方向が移動方向と逆 → 有効な押し出し
		sphereCenter += collisionVector * overlap;
	}
	else {
		// 押し出し方向が移動方向と同じか近い → 無視
		// すり抜け防止のため微修正するならここで対応
	}

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
DirectX::SimpleMath::Vector3 CollisionManager::PushOut(Box* box, Box* box2)
{

	DirectX::SimpleMath::Vector3 box1Min = box->GetCenter() - box->GetHalfSize();
	DirectX::SimpleMath::Vector3 box1Max = box->GetCenter() + box->GetHalfSize();
	DirectX::SimpleMath::Vector3 box2Min = box2->GetCenter() - box2->GetHalfSize();
	DirectX::SimpleMath::Vector3 box2Max = box2->GetCenter() + box2->GetHalfSize();
	// AABBの重なりを計算
	float overlapX = std::min(box1Max.x, box2Max.x) - std::max(box1Min.x, box2Min.x);
	float overlapY = std::min(box1Max.y, box2Max.y) - std::max(box1Min.y, box2Min.y);
	float overlapZ = std::min(box1Max.z, box2Max.z) - std::max(box1Min.z, box2Min.z);
	// 押し出し方向を決定
	DirectX::SimpleMath::Vector3 pushOutDirection;
	if (overlapX < overlapY && overlapX < overlapZ) {
		pushOutDirection.x = (box1Max.x > box2Max.x) ? overlapX : -overlapX;
		pushOutDirection.y = 0.0f;
		pushOutDirection.z = 0.0f;
	}
	else if (overlapY < overlapX && overlapY < overlapZ) {
		pushOutDirection.x = 0.0f;
		pushOutDirection.y = (box1Max.y > box2Max.y) ? overlapY : -overlapY;
		pushOutDirection.z = 0.0f;
	}
	else {
		pushOutDirection.x = 0.0f;
		pushOutDirection.y = 0.0f;
		pushOutDirection.z = (box1Max.z > box2Max.z) ? overlapZ : -overlapZ;
	}
	// 押し出し処理
	return box2->GetCenter() + pushOutDirection * 0.5f; // 中心位置を更新
}

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