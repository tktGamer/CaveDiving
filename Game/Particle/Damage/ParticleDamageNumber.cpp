/**
 * @file   ParticleDamageNumber.cpp
 *
 * @brief  敵消滅パーティクルに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/09/25
 */

 // ヘッダファイルの読み込み ===================================================

#include "pch.h"
#include "ParticleDamageNumber.h"
#include"Game/Message/Messenger.h"
#include"Game/Shader.h"
#include"Game/Common/ResourceManager.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pos    描画する基準座標
 * @param[in] number 描画する数列
 */
ParticleDamageNumber::ParticleDamageNumber(const std::string& texturePsth, const DirectX::SimpleMath::Vector3& pos,const int& number)
	:ParticleControl{texturePsth}
	,m_basePosition{pos}
{
	//	プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());
	m_texture = ResourceManager::GetInstance()->RequestTexture(texturePsth);
	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CameraBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_CBuffer);

	//渡された数字の桁を取得
	int digit = CheckDigit(number);
	//数値をいじるので別の変数に代入
	int numbers = number;
	DirectX::SimpleMath::Vector3 numberPos = {0,0,0};
	
	for (int i = 0; i < digit; i++) 
	{
		//下位桁から
		int num = numbers % 10;
		numbers /= 10;

		m_particleNumber.push_back
		(
			ParticleNumber3D
			(
			2.0f,
			numberPos,
			{ 0.0f,2.5f,0.0f },
			{ 0.0f,-3.0f,0.0f },
			DirectX::SimpleMath::Vector3::One,
			DirectX::SimpleMath::Vector3::One,
			DirectX::SimpleMath::Color{1.0f,1.0f,0.0f,1.0f},
			DirectX::SimpleMath::Color{1.0f,1.0f,0.0f,0.0f},
			num)
		);

		numberPos.x += -1.0f;
	}

}
/**
 * @brief デストラクタ
 */
ParticleDamageNumber::~ParticleDamageNumber()
{
}

 /**
  * @brief 更新処理
  *
  * @param[in] なし
  *
  * @return なし
  */
void ParticleDamageNumber::Update()
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();
	////	0.1秒ごとに1つパーティクルを生成
	////m_timer += elapsedTime;
	//for (std::vector<TimerAndPos>::iterator ite = m_timerAndPos.begin(); ite != m_timerAndPos.end(); )
	//{
	//	//	タイマーの更新
	//	ite->timer += elapsedTime;
	//	if (ite->timer >= 0.1f)
	//	{

	//		//	タイマーと位置のリストから、生成したパーティクルの情報を削除する
	//		ite = m_timerAndPos.erase(ite);
	//	}
	//	else
	//	{
	//		//	まだ0.2秒経過していないので、次のタイマーへ
	//		ite++;
	//	}
	//}


	//	timerを渡してm_effectの更新処理を行う
	for (std::list<ParticleNumber3D>::iterator ite = m_particleNumber.begin(); ite != m_particleNumber.end(); ite++)
	{
		//	更新結果の戻り値（true / false）をチェック
		if (!(ite)->Update())
		{
			//	falseが返ってきたら、消す
			ite = m_particleNumber.erase(ite);

			if (ite == m_particleNumber.end())
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
void ParticleDamageNumber::Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp)
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
	m_particleNumber.sort(
		//	ソート処理の基準を示す関数については、ラムダ式で指定する
		[&](ParticleNumber3D lhs, ParticleNumber3D  rhs)
		{
			//	カメラ正面の距離でソート
			return cameraDir.Dot(lhs.GetPosition() - cameraPos) > cameraDir.Dot(rhs.GetPosition() - cameraPos);
		});

	//	表示に使う頂点リストに登録されているデータを全削除
	m_vertices.clear();
	//	パーティクル情報から、表示に使う頂点リストを生成する
	for (ParticleNumber3D& li : m_particleNumber)
	{
		if (cameraDir.Dot(m_basePosition - cameraPos) < 0.0f) {
			//	内積の結果がマイナスの場合はカメラの後ろなので表示する必要なし
			continue;
		}

		DirectX::VertexPositionColorTexture vPCT;
		//	表示するパーティクルの中心座標のみを入れる。
		vPCT.position = DirectX::XMFLOAT3(li.GetPosition() /*+ *m_centerPos*/);
		//	テクスチャの色
		vPCT.color = DirectX::XMFLOAT4(li.GetNowColor());
		//第４要素に表示する数字の情報を入れる
		vPCT.color.w = li.GetNumber();
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
	//	ワールド行列を計算する
	CreateBillboard(cameraPos, cameraUp);
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world = world * m_billboard;
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(Shader::ShaderType::Number3D), 0, NULL, &cbuff, 0, 0);

	CameraBuffer cameraBuff;
	cameraBuff.cameraPos = cameraPos;
	cameraBuff.cameraUp = cameraUp;

	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cameraBuff, 0, 0); // b1 に渡す
	ID3D11Buffer* lb[1] = { m_CBuffer.Get() };
	context->GSSetConstantBuffers(1, 1, lb);

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
	shader->StartShader(Shader::ShaderType::Number3D, shader->GetCBuffer(Shader::ShaderType::Number3D));

	context->PSSetShaderResources(0, 1, m_texture);

	//	インプットレイアウトの登録
	context->IASetInputLayout(shader->GetInputLayout(Shader::ShaderType::Number3D));

	//	板ポリゴンを描画
	m_batch->Begin();
	//	ジオメトリシェーダでPointを受け取ることになっているため、
	//	ここではD3D11_PRIMITIVE_TOPOLOGY_POINTLISTを使う
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());
	m_batch->End();

	//	シェーダの登録を解除しておく
	shader->EndShader();
}

void ParticleDamageNumber::Reset()
{

}

void ParticleDamageNumber::CreateBillboard(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up)
{
	//	ビルボードを実現するための行列を作成する	
	m_billboard = DirectX::SimpleMath::Matrix::CreateBillboard(
		m_basePosition,//自身の位置
		eye,//カメラの位置
		up //カメラの上ベクトル
	);

	//上記のみだと逆を向いてしまうので、Y軸を反転させる
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::Identity;
	//Y軸を反転
	rotY._11 = -1.0f;
	rotY._33 = -1.0f;
	//rotY = DirectX::SimpleMath::Matrix::CreateRotationY(180.0f / 180.0f * DirectX::XM_PI);
	//ビルボード行列にY軸反転行列を掛ける
	m_billboard = rotY * m_billboard;

	//m_isBillboard = true;
}

bool ParticleDamageNumber::IsDelete()
{
	
	return (m_particleNumber.size()==0);
}

int ParticleDamageNumber::CheckDigit(const int& num)
{
	//０なら一桁
	if (num == 0)
	{
		return 1;
	}

	int digit = 0;
	// 符号を考慮して絶対値を取る
	int temp = (num < 0) ? -num : num;
	while (temp > 0)
	{
		temp /= 10;
		digit++;
	}

	return digit;
}
