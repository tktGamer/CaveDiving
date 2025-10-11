//--------------------------------------------------------------------------------------
// File: ParticleControl.cpp
//
// パーティクルクラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "ParticleControl.h"

#include"Game/Common/ResourceManager.h"
#include"Game/Shader.h"
#include"Game/Message/Messenger.h"
/// <summary>
/// コンストラクタ
/// </summary>
ParticleControl::ParticleControl(const std::string& texturePath)
	: m_timerAndPos{}
{
	m_texture = ResourceManager::GetInstance()->RequestTexture(texturePath);
	//	プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());

}

/**
 * @brief デストラクタ
 */
ParticleControl::~ParticleControl()
{
}




/// <summary>
/// ビルボード作成関数
/// </summary>
/// <param name="target">カメラターゲット（注視点）</param>
/// <param name="eye">カメラアイ（カメラ座標）</param>
/// <param name="up">上向きベクトル（基本はYのみ１のベクトル）</param>
void ParticleControl::CreateBillboard(DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up)
{
	m_billboard =
		DirectX::SimpleMath::Matrix::CreateBillboard(target, eye - target, up);

	//	回転情報を設定する
	DirectX::SimpleMath::Matrix rot = DirectX::SimpleMath::Matrix::Identity;
	//	180度逆を向いているので、補正するための情報を入れる
	rot._11 = -1;
	rot._33 = -1;

	m_cameraPosition = eye;
	m_cameraTarget = target;
	m_billboard = rot * m_billboard;
}

const DirectX::SimpleMath::Vector3& ParticleControl::GetCameraPosition() const
{
	return m_cameraPosition;
}

const DirectX::SimpleMath::Vector3& ParticleControl::GetCameraTarget() const
{
	return m_cameraTarget;
}

const DirectX::SimpleMath::Matrix& ParticleControl::GetBillBoard() const
{
	return m_billboard;
}

ID3D11ShaderResourceView** ParticleControl::GetTexture() const
{
	return m_texture;
}
