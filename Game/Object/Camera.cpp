/**
 * @file   Camera.cpp
 *
 * @brief  カメラに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/23
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Camera.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Camera::Camera()
    :
	m_up{DirectX::SimpleMath::Vector3::Up},
	m_view{},
	m_eyePos{},
	m_targetPos{},
	m_targetRotate{},
	m_distance{ DEFAULT_DISTANCE } // デフォルトの距離を設定
{
}

/**
 * @brief デストラクタ
 */
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
void Camera::Initialize(const DirectX::SimpleMath::Vector3& eyePosition)
{
	m_eyePos = eyePosition;
	m_up = DirectX::SimpleMath::Vector3::Up;
}

/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime
 *
 * @return なし
 */
void Camera::Update(const float& elapsedTime)
{
	
	// ターゲットの位置
	DirectX::SimpleMath::Vector3 targetpos = *m_targetPos; 
	//　ターゲットの回転を考慮してカメラの位置を加算
	targetpos += DirectX::SimpleMath::Vector3::Transform(m_distance,*m_targetRotate);
	//
    m_eyePos = DirectX::SimpleMath::Vector3::Lerp(m_eyePos, targetpos, elapsedTime * 5.0f); // Lerp減衰


    //自分で作成したビュー行列で設定する
    m_view = DirectX::SimpleMath::Matrix::CreateLookAt(
        m_eyePos,       //カメラの位置
        *m_targetPos,    //ターゲットの位置
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


/**
 * @brief カメラ位置設定
 *
 * @param[in] positon  カメラ位置
 *
 * @return なし
 */
void Camera::SetEyePos(const DirectX::SimpleMath::Vector3& position)
{
	m_eyePos = position;
}

/**
 * @brief カメラのX位置設定
 *
 * @param[in] posX  X位置
 *
 * @return なし
 */
void Camera::SetEyePosX(const float& posX)
{
	m_eyePos.x = posX;
}

/**
 * @brief カメラのY位置設定
 *
 * @param[in] posY  Y位置
 *
 * @return なし
 */
void Camera::SetEyePosY(const float& posY)
{
	m_eyePos.y = posY;
}

/**
 * @brief カメラのX位置設定
 *
 * @param[in] posZ  Z位置
 *
 * @return なし
 */
void Camera::SetEyePosZ(const float& posZ)
{
	m_eyePos.z = posZ;
}

/**
 * @brief カメラのターゲット設定
 *
 * @param[in] targetPos       ターゲットの位置
 * @param[in] rotate		  ターゲットの角度
 * @param[in] targetVelocity  ターゲットの速度
 *
 * @return なし
 */
void Camera::SetTartet(const DirectX::SimpleMath::Vector3& targetPos, const DirectX::SimpleMath::Quaternion& rotate,
	const DirectX::SimpleMath::Vector3& targetVelocity)
{
	m_targetPos = &targetPos;
	m_targetRotate = &rotate; // ターゲットの回転も設定
	m_targetVelocity = &targetVelocity;
}


/**
 * @brief カメラのターゲットとの距離
 *
 * @param[in] distance  距離
 *
 * @return なし
 */
void Camera::SetDistance(const DirectX::SimpleMath::Vector3& distance)
{
	m_distance = distance;
}

/**
 * @brief ビュー行列取得
 *
 * @param[in] なし
 *
 * @return ビュー行列
 */
const DirectX::SimpleMath::Matrix& Camera::GetView() const
{
    return m_view;
}
