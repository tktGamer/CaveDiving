/**
 * @file   CollisionManager.cpp
 *
 * @brief  当たり判定管理に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "CollisionManager.h"

// クラスの静的メンバ変数の初期化
std::unique_ptr<CollisionManager> CollisionManager::s_collisionManager = nullptr;

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
CollisionManager::CollisionManager()
	:m_graphics{Graphics::GetInstance()}
{

}



/**
 * @brief デストラクタ
 */
CollisionManager::~CollisionManager()
{

}



CollisionManager* const CollisionManager::GetInstance()
{
	if (s_collisionManager == nullptr)
	{
		//ResourceManagerオブジェクトを生成し、そのポインタをs_collisionManagerに格納する
		s_collisionManager.reset(new CollisionManager());
	}
	return s_collisionManager.get();
}


/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void CollisionManager::Register()
{
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
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void CollisionManager::Draw()
{
	ID3D11DeviceContext*		 context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = m_graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = m_graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = m_graphics->GetProjectionMatrix();
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
DirectX::SimpleMath::Vector3 CollisionManager::PushOut(Box* box, Sphere* sphere)
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

    // 押し出し処理
    if (distance > 0.0f) {
        float overlap = sphere->GetRadius() - distance;
        collisionVector.x /= distance;
        collisionVector.y /= distance;
        collisionVector.z /= distance;

        sphereCenter.x += collisionVector.x * overlap;
        sphereCenter.y += collisionVector.y * overlap;
        sphereCenter.z += collisionVector.z * overlap;
    }
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
