/**
 * @file   ParticleControl.cpp
 *
 * @brief  パーティクル管理の基底に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/10/22
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ParticleControl.h"

#include"Game/Common/ResourceManager.h"
#include"Game/Shader.h"
#include"Game/Message/Messenger.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] texturePath テクスチャハンドル
 */
ParticleControl::ParticleControl(const std::string& texturePath)
	: m_timerAndPos{}
	, m_vertices{}
{
	m_texture = ResourceManager::GetInstance()->RequestTexture(texturePath);
	//	プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CameraBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_cameraCBuffer);

}

/**
 * @brief デストラクタ
 */
ParticleControl::~ParticleControl()
{
}







/**
 * @brief 頂点があるか
 *
 * @return true  頂点がある
		   false 頂点がない
 */
bool ParticleControl::HasVertex() const
{
	return !m_vertices.empty();
}

/**
 * @brief テクスチャの取得
 *
 * @return テクスチャハンドル
 */
ID3D11ShaderResourceView** ParticleControl::GetTexture() const
{
	return m_texture;
}

/**
 * @brief 頂点追加
 *
 * @param[in] vPCT 頂点情報
 *
 * @return なし
 */
void ParticleControl::AddVertex(const DirectX::VertexPositionColorTexture& vPCT)
{
	m_vertices.push_back(vPCT);
}

/**
 * @brief 頂点消去
 *
 * @return なし
 */
void ParticleControl::ClearVertex()
{
	m_vertices.clear();
}


/**
 * @brief 1つのパーティクルの経過時間
 *
 * @param[in] cameraCB   カメラ情報
 * @param[in] startSlot  スタートスロット
 * @param[in] numBuffer  バッファ数
 *
 * @return なし
 */
void ParticleControl::AddTimerAndPos(const TimerAndPos& timerAnPos)
{
	m_timerAndPos.push_back(timerAnPos);
}

/**
 * @brief カメラの情報をバッファに渡す
 *
 * @param[in] cameraCB   カメラ情報
 * @param[in] startSlot  スタートスロット
 * @param[in] numBuffer  バッファ数
 *
 * @return なし
 */
void ParticleControl::SetCameraBuffer(const CameraBuffer& cameraCB, const UINT& startSlot, const UINT& numBuffer)
{
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//カメラの情報を渡す
	context->UpdateSubresource(m_cameraCBuffer.Get(), 0, NULL, &cameraCB, 0, 0); // b1 に渡す
	ID3D11Buffer* lb[1] = { m_cameraCBuffer.Get() };
	context->GSSetConstantBuffers(startSlot, numBuffer, lb);

}

/**
 * @brief 通常のパーティクルのシェーダー関連の設定
 *
 * @return なし
 */
void ParticleControl::SetShaderState()
{
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = Graphics::GetInstance()->GetCommonStates();

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	半透明描画指定
	ID3D11BlendState* blendstate = states->NonPremultiplied();

	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//	カリングはなし
	context->RSSetState(states->CullNone());

	//テクスチャの登録
	context->PSSetShaderResources(0, 1, GetTexture());

	//	インプットレイアウトの登録
	context->IASetInputLayout(Shader::GetInstance()->GetInputLayout(Shader::ShaderType::Particle));

}

/**
 * @brief 描画バッチ処理
 *
 * @param[in] customDraw カスタム描画関数
 *
 * @return なし
 */
void ParticleControl::DrawBatch(const std::function<void()>& customDraw)
{
	//頂点情報が空なら描画しない
	if (m_vertices.empty()) 
	{
		return;
	}

	//関数が渡されてきたら実行する
	if (customDraw) 
	{
		customDraw();
		return;
	}

	//	板ポリゴンを描画
	m_batch->Begin();
	//	ジオメトリシェーダでPointを受け取ることになっているため、
	//	ここではD3D11_PRIMITIVE_TOPOLOGY_POINTLISTを使う
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());
	m_batch->End();
}

