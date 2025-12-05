/**
 * @file   ParticlePowerUpControl.cpp
 *
 * @brief  パワーアップパーティクル管理に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/12/03
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ParticlePowerUpControl.h"

#include"Game/Common/ResourceManager.h"
#include"Game/Shader/Shader.h"
#include"Game/Message/Messenger.h"


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] texturePath テクスチャハンドル
 */
ParticlePowerUpControl::ParticlePowerUpControl(const std::string& texturePath)
	:ParticleControl{texturePath}
	,m_centerPos{nullptr}
{

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
	for (std::vector<TimerAndPos>::iterator ite = GetTimerAndPos().begin(); ite != GetTimerAndPos().end(); )
	{
		//	タイマーの更新
		ite->timer += elapsedTime;
		if (ite->timer >= 0.1f)
		{
			//	タイマーと位置のリストから、生成したパーティクルの情報を削除する
			ite = GetTimerAndPos().erase(ite);
		}
		else
		{
			//	まだ0.2秒経過していないので、次のタイマーへ
			ite++;
		}
	}
	//	パーティクルの更新
	UpdateParticles();


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

	//	頂点情報の作成
	CreateVertex(target, cameraPos,
		[&]() 
		{
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
		
			//表示に使う頂点リストに登録されているデータを全削除
			ClearVertex();
			//	パーティクル情報から、表示に使う頂点リストを生成する
			for (const std::unique_ptr<Particle>& particle : GetParticleList())
			{
				if (cameraDir.Dot(particle.get()->GetPosition() - cameraPos) < 0.0f)
				{
					//	内積の結果がマイナスの場合はカメラの後ろなので表示する必要なし
					continue;
				}

				DirectX::VertexPositionColorTexture vPCT;
				//---カスタム部分---//
				//	表示するパーティクルの中心座標のみを入れる。
				vPCT.position = DirectX::XMFLOAT3(particle.get()->GetPosition() + *m_centerPos);
				//-----------------//

				//	テクスチャの色
				vPCT.color = DirectX::XMFLOAT4(particle.get()->GetNowColor());
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
	//通常の設定
	SetShaderState();

	//	シェーダをセットする
	shader->StartShader(Shader::ShaderType::Particle, shader->GetCBuffer(Shader::ShaderType::Particle));
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
void ParticlePowerUpControl::Reset()
{
	ClearParticles();
	ClearVertex();
	ClearTimerAndPos();
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

		AddParticle(std::make_unique<ParticlePowerUp>(
			0.3f,																	//	生存時間(s)
			DirectX::SimpleMath::Vector3{ addX,-1.0f,addZ },													//	基準座標
			DirectX::SimpleMath::Vector3{ 0.0f,10.0f,0.0f },														//	速度
			DirectX::SimpleMath::Vector3::One * -0.1f,								//	加速度
			DirectX::SimpleMath::Vector3::One, DirectX::SimpleMath::Vector3::One,	//	初期スケール、最終スケール
			color, color	//	初期カラー、最終カラー
		));

	}
	//	パーティクルの発生位置とタイマーを追加
	AddTimerAndPos(TimerAndPos{ 0.0f, pos });

	m_centerPos = &pos;
}
