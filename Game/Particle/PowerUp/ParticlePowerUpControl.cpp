/**
 * @file   ParticlePowerUpControl.cpp
 *
 * @brief  敵消滅パーティクル管理に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/09/25
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ParticlePowerUpControl.h"

#include"Game/Common/ResourceManager.h"
#include"Game/Shader.h"
#include"Game/Message/Messenger.h"


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] texturePath テクスチャハンドル
 */
ParticlePowerUpControl::ParticlePowerUpControl(const std::string& texturePath)
	: m_timerAndPos{}
{
	m_texture = ResourceManager::GetInstance()->RequestTexture(texturePath);
	//	プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());

}

/**
 * @brief デストラクタ
 */
ParticlePowerUpControl::~ParticlePowerUpControl()
{
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ParticlePowerUpControl::Update()
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();
	//	0.1秒ごとに1つパーティクルを生成
	//m_timer += elapsedTime;
	for (std::vector<TimerAndPos>::iterator ite = m_timerAndPos.begin(); ite != m_timerAndPos.end(); )
	{
		//	タイマーの更新
		ite->timer += elapsedTime;
		if (ite->timer >= 0.1f)
		{
			////	0.2秒経過したら、パーティクルを生成
			//for (int i = 6; i < VANISH_PARTICLE_NUM; i++)
			//{

			//	m_particlePowerUp.push_back(
			//		ParticlePowerUp(
			//			0.2f,																					//	生存時間(s)
			//			ite->pos,																				//	基準座標
			//			VANISH_PARTICLE_DIRECTION[i] * 7.0f,													//	速度
			//			DirectX::SimpleMath::Vector3::One * -0.4f,												//	加速度
			//			DirectX::SimpleMath::Vector3::One * 0.1f, DirectX::SimpleMath::Vector3::One * 0.5f,		//	初期スケール、最終スケール
			//			DirectX::SimpleMath::Color(1.f, 1.f, 1.f, 1.f), DirectX::SimpleMath::Color(1.f, 1.f, 1.f, 1.f)	//	初期カラー、最終カラー
			//		)
			//	);
			//}
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
	for (std::list<ParticlePowerUp>::iterator ite = m_particlePowerUp.begin(); ite != m_particlePowerUp.end(); ite++)
	{
		//	更新結果の戻り値（true / false）をチェック
		if (!(ite)->Update())
		{
			//	falseが返ってきたら、消す
			ite = m_particlePowerUp.erase(ite);

			if (ite == m_particlePowerUp.end())
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
void ParticlePowerUpControl::Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp)
{
	Shader* shader = Shader::GetInstance();
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext1* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();

	//	ビルボード設定時にもらったカメラ情報から、視線ベクトルを計算する
	DirectX::SimpleMath::Vector3 cameraDir = m_cameraTarget - m_cameraPosition;
	//	視線ベクトルは正規化しておく
	cameraDir.Normalize();

	//	パーティクル情報を、カメラからの距離順でソートする
	m_particlePowerUp.sort(
		//	ソート処理の基準を示す関数については、ラムダ式で指定する
		[&](ParticlePowerUp lhs, ParticlePowerUp  rhs)
		{
			//	カメラ正面の距離でソート
			return cameraDir.Dot(lhs.GetPosition() - m_cameraPosition) > cameraDir.Dot(rhs.GetPosition() - m_cameraPosition);
		});

	//	表示に使う頂点リストに登録されているデータを全削除
	m_vertices.clear();
	//	パーティクル情報から、表示に使う頂点リストを生成する
	for (ParticlePowerUp& li : m_particlePowerUp)
	{
		if (cameraDir.Dot(li.GetPosition() - m_cameraPosition) < 0.0f) {
			//	内積の結果がマイナスの場合はカメラの後ろなので表示する必要なし
			continue;
		}

		DirectX::VertexPositionColorTexture vPCT;
		//	表示するパーティクルの中心座標のみを入れる。
		vPCT.position = DirectX::XMFLOAT3(li.GetPosition() + *m_centerPos);
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
	m_world = m_world.Identity * m_billboard;
	cbuff.matWorld = m_world.Transpose();
	cbuff.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
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
void ParticlePowerUpControl::Reset()
{
	m_vertices.clear();
	m_particlePowerUp.clear();
	m_timerAndPos.clear();
}



/**
 * @brief 敵消滅パーティクルリクエスト
 *
 * @param[in] pos 発生位置
 *
 * @return なし
 */
void ParticlePowerUpControl::RequestParticlePowerUp(const DirectX::SimpleMath::Vector3& pos,DirectX::SimpleMath::Color color)
{
	for (int i = 0; i < 6; i++)
	{
		
		float angle = DirectX::XMConvertToRadians(360.0f / 6* i); // 各オブジェクトの角度
		 float addX = 2.0f * cos(angle); // X座標
		 float addZ = 2.0f * sin(angle); // Z座標

		m_particlePowerUp.push_back(
			ParticlePowerUp(
				0.3f,																	//	生存時間(s)
				{ addX,-1.0f,addZ },													//	基準座標
				{0.0f,10.0f,0.0f},														//	速度
				DirectX::SimpleMath::Vector3::One*-0.1f,								//	加速度
				DirectX::SimpleMath::Vector3::One, DirectX::SimpleMath::Vector3::One,	//	初期スケール、最終スケール
				color, color	//	初期カラー、最終カラー
			)
		);
	}
	//	パーティクルの発生位置とタイマーを追加
	m_timerAndPos.push_back({ 0.0f, pos });

	m_centerPos = &pos;
}
