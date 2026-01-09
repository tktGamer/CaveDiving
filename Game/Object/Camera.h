/**
 * @file   Camera.h
 *
 * @brief  カメラに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/08
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================

class Camera
{

// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:

	//上ベクトル
	DirectX::SimpleMath::Vector3 m_up;
	//カメラの位置
	DirectX::SimpleMath::Vector3 m_eyePos;
	//ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	//ターゲットの位置
	const DirectX::SimpleMath::Vector3* m_targetPos;
	//ターゲットの回転
	const DirectX::SimpleMath::Quaternion* m_targetRotate;
	//ターゲットの速度
	const DirectX::SimpleMath::Vector3* m_targetVelocity;
	//ターゲットからの距離
	DirectX::SimpleMath::Vector3 m_distance;
public:
	Camera();

	~Camera();

	void Initialize(DirectX::SimpleMath::Vector3 position);

	void Update(float elapsedTime);


	void Finalize();


	void SetEyePos(const DirectX::SimpleMath::Vector3& position);
	void SetEyePosX(float posX);
	void SetEyePosY(float posY);
	void SetEyePosZ(float posZ);
	void SetTartet(const DirectX::SimpleMath::Vector3& targetPos,const DirectX::SimpleMath::Quaternion& rotate,const DirectX::SimpleMath::Vector3& targetVelocity = DirectX::SimpleMath::Vector3::Zero);
	void SetDistance(DirectX::SimpleMath::Vector3 distance);
	const DirectX::SimpleMath::Vector3& GetEyePos() const { return m_eyePos; }
	const DirectX::SimpleMath::Matrix& GetView() const;

	DirectX::SimpleMath::Vector3 GetTargetPos() const { return *m_targetPos; }
	const DirectX::SimpleMath::Vector3& GetUP() const { return m_up; }
};

