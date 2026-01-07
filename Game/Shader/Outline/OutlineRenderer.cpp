/**
 * @file   OutlineRenderer.cpp
 *
 * @brief  アウトライン描画に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/01/03
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "OutlineRenderer.h"
#include"Game/Common/Graphics.h"
#include"Game/Shader/ShaderManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief アウトライン描画
 *
 * @param[in] model  モデル
 * @param[in] world　ワールド行列 
 * @param[in] thickness　アウトラインの太さ
 *
 * @return なし
 */
void OutlineRenderer::Draw(const DirectX::Model& model, const DirectX::SimpleMath::Matrix& world, const float& thickness)
{
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();
	ShaderManager* shader = ShaderManager::GetInstance();

	OutlineShader::OutlineCB outline;
	outline.matWorld = world.Transpose();
	outline.matView = view.Transpose();
	outline.matProj = proj.Transpose();
	outline.outlineThickness = thickness;
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::ShaderType::Outline), 0, NULL, &outline, 0, 0);

	// モデル描画（アウトライン専用）
	model.Draw(context, *states, world, view, proj, false, [&]() 
	{
		// カリングを FrontFace にして裏面を描画（アウトライン用）
		context->RSSetState(states->CullCounterClockwise());

		// ブレンド・デプスステート
		context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);
		context->OMSetDepthStencilState(states->DepthDefault(), 0);

		// アウトラインシェーダを設定
		shader->StartShader(ShaderManager::ShaderType::Outline);
		context->IASetInputLayout(shader->GetInputLayout(ShaderManager::ShaderType::Outline));

	});

	shader->EndShader();

}
