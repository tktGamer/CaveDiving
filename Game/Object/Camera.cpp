// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Camera.h"

using namespace DirectX;

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Camera::Camera()
    :m_up{0.0f,1.0f,0.0f}
    ,m_view{}
	, m_eyePos{}
	, m_targetPos{}
	, m_distance{ 0.0f, 0.0f, 10.0f } // デフォルトの距離を設定
{
}

Camera::~Camera()
{
}


/**
 * @brief 初期化処理
 *
 * @param[in] position カメラの位置
 *
 * @return なし
 */
void Camera::Initialize(DirectX::SimpleMath::Vector3 eyePos)
{
	m_eyePos = eyePos;
    m_up={ 0.0f,1.0f,0.0f };

}

/**
 * @brief 更新処理
 *
 * @param[in] 
 *
 * @return なし
 */
void Camera::Update(float elapsedTime)
{
    DirectX::SimpleMath::Vector3 pos = m_target + m_distance; // 本来到達しているべきカメラ位置
    m_eyePos = DirectX::SimpleMath::Vector3::Lerp(m_eyePos, pos, elapsedTime * 3.0f); // Lerp減衰
    //自分で作成したビュー行列で設定する
    m_view = SimpleMath::Matrix::CreateLookAt(
        m_eyePos,       //カメラの位置
        m_target,    //ターゲットの位置
        m_up);          //カメラの上ベクトル



}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Camera::Finalize()
{
}


void Camera::SetEyePos(DirectX::SimpleMath::Vector3 position)
{
	m_eyePos = position;
}

void Camera::SetEyePosX(float posX)
{
	m_eyePos.x = posX;
}

void Camera::SetEyePosY(float posY)
{
	m_eyePos.y = posY;
}

void Camera::SetEyePosZ(float posZ)
{
	m_eyePos.z = posZ;
}

void Camera::SetTartet(const DirectX::SimpleMath::Vector3& targetPos, const DirectX::SimpleMath::Quaternion& rotate)
{
	m_targetPos = &targetPos;
	m_targetRotate = &rotate; // ターゲットの回転も設定
}


void Camera::SetDistance(DirectX::SimpleMath::Vector3 distance)
{
	m_distance = distance;
}

DirectX::SimpleMath::Matrix Camera::GetView()
{
    return m_view;
}
