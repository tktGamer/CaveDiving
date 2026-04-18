/**
 * @file   Transform.cpp
 *
 * @brief  トランスフォームに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/04/09
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Transform.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in]  initialPosition  初期座標
 * @param[in]  initialAngle 　　初期角度
 * @param[in]  initialScale 　　初期サイズ
 * 
 */
Transform::Transform(const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Quaternion& initialAngle, const DirectX::SimpleMath::Vector3& initialScale)
	:
	m_position{initialPosition},
	m_quaternion{initialAngle},
	m_scale{initialScale}
{
}

/**
 * @brief デストラクタ
 */
Transform::~Transform()
{
}

/**
 * @brief ローカルマトリックスを取得
 *
 * @param[in] なし
 *
 * @return なし
 */
const DirectX::SimpleMath::Matrix Transform::GetLocalMatrix() const
{
	return TKTLib::GetWorldMatrix(GetPosition(), GetQuaternion(), GetScale());
}
