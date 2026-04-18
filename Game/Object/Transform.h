/**
 * @file   Transform.h
 *
 * @brief  オブジェクトの基底クラスに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/25
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief オブジェクトの基底
  */
class Transform
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//座標の設定
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	// モデルの位置の取得
	const DirectX::SimpleMath::Vector3& GetPosition() const { return m_position; }
	//回転の設定
	void SetQuaternion(const DirectX::SimpleMath::Quaternion& q) { m_quaternion = q; }
	// モデルの回転の取得
	const DirectX::SimpleMath::Quaternion& GetQuaternion() const { return m_quaternion; }
	//拡大率の設定
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	// モデルの拡大率の取得
	const DirectX::SimpleMath::Vector3& GetScale() const { return m_scale; }
// コンストラクタ/デストラクタ
	// コンストラクタ
	Transform(
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity,
		const DirectX::SimpleMath::Vector3& initialScale = DirectX::SimpleMath::Vector3::One);
	// デストラクタ
	virtual ~Transform();
// 操作
	//ローカル行列取得
	const DirectX::SimpleMath::Matrix GetLocalMatrix() const;

//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	// モデルの位置
	DirectX::SimpleMath::Vector3 m_position;
	// モデルの回転
	DirectX::SimpleMath::Quaternion m_quaternion;
	// モデルの拡大率
	DirectX::SimpleMath::Vector3 m_scale;

};
