/**
 * @file   ParticleMoveDustControl.cpp
 *
 * @brief  敵消滅パーティクル管理に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/09/25
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ParticleMoveDustControl.h"

#include"Game/Common/ResourceManager.h"
#include"Game/Shader.h"
#include"Game/Message/Messenger.h"


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] texturePath テクスチャハンドル
 */
ParticleMoveDustControl::ParticleMoveDustControl(const std::string& texturePath)
	:ParticleControl{ texturePath }
	, m_timerAndPos{}
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
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_CBuffer);

}

/**
 * @brief デストラクタ
 */
ParticleMoveDustControl::~ParticleMoveDustControl()
{
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ParticleMoveDustControl::Update()
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();
	//	0.1秒ごとに1つパーティクルを生成
	for (std::vector<TimerAndPos>::iterator ite = m_timerAndPos.begin(); ite != m_timerAndPos.end(); )
	{
		//	タイマーの更新
		ite->timer += elapsedTime;
		if (ite->timer >= 0.2f)
		{
			//	タイマーと位置のリストから、生成したパーティクルの情報を削除する
			ite = m_timerAndPos.erase(ite);
		}
		else
		{
			//	まだ0.2秒経過していないので、次のタイマーへ
			ite++;
		}
	}


	//	timerを渡してm_effectの更新処理を行う
	for (std::list <ParticleMoveDust> ::iterator ite = m_particleMoveDust.begin(); ite != m_particleMoveDust.end(); ite++)
	{
		//	更新結果の戻り値（true / false）をチェック
		if (!(ite)->Update())
		{
			//	falseが返ってきたら、消す
			ite = m_particleMoveDust.erase(ite);

			if (ite == m_particleMoveDust.end())
			{
				//	最後のオブジェクトを消したので、ループ終了
				break;
			}
		}
	}
}


/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ParticleMoveDustControl::Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp)
{
	Shader* shader = Shader::GetInstance();
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext1* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();

	//	ビルボード設定時にもらったカメラ情報から、視線ベクトルを計算する
	DirectX::SimpleMath::Vector3 cameraDir = target - cameraPos;
	//	視線ベクトルは正規化しておく
	cameraDir.Normalize();

	//	パーティクル情報を、カメラからの距離順でソートする
	m_particleMoveDust.sort(
		//	ソート処理の基準を示す関数については、ラムダ式で指定する
		[&](ParticleMoveDust lhs, ParticleMoveDust  rhs)
		{
			//	カメラ正面の距離でソート
			return cameraDir.Dot(lhs.GetPosition() - cameraPos) > cameraDir.Dot(rhs.GetPosition() - cameraPos);
		});

	//	表示に使う頂点リストに登録されているデータを全削除
	m_vertices.clear();
	//	パーティクル情報から、表示に使う頂点リストを生成する
	for (ParticleMoveDust& li : m_particleMoveDust)
	{
		if (cameraDir.Dot(li.GetPosition() - cameraPos) < 0.0f) {
			//	内積の結果がマイナスの場合はカメラの後ろなので表示する必要なし
			continue;
		}

		DirectX::VertexPositionColorTexture vPCT;
		//	表示するパーティクルの中心座標のみを入れる。
		vPCT.position = DirectX::XMFLOAT3(li.GetPosition());
		//	テクスチャの色
		vPCT.color = DirectX::XMFLOAT4(li.GetNowColor());
		//	現在のテクスチャのスケールを「XMFLOAT2」のXに入れる。
		//	Yは使用しないため、0.0fを入れておく
		vPCT.textureCoordinate = DirectX::XMFLOAT2(li.GetNowScale().x, 0.0f);

		//	頂点情報を1つだけ追加。
		m_vertices.push_back(vPCT);
	}

	//	表示する点がない場合は描画を終わる
	if (m_vertices.empty())
	{
		return;
	}

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	//	ビュー設定
	cbuff.matView = view.Transpose();

	//	プロジェクション設定
	cbuff.matProj = proj.Transpose();
	//	ワールド設定

	cbuff.matWorld = DirectX::SimpleMath::Matrix::Identity.Transpose();
	cbuff.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(Shader::ShaderType::Particle), 0, NULL, &cbuff, 0, 0);



	CameraBuffer cameraBuff;
	cameraBuff.cameraPos = cameraPos;
	cameraBuff.cameraUp = cameraUp;

	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cameraBuff, 0, 0); // b1 に渡す
	ID3D11Buffer* lb[1] = { m_CBuffer.Get() };
	context->GSSetConstantBuffers(1, 1, lb);

	context->UpdateSubresource(shader->GetCBuffer(Shader::ShaderType::Particle), 0, NULL, &cbuff, 0, 0);

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

	//	シェーダをセットする
	shader->StartShader(Shader::ShaderType::Particle, shader->GetCBuffer(Shader::ShaderType::Particle));

	context->PSSetShaderResources(0, 1, m_texture);

	//	インプットレイアウトの登録
	context->IASetInputLayout(shader->GetInputLayout(Shader::ShaderType::Particle));

	//	板ポリゴンを描画
	m_batch->Begin();
	//	ジオメトリシェーダでPointを受け取ることになっているため、
	//	ここではD3D11_PRIMITIVE_TOPOLOGY_POINTLISTを使う
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());
	m_batch->End();

	//	シェーダの登録を解除しておく
	shader->EndShader();
}

/**
 * @brief リセット
 *
 * @param[in] なし
 *
 * @return なし
 */
void ParticleMoveDustControl::Reset()
{
	m_vertices.clear();
	m_particleMoveDust.clear();
	m_timerAndPos.clear();
}



/**
 * @brief 敵消滅パーティクルリクエスト
 *
 * @param[in] pos 発生位置
 *
 * @return なし
 */
void ParticleMoveDustControl::RequestMoveDustParticle(DirectX::SimpleMath::Vector3 pos)
{
	m_particleMoveDust.push_back(
		ParticleMoveDust(
			0.2f,																							//	生存時間(s)
			pos,																							//	基準座標
			{0.0f,1.0f,0.0f},													//	速度
			DirectX::SimpleMath::Vector3::One,																//	加速度
			DirectX::SimpleMath::Vector3::One, DirectX::SimpleMath::Vector3::One*1.0f,							//	初期スケール、最終スケール
			DirectX::SimpleMath::Color(1.f, 1.f, 1.f, 1.f), DirectX::SimpleMath::Color(1.f, 1.f, 1.f, 0.f)	//	初期カラー、最終カラー
		)
	);
	
	//	パーティクルの発生位置とタイマーを追加
	m_timerAndPos.push_back({ 0.0f, pos });
}
