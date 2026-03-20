/**
 * @file   Camera.h
 *
 * @brief  カメラに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/23
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================

// クラスの定義 ===============================================================
/**
  * @brief カメラ
  */
class Camera
{
// クラス定数の宣言 -------------------------------------------------
public:
	//デフォルト距離
	static constexpr DirectX::SimpleMath::Vector3 DEFAULT_DISTANCE = { 0.0f,2.0f,8.0f };
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//コンストラクタ
	Camera(const DirectX::SimpleMath::Vector3& eyePosition);
	//デストラクタ
	~Camera();
//　操作
	//初期化
	void Initialize();
	//更新
	void Update(const float& elapsedTime);
	//終了
	void Finalize();
//　取得・設定
	//カメラ位置設定
	void SetEyePos(const DirectX::SimpleMath::Vector3& position);
	void SetEyePosX(const float& posX);
	void SetEyePosY(const float& posY);
	void SetEyePosZ(const float& posZ);
	//カメラ位置取得
	const DirectX::SimpleMath::Vector3& GetEyePos() const { return m_eyePos; }
	//注視点設定
	void SetTarget(const DirectX::SimpleMath::Vector3& targetPos,const DirectX::SimpleMath::Quaternion& rotate,
		const DirectX::SimpleMath::Vector3& targetVelocity = DirectX::SimpleMath::Vector3::Zero);
	//距離設定
	void SetDistance(const DirectX::SimpleMath::Vector3& distance);
	//ビュー行列取得
	const DirectX::SimpleMath::Matrix& GetView() const;
	//上ベクトル取得
	const DirectX::SimpleMath::Vector3& GetUP() const { return m_up; }
	//ターゲット取得
	DirectX::SimpleMath::Vector3 GetTargetPos() const { return *m_targetPos; }
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
};