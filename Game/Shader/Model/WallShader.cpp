/**
 * @file   WallShader.cpp
 *
 * @brief  壁モデル用シェーダーに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/08
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "WallShader.h"
#include "Game/Common/ResourceManager.h"
#include"Game/Object/Light.h"
// クラス定数の定義 ===========================================================


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pathes
 */
WallShader::WallShader(const ShaderPath& pathes)
	:ModelShader{pathes}
{
	

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WallShader::CameraToPlayerCB);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_cameraToPlayerCB);

}


/**
 * @brief デストラクタ
 */
WallShader::~WallShader()
{
}

void WallShader::StartShader(const CameraToPlayerCB& cb)
{
	ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	context->UpdateSubresource(m_cameraToPlayerCB.Get(), 0, NULL, &cb, 0, 0);
	//ピクセルシェーダーにカメラとプレイヤーの情報渡す
	ID3D11Buffer* lb[1] = { m_cameraToPlayerCB.Get() };
	context->PSSetConstantBuffers(2, 1, lb);
	ModelShader::StartShader();
}

