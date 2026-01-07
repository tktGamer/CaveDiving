/**
 * @file   Bloom.cpp
 *
 * @brief  DirectXのBloom機能に関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Bloom.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Bloom::Bloom()
{

}



/**
 * @brief デストラクタ
 */
Bloom::~Bloom()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Bloom::Initialize()
{
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//レンダーテクスチャの作成
	m_offScreenRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R8G8B8A8_UNORM);//画像の保存形式の指定
	m_offScreenRT->SetDevice(device);
	RECT rect = Graphics::GetInstance()->GetDeviceResources()->GetOutputSize();
	m_offScreenRT->SetWindow(rect);


	//ベーシックエフェクト作成
	m_basicPostProcess = std::make_unique<DirectX::BasicPostProcess>(device);

	//レンダーテクスチャの作成
	//画面サイズを半分にする
	rect.right /= 2.0f;
	rect.bottom /= 2.0f;

	//ブラーの作成
	m_blur1RT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R8G8B8A8_UNORM);
	m_blur1RT->SetDevice(device);
	m_blur1RT->SetWindow(rect);

	m_blur2RT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R8G8B8A8_UNORM);
	m_blur2RT->SetDevice(device);
	m_blur2RT->SetWindow(rect);

	//デュアルポストプロセスの作成
	m_dualPostProcess = std::make_unique<DirectX::DualPostProcess>(device);

}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Bloom::Update()
{

}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Bloom::Draw()
{
	ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//設定情報を取得
	auto renderTarget = Graphics::GetInstance()->GetDeviceResources()->GetRenderTargetView();
	auto depthStencil = Graphics::GetInstance()->GetDeviceResources()->GetDepthStencilView();
	auto offScreenRTV = m_offScreenRT->GetRenderTargetView();
	auto offScreenSRV = m_offScreenRT->GetShaderResourceView();

	// 画面のサイズを取得
	RECT rect = Graphics::GetInstance()->GetDeviceResources()->GetOutputSize();

	//レンダーターゲットを変更----------------
	context->ClearRenderTargetView(offScreenRTV, DirectX::Colors::Black);
	context->ClearDepthStencilView(
		depthStencil,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, //フラグ　　デプスとステンシルのクリア
		1.0f,
		0);
	context->OMSetRenderTargets(1, &offScreenRTV, depthStencil);

	//---------------------------------------------------------------------------//
	//ブラーするオブジェクトの描画
	//---------------------------------------------------------------------------//

	
//	m_stage->Draw();


	//Pass1 offScreenSRVをもとにblur1RTV blur1SRVに明るい部分を抽出する----------------------------------------

	//レンダーターゲットを切り替えると絵の出力先が変わる
	auto blur1RTV = m_blur1RT->GetRenderTargetView();
	auto blur1SRV = m_blur1RT->GetShaderResourceView();

	//切り替え
	context->OMSetRenderTargets(1, &blur1RTV, nullptr);

	D3D11_VIEWPORT vp_blur = { 0.0f,0.0f,rect.right / 2.0f,rect.bottom / 2.0f,0.0f,1.0f };
	context->RSSetViewports(1, &vp_blur);

	//抽出
	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::BloomExtract);
	m_basicPostProcess->SetBloomExtractParameter(0.25f);
	m_basicPostProcess->SetSourceTexture(offScreenSRV);//レンダーターゲットをソースにして作成
	m_basicPostProcess->Process(context);

	ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
	context->PSSetShaderResources(0, 1, nullSRV);

	//----------------------------------------

	//Pass2 blur1SRVをもとにblur2RTV(blur2SRV)に横にぶれた画像を作成する-----------------
	auto blur2RTV = m_blur2RT->GetRenderTargetView();
	auto blur2SRV = m_blur2RT->GetShaderResourceView();
	//切り替え
	context->OMSetRenderTargets(1, &blur2RTV, nullptr);

	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::Effect::BloomBlur);
	m_basicPostProcess->SetBloomBlurParameters
	(
		true,//横のぼかしができる
		4.0f,	//ぼかしの量
		1.0f	//明るさ 1 => 元の画像の明るさ
	);

	m_basicPostProcess->SetSourceTexture(blur1SRV);
	m_basicPostProcess->Process(context);

	context->PSSetShaderResources(0, 1, nullSRV);

	//------------------------------------------------------

	//Pass3 blur2SRVをもとにblur1RTV(blur1SRV)に縦にぶれた画像を作成する-----------------
	//切り替え
	context->OMSetRenderTargets(1, &blur1RTV, nullptr);

	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::Effect::BloomBlur);
	m_basicPostProcess->SetBloomBlurParameters
	(
		false,//横のぼかしができる
		4.0f,	//ぼかしの量
		1.0f	//明るさ 1 => 元の画像の明るさ
	);

	m_basicPostProcess->SetSourceTexture(blur2SRV);
	m_basicPostProcess->Process(context);

	context->PSSetShaderResources(0, 1, nullSRV);

	// -------------------------------------------------------------------------- //
	// レンダーターゲットとビューポートを元に戻す
	// -------------------------------------------------------------------------- //
	//auto renderTarget = Graphics::GetInstance()->GetDeviceResources()->GetRenderTargetView();
	//auto depthStencil = Graphics::GetInstance()->GetDeviceResources()->GetDepthStencilView();


	context->ClearRenderTargetView(renderTarget, DirectX::Colors::Black);
	context->ClearDepthStencilView(depthStencil, /*D3D11_CLEAR_DEPTH |*/ D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);
	//-----------------------------------------------------
	// ビューポートを元に戻す
	//-----------------------------------------------------
	auto const viewport = Graphics::GetInstance()->GetDeviceResources()->GetScreenViewport();
	context->RSSetViewports(1, &viewport);




	//Pass4 offScreenSRVとblur1STVをもとにぼかした画像を作成する-----------------
	m_dualPostProcess->SetEffect(DirectX::DualPostProcess::BloomCombine);
	m_dualPostProcess->SetBloomCombineParameters
	(
		1.25f,//合成される光　明るさ
		1.0f,
		0.0f,//ライト　彩度
		1.0f//白っぽくなる
	);

	m_dualPostProcess->SetSourceTexture(offScreenSRV);
	m_dualPostProcess->SetSourceTexture2(blur1SRV);//追加するもの

	m_dualPostProcess->Process(context);

	context->PSSetShaderResources(0, 1, nullSRV);

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Bloom::Finalize()
{

}
