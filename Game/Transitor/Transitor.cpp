/**
 * @file   Transitor.cpp
 *
 * @brief  トランジスターに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/01/29
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Transitor.h"
#include"Game/Common/ResourceManager.h"
#include"Game/Shader/ShaderManager.h"
#include"Game/Message/Messenger.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] isIn  フェードイン・アウト
 */
Transitor::Transitor(bool isIn)
	:
	m_time{0.0f},
	m_isIn{isIn},
	m_batch{},
	m_vertices{}
{
	//	プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());
}


/**
 * @brief デストラクタ
 */
Transitor::~Transitor()
{
}

/**
 * @brief 再スタート
 *
 * @param[in] isIn  フェードイン・アウト
 * 
 * @return なし
 */
void Transitor::ReStart(bool isIn)
{
	m_time = 0.0f;
	m_isIn = isIn;
}

/**
 * @brief 更新
 *
 * @param[in] なし
 * 
 * @return トランジション終了フラグ
 */
bool Transitor::Update()
{
	//	トランジション時間を超えたら終了
	if (m_time > TRANSITION_TIME) 
	{
		return true;
	}

	m_time+= Messenger::GetInstance()->GetElapsedTime();

	return false;
}

/**
 * @brief 描画
 *
 * @param[in] なし
 * 
 * @return なし
 */
void Transitor::Render() 
{

	ID3D11DeviceContext1* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = Graphics::GetInstance()->GetCommonStates();
	ShaderManager* shader = ShaderManager::GetInstance();

	//	頂点情報(板ポリゴンの４頂点の座標情報）
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture::VertexPositionColorTexture(
			DirectX::SimpleMath::Vector3(0.0f,  0.0f, 0.0f)
		,DirectX::SimpleMath::Vector4::One,DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
	};

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView = DirectX::SimpleMath::Matrix::Identity;
	cbuff.matProj = DirectX::SimpleMath::Matrix::Identity;
	cbuff.matWorld = DirectX::SimpleMath::Matrix::Identity;
	//	モードと時間のセット
	cbuff.mode = float(m_isIn);
	cbuff.time = m_time;

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::ShaderType::Fade), 0, NULL, &cbuff, 0, 0);
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
	//	シェーダの登録
	shader->StartShader(ShaderManager::ShaderType::Fade);
	//	インプットレイアウトの登録
	context->IASetInputLayout(shader->GetInputLayout(ShaderManager::ShaderType::Fade));

	//	板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//	シェーダの登録を解除しておく
	shader->EndShader();
}
