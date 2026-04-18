/**
 * @file   Number.cpp
 *
 * @brief  数字UIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/30
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Number.h"
#include"Game/Common/ResourceManager.h"
#include"Game/Shader/ShaderManager.h"
#include"Game/UI/UIManager.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Number::Number(const std::string& texturepath, DirectX::SimpleMath::Vector2 textureSize)
	: 
	m_pNumberTexture{},
	m_textureSize{textureSize},
	m_anchor{UserInterface::ANCHOR::MIDDLE_CENTER},
	m_windowHeight{ 0 },
	m_windowWidth{ 0 },
	m_number{},
	m_position{ DirectX::SimpleMath::Vector2::Zero },
	m_scale{ DirectX::SimpleMath::Vector2::One },
	m_color{},
	m_renderRatio{ 1.0f },
	m_renderRatioOffset{ 0.0f }

{
	m_pNumberTexture = ResourceManager::GetInstance()->RequestTexture(texturepath);
	//	プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());

}

/**
 * @brief デストラクタ
 */
Number::~Number()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Number::Initialize()
{
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Number::Update()
{
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Number::Draw(const int& number, const DirectX::SimpleMath::Vector2& pos, const DirectX::SimpleMath::Vector2& scale, const DirectX::SimpleMath::Vector4& color)
{
	ShaderManager* shader = ShaderManager::GetInstance();

	ID3D11DeviceContext1* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//	頂点情報
	//	Position.xy	:拡縮用スケール
	//	Position.z	:アンカータイプ(0～8)の整数で指定
	//	Color.xy　	:アンカー座標(ピクセル指定:1280 ×720)
	//	Color.zw	:画像サイズ
	//	Tex.xy		:x = 0, y = 0
	DirectX::VertexPositionColorTexture vertex[1] = {
		DirectX::VertexPositionColorTexture(
			 DirectX::SimpleMath::Vector3(scale.x, scale.y, static_cast<float>(m_anchor))
			,DirectX::SimpleMath::Vector4(pos.x , pos.y, 130, 205)
			,m_textureSize)
	};

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Number2DShader::Number2DCB cbuff;
	//	ウィンドウサイズ
	cbuff.windowSize = DirectX::SimpleMath::Vector2(static_cast<float>(UIManager::WINDOW_SIZE_X), static_cast<float>(UIManager::WINDOW_SIZE_Y));
	cbuff.alphaData = m_renderRatio - m_renderRatioOffset;
	cbuff.number = number; 
	cbuff.widthNumber = 10;
	cbuff.heightNumber = 1;
	cbuff.numberColor = color;

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	//context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::ShaderType::Number2D), 0, NULL, &cbuff, 0, 0);
	shader->StartShader(ShaderManager::ShaderType::Number2D);

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { Graphics::GetInstance()->GetCommonStates()->LinearWrap()};
	context->PSSetSamplers(0, 1, sampler);
	//	半透明描画指定
	ID3D11BlendState* blendstate = Graphics::GetInstance()->GetCommonStates()->NonPremultiplied();
	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(Graphics::GetInstance()->GetCommonStates()->DepthDefault(), 0);
	//	カリングは左周り
	context->RSSetState(Graphics::GetInstance()->GetCommonStates()->CullNone());
	//	ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, m_pNumberTexture);
	//	インプットレイアウトの登録
	context->IASetInputLayout(shader->GetInputLayout(ShaderManager::Number2D));

	//	板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//	シェーダの登録を解除しておく
	shader->EndShader();
}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Number::Finalize()
{
}

/**
 * @brief 数字更新
 *
 * @param[in] number　数字  
 * @param[in] pos　   位置
 * @param[in] scale　 大きさ
 * @param[in] color　 色
 *
 * @return なし
 */
void Number::ChangeNumber(const int& number, const DirectX::SimpleMath::Vector2& pos,
	const DirectX::SimpleMath::Vector2& scale, const DirectX::SimpleMath::Vector4& color)
{
	m_number = number;
	m_position = pos;
	m_scale = scale;
	m_color = color;
}