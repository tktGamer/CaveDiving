/**
 * @file   UserInterface.cpp
 *
 * @brief  ユーザーインターフェイスに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "UserInterface.h"
#include"../Common/ResourceManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
UserInterface::UserInterface()
	:m_graphics{Graphics::GetInstance()}
	, m_pDR(nullptr)
	, m_windowHeight(0)
	, m_windowWidth(0)
	, m_textureHeight(0)
	, m_textureWidth(0)
	, m_texture(nullptr)
	, m_res(nullptr)
	, m_scale(DirectX::SimpleMath::Vector2::One)
	, m_position(DirectX::SimpleMath::Vector2::Zero)
	, m_anchor(ANCHOR::TOP_LEFT)
	, m_renderRatio(1.0f)
	, m_renderRatioOffset(0.0f)

{

}



/**
 * @brief デストラクタ
 */
UserInterface::~UserInterface()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UserInterface::Initialize()
{

}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UserInterface::Update()
{

}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UserInterface::Draw()
{
	Shader* shader = Shader::GetInstance();

	ID3D11DeviceContext1* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	//	頂点情報
	//	Position.xy	:拡縮用スケール
	//	Position.z	:アンカータイプ(0～8)の整数で指定
	//	Color.xy　	:アンカー座標(ピクセル指定:1280 ×720)
	//	Color.zw	:画像サイズ
	//	Tex.xy		:x = 0, y = 0
	DirectX::VertexPositionColorTexture vertex[1] = {
		DirectX::VertexPositionColorTexture(
			 DirectX::SimpleMath::Vector3(m_scale.x, m_scale.y, static_cast<float>(m_anchor))
			,DirectX::SimpleMath::Vector4(m_position.x, m_position.y, static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight))
			,DirectX::SimpleMath::Vector2(0,0))
	};

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	//	ウィンドウサイズ
	cbuff.windowSize = DirectX::SimpleMath::Vector2(static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight));
	cbuff.AlphaData = m_renderRatio - m_renderRatioOffset; 
	cbuff.dammy = 0.0f; //	未使用


	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	//context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);
	context->UpdateSubresource(shader->GetCBuffer(Shader::ShaderType::UI), 0, NULL, &cbuff, 0, 0);
	shader->StartShader(Shader::ShaderType::UI, shader->GetCBuffer(Shader::ShaderType::UI));

	//	シェーダーにバッファを渡す
	//ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	//context->VSSetConstantBuffers(0, 1, cb);
	//context->GSSetConstantBuffers(0, 1, cb);
	//context->PSSetConstantBuffers(0, 1, cb);

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	半透明描画指定
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//	カリングは左周り
	context->RSSetState(m_states->CullNone());

	//	シェーダをセットする
	//context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	//context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	//context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, m_texture);

	//	インプットレイアウトの登録
	//context->IASetInputLayout(m_inputLayout.Get());
	context->IASetInputLayout(shader->GetInputLayout(Shader::UI));

	//	板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//	シェーダの登録を解除しておく
	//context->VSSetShader(nullptr, nullptr, 0);
	//context->GSSetShader(nullptr, nullptr, 0);
	//context->PSSetShader(nullptr, nullptr, 0);
	shader->EndShader();
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UserInterface::Finalize()
{

}

void UserInterface::Create(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor)
{
	m_pDR = m_graphics->GetDeviceResources();
	ID3D11Device1* device = m_graphics->GetDeviceResources()->GetD3DDevice();
	m_position = position;
	m_baseScale = m_scale = scale;
	m_anchor = anchor;

	//	シェーダーの作成
	//CreateShader(shader);

	//	画像の読み込み
	//LoadTexture(path);
	m_texture = ResourceManager::GetInstance()->RequestTexture(path);
	//	プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(m_graphics->GetDeviceResources()->GetD3DDeviceContext());

	m_states = m_graphics->GetCommonStates();

	//画像サイズを取得
	ResourceManager::GetInstance()->GetTextureSize(path, m_textureWidth, m_textureHeight);
	
}

void UserInterface::SetWindowSize(const int& width, const int& height)
{
	m_windowWidth = width;
	m_windowHeight = height;

}

void UserInterface::SetScale(DirectX::SimpleMath::Vector2 scale)
{
	m_scale = scale;
}
void UserInterface::SetPosition(DirectX::SimpleMath::Vector2 position)
{
	m_position = position;
}
void UserInterface::SetAnchor(ANCHOR anchor)
{
	m_anchor = anchor;
}
void UserInterface::SetRenderRatio(float ratio)
{
	m_renderRatio = ratio;
}
void UserInterface::SetRenderRatioOffset(float offset)
{
	m_renderRatioOffset = offset;
}
