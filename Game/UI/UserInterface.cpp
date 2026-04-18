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
UserInterface::UserInterface(const GameObject2D* parent, const DirectX::SimpleMath::Vector2& initialPosition, const DirectX::SimpleMath::Vector2& initialScale)
	:
	GameObject2D{Tag::ObjectType::UI,parent,initialPosition,initialScale}
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
	ShaderManager* shader = ShaderManager::GetInstance();
	DirectX::CommonStates* states = Graphics::GetInstance()->GetCommonStates();
	ID3D11DeviceContext1* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//	頂点情報
	//	Position.xy	:座標
	//	Position.z	:
	//	Color.xy　	:
	//	Color.zw	:
	//	Tex.xy		:サイズ
	DirectX::VertexPositionColorTexture vertex[1] = {
		DirectX::VertexPositionColorTexture(
			 DirectX::SimpleMath::Vector3(GetWorldPosition().x,GetWorldPosition().y, static_cast<float>(GetAnchor()))
			,DirectX::SimpleMath::Vector4(GetPosition().x, GetPosition().y, static_cast<float>(GetTextureSize().x), static_cast<float>(GetTextureSize().y))
			,GetWorldScale())
	};

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	UIShader::UICB cbuff;
	//	ウィンドウサイズ
	cbuff.windowSize = GetBaseWindowSize();
	cbuff.AlphaData = GetRenderRatio() - GetRenderRatioOffset();
	cbuff.dammy = 0.0f; //	未使用


	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
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
	context->PSSetShaderResources(0, 1, GetTexture().GetAddressOf());
	//	インプットレイアウトの登録
	context->IASetInputLayout(shader->GetInputLayout(ShaderManager::ShaderType::UI));

	//	板ポリゴンを描画
	GetBatch().Begin();
	GetBatch().Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	GetBatch().End();

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
