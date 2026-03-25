/**
 * @file   Bloom.cpp
 *
 * @brief  DirectXのBloom機能に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/24
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Bloom.h"
#include <Game/Object/GameObject.h>
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Bloom::Bloom()
{
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//レンダーテクスチャの作成
	m_bloomRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R8G8B8A8_UNORM);
	m_bloomRT->SetDevice(device);
	//ベーシックエフェクト作成
	m_basicPostProcess = std::make_unique<DirectX::BasicPostProcess>(device);
	//ブラーの作成
	m_blur1RT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R8G8B8A8_UNORM);
	m_blur1RT->SetDevice(device);

	m_blur2RT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R8G8B8A8_UNORM);
	m_blur2RT->SetDevice(device);
	//デュアルポストプロセスの作成
	m_dualPostProcess = std::make_unique<DirectX::DualPostProcess>(device);

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
	// 画面のサイズを取得
	RECT rect = Graphics::GetInstance()->GetDeviceResources()->GetOutputSize();
	//画面サイズを設定
	m_bloomRT->SetWindow(rect);
	//レンダーテクスチャの作成
	//画面サイズを半分にする
	rect.right /= static_cast<LONG>(BLOOM_DOWNSAMPLE);
	rect.bottom /= static_cast<LONG>(BLOOM_DOWNSAMPLE);
	m_blur1RT->SetWindow(rect);
	m_blur2RT->SetWindow(rect);

}

/**
 * @brief ブルーム処理
 *
 * @param[in] objects  ブルーム対象のオブジェクトリスト
 * @param[in] bloomRT  最終的なブルーム結果を書き込むレンダーテクスチャ
 *
 * @return なし
 */
void Bloom::ExecuteBloom(std::list<GameObject*> objects, std::unique_ptr<DX::RenderTexture>& bloomRT)
{

	ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//設定情報を取得
	auto depthStencil = Graphics::GetInstance()->GetDeviceResources()->GetDepthStencilView();
	// 画面のサイズを取得
	RECT rect = Graphics::GetInstance()->GetDeviceResources()->GetOutputSize();

	// =========================
	// Bloom用描画
	// =========================
	auto bloomRTV = m_bloomRT->GetRenderTargetView();
	auto bloomSRV = m_bloomRT->GetShaderResourceView();
	//レンダーターゲットをクリア
	context->ClearRenderTargetView(bloomRTV, DirectX::Colors::Black);
	//出力先をbloomRTに切り替え
	context->OMSetRenderTargets(1, &bloomRTV, depthStencil);
	//ブルーム対象のオブジェクトを描画
	for (auto object : objects)
	{
		object->Draw();
	}


	//ビューポートを半分のサイズに
	D3D11_VIEWPORT vp_blur = { 0.0f,0.0f,rect.right / BLOOM_DOWNSAMPLE,rect.bottom / BLOOM_DOWNSAMPLE,0.0f,1.0f };
	context->RSSetViewports(1, &vp_blur);
	//ブラー用レンダーテクスチャ取得
	auto blur1RTV = m_blur1RT->GetRenderTargetView();
	auto blur1SRV = m_blur1RT->GetShaderResourceView();

	auto blur2RTV = m_blur2RT->GetRenderTargetView();
	auto blur2SRV = m_blur2RT->GetShaderResourceView();

	// =========================
    // 明るい部分を抽出
    // =========================
	//bloomRTからblur1RTに書き込む
	context->OMSetRenderTargets(1, &blur1RTV, nullptr);

	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::BloomExtract);
	//閾値設定（抽出する最低値）
	m_basicPostProcess->SetBloomExtractParameter(BLOOM_EXTRACT_THRESHOLD);
	m_basicPostProcess->SetSourceTexture(bloomSRV);
	m_basicPostProcess->Process(context);
	//バインド解除
	ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
	context->PSSetShaderResources(0, 1, nullSRV);

	// =========================
	// 横方向ブラー
	// =========================
	//blur1RTからblur2RTに書き込む
	context->OMSetRenderTargets(1, &blur2RTV, nullptr);

	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::BloomBlur);
	//ブルームのパラメータ調整
	m_basicPostProcess->SetBloomBlurParameters(true, BLOOM_BLUR_AMOUNT, BLOOM_INTENSITY);
	m_basicPostProcess->SetSourceTexture(blur1SRV);
	m_basicPostProcess->Process(context);
	//バインド解除
	context->PSSetShaderResources(0, 1, nullSRV);

	// =========================
	// 縦方向ブラー
	// =========================
	//blur2RTからbloomRT(引数)に書き込む
	ID3D11RenderTargetView* bloomRTV_forOM = bloomRT->GetRenderTargetView();
	context->OMSetRenderTargets(1, &bloomRTV_forOM, nullptr);

	m_basicPostProcess->SetEffect(DirectX::BasicPostProcess::BloomBlur);
	m_basicPostProcess->SetBloomBlurParameters(
		false,//縦方向
		BLOOM_BLUR_AMOUNT,	//ぼかしの量
		BLOOM_INTENSITY	//明るさ 1 => 元の画像の明るさ
	);
	m_basicPostProcess->SetSourceTexture(blur2SRV);
	m_basicPostProcess->Process(context);
	//バインド解除
	context->PSSetShaderResources(0, 1, nullSRV);
}