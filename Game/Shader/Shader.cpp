/**
 * @file   Shader.cpp
 *
 * @brief  シェーダーの基底に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/09
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Shader.h"
#include "Game/Common/ResourceManager.h"
// クラス定数の定義 ===========================================================





// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Shader::Shader()
{
}

/**
 * @brief デストラクタ
 */
Shader::~Shader()
{
}







/**
 * @brief シェーダーの開始
 *
 * @param[in]　なし
 *
 * @return なし
 */
void Shader::StartShader()
{

	ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_constantBuffer.Get()};

	// コンスタントバッファを設定
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	// シェーダーを設定
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);

}


/**
 * @brief シェーダーの終了 (通常状態は頂点・ピクセル・ジオメトリのみ)
 *
 * @param[in]　customState 独自のシェーダー設定
 *
 * @return なし
 */
void Shader::EndShader(const std::function<void()>& customState)
{
	//独自の設定があるなら
	if (customState)
	{
		customState;
		return;
	}

	ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// シェーダーを無効化
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	// コンスタントバッファを無効化
	ID3D11Buffer* nullBuffer = nullptr;
	context->VSSetConstantBuffers(0, 1, &nullBuffer);
	context->PSSetConstantBuffers(0, 1, &nullBuffer);
	context->PSSetConstantBuffers(0, 1, &nullBuffer);

}


/**
 * @brief 頂点・ジオメトリ・ピクセルシェーダーを読み込む
 *
 * @pathExample   L"Resources/Shaders/ModelShader/ModelVS.cso"
 * @param[in] vsPath  頂点シェーダーのパス
 * @param[in] psPath　ピクセルシェーダーのパス
 * @param[in] gsPath　ジオメトリシェーダーのパス
 *
 * @return 頂点シェーダーへのポインタ
 */
void Shader::CreateShader(const wchar_t* vsPath, const wchar_t* psPath, const wchar_t* gsPath)
{
	// シェーダーのバイナリデータを読み込む
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	BinaryFile VSData = resourceManager->RequestBinaryFile(vsPath);
	BinaryFile PSData = resourceManager->RequestBinaryFile(psPath);
	BinaryFile GSData = resourceManager->RequestBinaryFile(gsPath);
	// シェーダーを作成する
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
		VSData.GetData(), VSData.GetSize(), nullptr, m_vertexShader.ReleaseAndGetAddressOf());
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
		PSData.GetData(), PSData.GetSize(), nullptr, m_pixelShader.ReleaseAndGetAddressOf());
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
		GSData.GetData(), GSData.GetSize(), nullptr, m_geometryShader.ReleaseAndGetAddressOf());

}


/**
 * @brief インプットレイアウトの作成
 *
 * @param[in]　layout　頂点データ
 * @param[in]　vsPath　頂点シェーダーのパス
 *
 * @return なし
 */
void Shader::CreateInputLayput(const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, const wchar_t* vsPath)
{
	BinaryFile VSData = ResourceManager::GetInstance()->RequestBinaryFile(vsPath);

	//インプットレイアウトの作成
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
		&layout[0],
		static_cast<UINT>(layout.size()),
		VSData.GetData(),
		VSData.GetSize(),
		m_inputLayout.GetAddressOf());

}


/**
 * @brief インプットレイアウトの取得
 *
 * @param[in]　なし
 *
 * @return インプットレイアウトのポインタ
 */
ID3D11InputLayout* Shader::GetInputLayout()
{
	return m_inputLayout.Get();
}


/**
 * @brief コンスタントバッファの取得
 *
 * @param[in]　なし
 *
 * @return コンスタントバッファのポインタ
 */
ID3D11Buffer* Shader::GetConstantBuffer()
{
	return m_constantBuffer.Get();
}

/**
 * @brief 頂点シェーダーを取得する
 *
 * @param[in] なし
 *
 * @return 頂点シェーダーへのポインタ
 */
ID3D11VertexShader* Shader::GetVertexShader()
{
	return m_vertexShader.Get();
}


/**
 * @brief ピクセルシェーダーを取得する
 *
 * @param[in] なし
 *
 * @return ピクセルシェーダーへのポインタ
 */
ID3D11PixelShader* Shader::GetPixelShader()
{
	return m_pixelShader.Get();
}


/**
 * @brief ジオメトリシェーダーを取得する
 *
 * @param[in] なし
 *
 * @return ジオメトリシェーダーへのポインタ
 */
ID3D11GeometryShader* Shader::GetGeometryShader()
{
	return m_geometryShader.Get();
}


