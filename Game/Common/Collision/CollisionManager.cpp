/**
 * @file   CollisionManager.cpp
 *
 * @brief  ＸＸＸＸに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "CollisionManager.h"

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



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void CollisionManager::Initialize()
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
