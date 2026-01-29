/**
 * @file   WallShader.cpp
 *
 * @brief  壁モデル用シェーダーに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/29
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "WallShader.h"
// クラス定数の定義 ===========================================================

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pathes　シェーダーのパス
 */
WallShader::WallShader(const ShaderPath& pathes)
	:
	ModelShader{pathes}
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

/**
 * @brief シェーダーの開始
 *
 * @param[in]　cb  カメラとプレイヤーのデータ
 *
 * @return なし
 */
void WallShader::StartShader(const CameraToPlayerCB& cb)
{
	//追加処理-----
	ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//cbから変換
	context->UpdateSubresource(m_cameraToPlayerCB.Get(), 0, NULL, &cb, 0, 0);
	//ピクセルシェーダーにカメラとプレイヤーの情報渡す
	ID3D11Buffer* lb[1] = { m_cameraToPlayerCB.Get() };
	context->PSSetConstantBuffers(2, 1, lb);
	//-------------
	//元の処理を始める
	ModelShader::StartShader();
}

