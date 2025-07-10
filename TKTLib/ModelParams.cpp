/**
 * @file   ModelParams.cpp
 *
 * @brief  モデル描画に必要なパラメータに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ModelParams.h"
namespace TKTLib
{

	// メンバ関数の定義 ===========================================================
	/**
	 * @brief コンストラクタ
	 *
	 * @param[in] なし
	 */
	ModelParams::ModelParams()
		: m_model{ nullptr }
		, m_position{ 0.0f,0.0f,0.0f }
		, m_rotation{ 0.0f,0.0f,0.0f }
		, m_scale{ 1.0f,1.0f,1.0f }
	{

	}
	/**
	 * @brief コピーコンストラクタ
	 *
	 * @param[in] modelParams コピー元のモデルパラメータ
	 */
	ModelParams::ModelParams(ModelParams& modelParams)
		: m_model{ modelParams.m_model }
		, m_position{ modelParams.m_position }
		, m_rotation{ modelParams.m_rotation }
		, m_scale{ modelParams.m_scale }
	{
	}
	/**
	 * @brief コンストラクタ
	 *
	 * @param[in] model モデルデータ
	 * @param[in] position モデルの位置
	 * @param[in] rotation モデルの回転
	 * @param[in] scale モデルの拡大率
	 */
	ModelParams::ModelParams(DirectX::Model* model, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale)
		: m_model{ model }
		, m_position{ position }
		, m_rotation{ rotation }
		, m_scale{ scale }
	{
	}



	/**
	 * @brief デストラクタ
	 */
	ModelParams::~ModelParams()
	{

	}

	/**
	 * @brief world行列を取得する
	 *
	 * @param[in] なし
	 *
	 * @return world行列
	 */
	DirectX::SimpleMath::Matrix ModelParams::GetWorldMatrix()
	{
		//平行移動行列を作成する
		DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
		//Y軸の回転行列を作成する
		DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(m_rotation.y);
		//X軸の回転行列を作成する
		DirectX::SimpleMath::Matrix rotX = DirectX::SimpleMath::Matrix::CreateRotationX(m_rotation.x);
		//Z軸の回転行列を作成する
		DirectX::SimpleMath::Matrix rotZ = DirectX::SimpleMath::Matrix::CreateRotationZ(m_rotation.z);
		//拡大率行列を作成する
		DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
		return scale * rotY * rotX * rotZ * tras;
	}

	/**
	 * @brief モデルパラメータの設定
	 *
	 * @param[in] modelParams モデルパラメータ
	 *
	 * @return なし
	 */
	void ModelParams::SetModelParams(ModelParams& modelParams)
	{
		m_model = modelParams.m_model;
		m_position = modelParams.m_position;
		m_rotation = modelParams.m_rotation;
		m_scale = modelParams.m_scale;
	}



	/**
	 * @brief モデルパラメータ・モデルの設定
	 *
	 * @param[in] model モデルデータ
	 *
	 * @return なし
	 */
	void ModelParams::SetModelParams(const DirectX::Model* model)
	{
		m_model = const_cast<DirectX::Model*>(model);
	}

	/**
	 * @brief モデルパラメータの設定
	 *
	 * @param[in] position モデルの位置
	 * @param[in] rotation モデルの回転
	 * @param[in] scale モデルの拡大率
	 *
	 * @return なし
	 */
	void ModelParams::SetModelParams(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& rotation, const DirectX::SimpleMath::Vector3& scale)
	{
		m_position = position;
		m_rotation = rotation;
		m_scale = scale;
	}

	/**
	 * @brief モデルパラメータ・座標の設定
	 *
	 * @param[in] position モデルの位置
	 *
	 * @return なし
	 */
	void ModelParams::SetModelParamsP(const DirectX::SimpleMath::Vector3& position)
	{
		m_position = position;
	}

	/**
	 * @brief モデルパラメータ・回転の設定
	 *
	 * @param[in] rotation モデルの回転
	 *
	 * @return なし
	 */
	void ModelParams::SetModelParamsR(const DirectX::SimpleMath::Vector3& rotation)
	{
		m_rotation = rotation;
	}

	/**
	 * @brief モデルパラメータ・拡大率の設定
	 *
	 * @param[in] scale モデルの拡大率
	 *
	 * @return なし
	 */
	void ModelParams::SetModelParamsS(const DirectX::SimpleMath::Vector3& scale)
	{
		m_scale = scale;
	}

	/**
	 * @brief モデルデータの取得
	 *
	 * @param[in] なし
	 *
	 * @return モデルデータ
	 */
	DirectX::Model* ModelParams::GetModel()
	{
		return m_model;
	}


	/**
	 * @brief モデルの位置を取得する
	 *
	 * @param[in] なし
	 *
	 * @return モデルの位置
	 */
	DirectX::SimpleMath::Vector3& ModelParams::GetPosition() 
	{
		return m_position;
	}

	/**
	 * @brief モデルの回転を取得する
	 *
	 * @param[in] なし
	 *
	 * @return モデルの回転
	 */
	DirectX::SimpleMath::Vector3& ModelParams::GetRotation() 
	{
		return m_rotation;
	}

	/**
	 * @brief モデルの拡大率を取得する
	 *
	 * @param[in] なし
	 *
	 * @return モデルの拡大率
	 */
	DirectX::SimpleMath::Vector3& ModelParams::GetScale()
	{
		return m_scale;
	}
	DirectX::SimpleMath::Quaternion& ModelParams::GetQuaternion()
	{
		return m_quaternion;
	}
}