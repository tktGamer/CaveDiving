/**
 * @file   RenderPipeLine.cpp
 *
 * @brief  描画に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/03/22
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "RenderPipeLine.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
RenderPipeLine::RenderPipeLine()
    :
	m_renderObjects{},
	m_bloom{ std::make_unique<Bloom>() }
{
	m_bloom->Initialize();

    auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();

    //レンダーテクスチャの作成
    m_offScreenRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R8G8B8A8_UNORM);//画像の保存形式の指定
    m_offScreenRT->SetDevice(device);
    m_bloomRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R8G8B8A8_UNORM);//画像の保存形式の指定
    m_bloomRT->SetDevice(device);
    //デュアルポストプロセスの作成
    m_dualPostProcess = std::make_unique<DirectX::DualPostProcess>(device);

	ReSize();
}

/**
 * @brief デストラクタ
 */
RenderPipeLine::~RenderPipeLine()
{
}

/**
 * @brief 追加
 *
 * @param[in] なし
 *
 * @return なし
 */
void RenderPipeLine::Register(const RenderLayer& layer, GameObject* object)
{
	//レイヤーごとにオブジェクトを管理するマップに追加
	m_renderObjects[layer].push_back(object);
}

/**
 * @brief　削除
 *
 * @param[in] なし
 *
 * @return なし
 */
void RenderPipeLine::UnRegister(GameObject* object)
{
	//オブジェクトを管理するマップから削除
    for (auto& pair : m_renderObjects)
    {
        auto& objects = pair.second;

        objects.erase(
            std::remove(objects.begin(), objects.end(), object),
            objects.end()
        );
    }
}

/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void RenderPipeLine::Render()
{
    //通常描画
    NormalPass();
    //ブルーム描画
    BloomPass();
	//合成描画
	BlendPass();
}

void RenderPipeLine::ReSize()
{
	m_bloom->Initialize();
	//新しい画面サイズを設定
    RECT rect = Graphics::GetInstance()->GetDeviceResources()->GetOutputSize();
    m_offScreenRT->SetWindow(rect);
    rect = Graphics::GetInstance()->GetDeviceResources()->GetOutputSize();
    m_bloomRT->SetWindow(rect);

    //レンダーテクスチャの作成
    //画面サイズを半分にする
    rect.right /= static_cast<LONG>(DOWNSAMPLE);
    rect.bottom /= static_cast<LONG>(DOWNSAMPLE);
}


/**
 * @brief 通常描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void RenderPipeLine::NormalPass()
{
	ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//設定情報を取得
	auto depthStencil = Graphics::GetInstance()->GetDeviceResources()->GetDepthStencilView();
	auto offScreenRTV = m_offScreenRT->GetRenderTargetView();

	// =========================
    //  通常描画（全部）
    // =========================
	context->ClearRenderTargetView(offScreenRTV, DirectX::Colors::Black);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH, CLEAR_DEPTH, 0);
	context->OMSetRenderTargets(1, &offScreenRTV, depthStencil);

   //レイヤーごとにオブジェクトを管理するマップをループ
    for (const auto& pair : m_renderObjects)
    {
        //オブジェクトのリストを取得
        const std::vector<GameObject*>& objects = pair.second;
        //オブジェクトのリストをループして描画
        for (GameObject* object : objects)
        {
            object->Draw();
        }
	}
}
/**
 * @brief ブルーム描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void RenderPipeLine::BloomPass()
{
	//ブルーム描画用のオブジェクトリストを作成
    std::list<GameObject*> bloomObject;
	//レイヤーごとにオブジェクトを管理するマップをループ
    for (const auto& pair : m_renderObjects)
    {
        //オブジェクトのリストを取得
        const std::vector<GameObject*>& objects = pair.second;
        //オブジェクトのリストをループしてブルーム描画するオブジェクトを追加
        for (GameObject* object : objects)
        {
            if (object->IsBloom())
            {
                bloomObject.push_back(object);
            }
        }
    }

	ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//設定情報を取得
	auto depthStencil = Graphics::GetInstance()->GetDeviceResources()->GetDepthStencilView();
	// =========================
    // Bloom用描画
    // =========================
	auto bloomRTV = m_bloomRT->GetRenderTargetView();
	auto bloomSRV = m_bloomRT->GetShaderResourceView();
    context->ClearRenderTargetView(bloomRTV, DirectX::Colors::Black);
    context->OMSetRenderTargets(1, &bloomRTV, depthStencil);
	m_bloom->ExecuteBloom(bloomObject,m_bloomRT);
}

/**
 * @brief 合成描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void RenderPipeLine::BlendPass()
{
	ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//設定情報を取得
	auto renderTarget = Graphics::GetInstance()->GetDeviceResources()->GetRenderTargetView();
	auto depthStencil = Graphics::GetInstance()->GetDeviceResources()->GetDepthStencilView();
	auto offScreenRTV = m_offScreenRT->GetRenderTargetView();
	auto offScreenSRV = m_offScreenRT->GetShaderResourceView();
	// 画面のサイズを取得
	auto vp = Graphics::GetInstance()->GetDeviceResources()->GetScreenViewport();
	context->RSSetViewports(1, &vp);
	//レンダーターゲットをクリアしてセット
	context->ClearRenderTargetView(renderTarget, DirectX::Colors::Black);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);
	//合成用のシェーダーにテクスチャをセット
	m_dualPostProcess->SetEffect(DirectX::DualPostProcess::BloomCombine);
	m_dualPostProcess->SetBloomCombineParameters(BLOOM_COMBINE_INTENSITY, BLOOM_BASE_INTENSITY, BLOOM_SATURATION, BLOOM_BASE_SATURATION);
	//SRVをセット
	m_dualPostProcess->SetSourceTexture(offScreenSRV);   // 全体
	m_dualPostProcess->SetSourceTexture2(m_bloomRT->GetShaderResourceView()); // 光だけ
	//合成描画
	m_dualPostProcess->Process(context);
	//描画後にSRVを解放
	ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
	context->PSSetShaderResources(0, 1, nullSRV);
}
