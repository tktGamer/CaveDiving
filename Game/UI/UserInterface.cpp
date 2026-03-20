/**
 * @file   UserInterface.cpp
 *
 * @brief  ユーザーインターフェイスに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/02/02
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "UserInterface.h"
#include"../Common/ResourceManager.h"
#include"Game/Shader/ShaderManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
UserInterface::UserInterface()
	:
	m_windowHeight{ 0 },
	m_windowWidth{0},
	m_textureHeight{ 0 },
	m_textureWidth{0},
	m_texture{nullptr},
	m_res{ nullptr },
	m_scale{ DirectX::SimpleMath::Vector2::One },
	m_position{DirectX::SimpleMath::Vector2::Zero},
	m_anchor{ ANCHOR::TOP_LEFT },
	m_renderRatio{1.0f},
	m_renderRatioOffset{ 0.0f }
{
}

/**
 * @brief デストラクタ
 */
UserInterface::~UserInterface()
{
	m_texture = nullptr;
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
void UserInterface::Render()
{
	ShaderManager* shader = ShaderManager::GetInstance();
	DirectX::CommonStates* states = Graphics::GetInstance()->GetCommonStates();
	ID3D11DeviceContext1* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
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
	UIShader::UICB cbuff;
	//	ウィンドウサイズ
	cbuff.windowSize = DirectX::SimpleMath::Vector2(static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight));
	cbuff.AlphaData = m_renderRatio - m_renderRatioOffset; 
	cbuff.dammy = 0.0f; //	未使用


	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	//context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::ShaderType::UI), 0, NULL, &cbuff, 0, 0);
	shader->StartShader(ShaderManager::ShaderType::UI);


	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	//	半透明描画指定
	ID3D11BlendState* blendstate = states->NonPremultiplied();
	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(states->DepthDefault(), 0);
	//	カリングは左周り
	context->RSSetState(states->CullNone());
	//	ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, m_texture);
	//	インプットレイアウトの登録
	context->IASetInputLayout(shader->GetInputLayout(ShaderManager::ShaderType::UI));

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
void UserInterface::Finalize()
{
}

/**
 * @brief 生成処理
 *
 * @param[in] path　　  ファイルパス
 * @param[in] position　座標
 * @param[in] scale　　 拡大率
 * @param[in] anchor    アンカー位置
 *
 * @return なし
 */
void UserInterface::Create(const wchar_t* path, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale, const ANCHOR& anchor)
{
	m_position = position;
	m_baseScale = m_scale = scale;
	m_anchor = anchor;

	//画像の設定
	SetTexture(path);
	//	プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());

	//テクスチャサイズを取得
	ResourceManager::GetInstance()->GetTextureSize(path, m_textureWidth, m_textureHeight);
}

/**
 * @brief ウィンドウサイズの設定
 *
 * @param[in] width   幅
 * @param[in] height　高さ
 *
 * @return なし
 */
void UserInterface::SetWindowSize(const int& width, const int& height)
{
	m_windowWidth = width;
	m_windowHeight = height;
}

/**
 * @brief 拡大率の設定
 *
 * @param[in] scale  拡大率
 *
 * @return なし
 */
void UserInterface::SetScale(const DirectX::SimpleMath::Vector2& scale)
{
	m_scale = scale;
}

/**
 * @brief 座標の設定
 *
 * @param[in] position 描画座標
 *
 * @return なし
 */
void UserInterface::SetPosition(const DirectX::SimpleMath::Vector2& position)
{
	m_position = position;
}


/**
 * @brief アンカーの設定
 *
 * @param[in] anchor　アンカー位置 
 *
 * @return なし
 */
void UserInterface::SetAnchor(const ANCHOR& anchor)
{
	m_anchor = anchor;
}

/**
 * @brief 描画比率の設定
 *
 * @param[in] ratio　比率
 *
 * @return なし
 */
void UserInterface::SetRenderRatio(const float& ratio)
{
	m_renderRatio = ratio;
}

/**
 * @brief 描画オフセットの設定
 *
 * @param[in] offset　オフセット
 *
 * @return なし
 */
void UserInterface::SetRenderRatioOffset(const float& offset)
{
	m_renderRatioOffset = offset;
}

/**
 * @brief テクスチャの設定
 *
 * @param[in] path　テクスチャのパス
 *
 * @return なし
 */
void UserInterface::SetTexture(const wchar_t* path)
{
	m_texture = ResourceManager::GetInstance()->RequestTexture(path);
}

/**
 * @brief テクスチャの設定
 *
 * @param[in] texture 　テクスチャのポインタ
 *
 * @return なし
 */
void UserInterface::SetTexture(ID3D11ShaderResourceView** texture)
{
	m_texture =texture;
}