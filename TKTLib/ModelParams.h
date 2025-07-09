/**
 * @file   ModelParams.h
 *
 * @brief  モデル描画に必要なパラメータに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付 2025 5/14
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================

// クラスの宣言 ===============================================================

namespace TKTLib
{


	// クラスの定義 ===============================================================
	/**
	  * @brief ModelParams
	  */
	class ModelParams
	{
		// クラス定数の宣言 -------------------------------------------------
	public:


		// データメンバの宣言 -----------------------------------------------
	private:
		DirectX::Model* m_model;	///< モデルデータ
		DirectX::SimpleMath::Vector3 m_position = { 0.0f,0.0f,0.0f };	///< モデルの位置
		DirectX::SimpleMath::Vector3 m_rotation = { 0.0f,0.0f,0.0f };	///< モデルの回転
		DirectX::SimpleMath::Vector3 m_scale = { 1.0f,1.0f,1.0f };	///< モデルの拡大率

		// モデルのクォータニオン回転
		DirectX::SimpleMath::Quaternion m_quaternion = { 0.0f,0.0f,0.0f,1.0f };
		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
	public:
		// コンストラクタ
		ModelParams();
		// コピーコンストラクタ
		ModelParams(ModelParams& modelParams);
		ModelParams(DirectX::Model* model, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale);
		

		// デストラクタ
		~ModelParams();


		// 操作
	public:
		// ワールド行列を取得する
		DirectX::SimpleMath::Matrix GetWorldMatrix();

		//　取得・設定
	public:
		// モデルパラメータの設定
		void SetModelParams(ModelParams& modelParams);
		// モデルパラメータ・モデルの設定
		void SetModelParams(const DirectX::Model* model);
		// モデルパラメータの設定
		void SetModelParams(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& rotation, const DirectX::SimpleMath::Vector3& scale);
		// モデルパラメータ・座標の設定
		void SetModelParamsP(const DirectX::SimpleMath::Vector3& position);
		// モデルパラメータ・回転の設定
		void SetModelParamsR(const DirectX::SimpleMath::Vector3& rotation);
		// モデルパラメータ・拡大率の設定
		void SetModelParamsS(const DirectX::SimpleMath::Vector3& scale);

		// モデルデータの取得
		DirectX::Model* GetModel();
		// モデルの位置の取得
		DirectX::SimpleMath::Vector3 GetPosition() const;
		// モデルの回転の取得
		DirectX::SimpleMath::Vector3 GetRotation() const;
		// モデルの拡大率の取得
		DirectX::SimpleMath::Vector3 GetScale() const;
		// モデルのクォータニオン回転の取得
		DirectX::SimpleMath::Quaternion GetQuaternion() const;
		//　内部操作
	private:

	};

}