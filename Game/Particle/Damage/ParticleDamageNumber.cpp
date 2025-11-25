/**
 * @file   ParticleDamageNumber.cpp
 *
 * @brief  敵消滅パーティクルに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/11/25
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
 * @param[in] texturePsth    描画
 * @param[in] pos			 描画する基準座標
 * @param[in] number		 描画する数列
 */
ParticleDamageNumber::ParticleDamageNumber(const std::string& texturePsth, const DirectX::SimpleMath::Vector3& pos,const int& number)
	:ParticleControl{texturePsth}
	,m_basePosition{pos}
{
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

		AddParticle
		(
			std::make_unique<ParticleNumber3D>
			(
			2.0f,
			numberPos,
			DirectX::SimpleMath::Vector3{ 0.0f,2.5f,0.0f },
			DirectX::SimpleMath::Vector3{ 0.0f,-3.0f,0.0f },
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
	//	パーティクルの更新
	UpdateParticles();

}


/**
 * @brief 描画処理
 *
 * @param[in] target  　 カメラの注視点
 * @param[in] cameraPos　カメラの座標
 * @param[in] cameraUp　 カメラの上ベクトル
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


	//	頂点情報の作成
	CreateVertex(target, cameraPos,
		[&]() {
			//	ビルボード設定時にもらったカメラ情報から、視線ベクトルを計算する
			DirectX::SimpleMath::Vector3 cameraDir = target - cameraPos;
			//	視線ベクトルは正規化しておく
			cameraDir.Normalize();
			
			//	パーティクル情報を、カメラからの距離順でソートする
			GetParticleList().sort(
				//	ソート処理の基準を示す関数については、ラムダ式で指定する
				[&](const std::unique_ptr<Particle>& lhs, const std::unique_ptr<Particle>& rhs)
				{
					//	カメラ正面の距離でソート
					return cameraDir.Dot(lhs.get()->GetPosition() - cameraPos) > cameraDir.Dot(rhs.get()->GetPosition() - cameraPos);
				});
			
			//	表示に使う頂点リストに登録されているデータを全削除
			ClearVertex();
			//	パーティクル情報から、表示に使う頂点リストを生成する
			for (const std::unique_ptr<Particle>& particle : GetParticleList())
			{
				//---カスタム部分---//
				if (cameraDir.Dot(m_basePosition - cameraPos) < 0.0f) 
				//-----------------//
				{
					//内積の結果がマイナスの場合はカメラの後ろなので表示する必要なし
					continue;
				}
			
				DirectX::VertexPositionColorTexture vPCT;
				//	表示するパーティクルの中心座標のみを入れる。
				vPCT.position = DirectX::XMFLOAT3(particle.get()->GetPosition());
				//	テクスチャの色
				vPCT.color = DirectX::XMFLOAT4(particle.get()->GetNowColor());
				//---カスタム部分---//
				//第４要素に表示する数字の情報を入れる
				vPCT.color.w =dynamic_cast<ParticleNumber3D*>(particle.get())->GetNumber();
				//-----------------//

				//	現在のテクスチャのスケールを「XMFLOAT2」のXに入れる。
				//	Yは使用しないため、0.0fを入れておく
				vPCT.textureCoordinate = DirectX::XMFLOAT2(particle.get()->GetNowScale().x, 0.0f);
			
				//	頂点情報を1つだけ追加。
				AddVertex(vPCT);
			}
			
		});

	//	頂点情報がない場合は描画を終わる
	if (!HasVertex())
	{
		return;
	}

	//カメラの情報を渡す
	ParticleControl::CameraBuffer cameraBuff;
	cameraBuff.cameraPos = cameraPos;
	cameraBuff.cameraUp = cameraUp;
	SetCameraBuffer(cameraBuff);
	//コンストバッファの要素が基底と異なるのでSetShaderStateは使わない
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


	context->PSSetShaderResources(0, 1, GetTexture());

	//	インプットレイアウトの登録
	context->IASetInputLayout(shader->GetInputLayout(Shader::ShaderType::Number3D));

	//	シェーダをセットする
	shader->StartShader(Shader::ShaderType::Number3D, shader->GetCBuffer(Shader::ShaderType::Number3D));
	//	プリミティブバッチの描画処理
	DrawBatch();
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
void ParticleDamageNumber::Reset()
{
	ClearVertex();
	ClearParticles();
}

/**
 * @brief ビルボード
 *
 * @param[in] eye　カメラの座標
 * @param[in] up　 カメラの上ベクトル
 *
 * @return なし
 */
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

}

/**
 * @brief 削除するか
 *
 * @param[in] なし
 *
 * @return true   削除する
 *		   false　削除しない
 */
bool ParticleDamageNumber::IsDelete()
{
	
	return (GetParticleList().size() == 0);
}


/**
 * @brief 桁数カウント
 *
 * @param[in] num　数列
 *
 * @return 桁数
 */
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
