#pragma once
// ヘッダファイルの読み込み ===================================================

class Camera
{

	//カメラのタイプ
	enum class Type
	{
		Type_A,	//プレイヤーを追尾するカメラ
		Type_B	//プレイヤーの周りをまわるカメラ
	};

private:

	//現在のカメラタイプ
	Type m_type;



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
	//ターゲットからの距離
	DirectX::SimpleMath::Vector3 m_distance;
public:
	Camera();

	~Camera();

	void Initialize(DirectX::SimpleMath::Vector3 position);

	void Update(float elapsedTime);


	void Finalize();


	void SetEyePos(DirectX::SimpleMath::Vector3 position);
	void SetEyePosX(float posX);
	void SetEyePosY(float posY);
	void SetEyePosZ(float posZ);
	void SetTartet(const DirectX::SimpleMath::Vector3& targetPos,const DirectX::SimpleMath::Quaternion& rotate);
	void SetDistance(DirectX::SimpleMath::Vector3 distance);
	DirectX::SimpleMath::Vector3 GetEyePos() { return m_eyePos; }
	DirectX::SimpleMath::Matrix GetView();

	DirectX::SimpleMath::Vector3 GetTargetPos() const { return *m_targetPos; }
};

