/**
 * @file   ParticleControl.cpp
 *
 * @brief  パーティクル管理の基底に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/28
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ParticleControl.h"
#include"Game/Common/ResourceManager.h"
#include"Game/Shader/ShaderManager.h"
#include"Game/Message/Messenger.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] texturePath テクスチャハンドル
 */
ParticleControl::ParticleControl(const wchar_t* texturePath)
	: 
	m_timerAndPos{},
	m_vertices{},
	m_batch{},
	m_cameraCBuffer{},
	m_texture{},
	m_particles{}
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
 * @param[in] なし
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
 * @param[in] なし
 * 
 * @return テクスチャハンドル
 */
ID3D11ShaderResourceView** ParticleControl::GetTexture() const
{
	return m_texture;
}

/**
 * @brief パーティクルの更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void ParticleControl::UpdateParticles()
{
	//パーティクルのリストを先頭から順に更新していく
	for (std::list<std::unique_ptr<Particle>>::iterator ite = m_particles.begin(); ite != m_particles.end(); ite++)
	{
		//	更新結果の戻り値（true / false）をチェック
		if (!(ite)->get()->Update())
		{
			//	falseが返ってきたら、消す
			ite = m_particles.erase(ite);

			if (ite == m_particles.end())
			{
				//	最後のオブジェクトを消したので、ループ終了
				break;
			}
		}
	}

}

/**
 * @brief パーティクルの追加
 *
 * @param[in] pParticle パーティクルポインタ
 *
 * @return なし
 */
void ParticleControl::AddParticle(std::unique_ptr<Particle> pParticle)
{
	m_particles.push_back(std::move(pParticle));
}

/**
 * @brief パーティクルリスト取得
 *
 * @param[in] なし
 * 
 * @return パーティクルリストの参照
 */
std::list<std::unique_ptr<Particle>>& ParticleControl::GetParticleList()
{
	return m_particles;
}

/**
 * @brief パーティクルの消去
 *
 * @param[in] なし
 *
 * @return なし
 */
void ParticleControl::ClearParticles()
{
	m_particles.clear();
}

/**
 * @brief 頂点を作成
 *
 * @param[in] target  カメラの注視点座標
 * @param[in] cameraPos カメラの座標
 * @param[in] customCreate  カスタム生成処理
 *
 * @return　なし
 */
void ParticleControl::CreateVertex(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const std::function<void()>& customCreate)
{
	//関数が渡されてきたら実行する
	if (customCreate)
	{
		customCreate();
		return;
	}

	//	ビルボード設定時にもらったカメラ情報から、視線ベクトルを計算する
	DirectX::SimpleMath::Vector3 cameraDir = target - cameraPos;
	//	視線ベクトルは正規化しておく
	cameraDir.Normalize();

	//	パーティクル情報を、カメラからの距離順でソートする
	m_particles.sort(
		//	ソート処理の基準を示す関数については、ラムダ式で指定する
		[&](const std::unique_ptr<Particle>& lhs, const std::unique_ptr<Particle>& rhs)
		{
			//	カメラ正面の距離でソート
			return cameraDir.Dot(lhs.get()->GetPosition() - cameraPos) > cameraDir.Dot(rhs.get()->GetPosition() - cameraPos);
		});


	//	表示に使う頂点リストに登録されているデータを全削除
	ClearVertex();
	//	パーティクル情報から、表示に使う頂点リストを生成する
	for (const std::unique_ptr<Particle>& particle : m_particles)
	{
		if (cameraDir.Dot(particle.get()->GetPosition() - cameraPos) < 0.0f)
		{
			//	内積の結果がマイナスの場合はカメラの後ろなので表示する必要なし
			continue;
		}

		DirectX::VertexPositionColorTexture vPCT;
		//	表示するパーティクルの中心座標のみを入れる。
		vPCT.position = DirectX::XMFLOAT3(particle.get()->GetPosition());
		//	テクスチャの色
		vPCT.color = DirectX::XMFLOAT4(particle.get()->GetNowColor());
		//	現在のテクスチャのスケールを「XMFLOAT2」のXに入れる。
		//	Yは使用しないため、0.0fを入れておく
		vPCT.textureCoordinate = DirectX::XMFLOAT2(particle.get()->GetNowScale().x, 0.0f);

		//	頂点情報を1つだけ追加。
		AddVertex(vPCT);
	}

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
 * @brief 発生位置・タイマーの取得
 *
 * @param[in] なし
 * 
 * @return 発生位置・タイマーの参照
 */
std::vector<ParticleControl::TimerAndPos>& ParticleControl::GetTimerAndPos()
{
	return m_timerAndPos;
}

/**
 * @brief 発生位置・タイマーの消去
 *
 * @return なし
 */
void ParticleControl::ClearTimerAndPos()
{
	m_timerAndPos.clear();
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
void ParticleControl::SetShaderState() const
{
	ShaderManager* shader = ShaderManager::GetInstance();
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = Graphics::GetInstance()->GetCommonStates();

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ParticleShader::ParticleCB cbuff;
	//	ビュー設定
	cbuff.matView = Graphics::GetInstance()->GetViewMatrix().Transpose();
	//	プロジェクション設定
	cbuff.matProj = Graphics::GetInstance()->GetProjectionMatrix().Transpose();
	//	ワールド設定
	cbuff.matWorld = DirectX::SimpleMath::Matrix::Identity.Transpose();
	cbuff.diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::ShaderType::Particle), 0, NULL, &cbuff, 0, 0);
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
	context->IASetInputLayout(shader->GetInputLayout(ShaderManager::ShaderType::Particle));
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