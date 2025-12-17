/**
 * @file   ParticleHPHealControl.cpp
 *
 * @brief  HP回復パーティクル管理に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/12/10
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ParticleHPHealControl.h"

#include"Game/Common/ResourceManager.h"
#include"Game/Shader/ShaderManager.h"
#include"Game/Message/Messenger.h"


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] texturePath テクスチャハンドル
 */
ParticleHPHealControl::ParticleHPHealControl(const std::string& texturePath)
	:ParticleControl{ texturePath }
	, m_centerPos{ nullptr }
{

}

/**
 * @brief デストラクタ
 */
ParticleHPHealControl::~ParticleHPHealControl()
{
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ParticleHPHealControl::Update()
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
void ParticleHPHealControl::Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp)
{

	ShaderManager* shader = ShaderManager::GetInstance();
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
	ParticleShader::CameraCB cameraBuff;
	cameraBuff.cameraPos = cameraPos;
	cameraBuff.cameraUp = cameraUp;
	shader->SetCameraCB(cameraBuff);
	//通常の設定
	SetShaderState();

	//	シェーダをセットする
	shader->StartShader(ShaderManager::ShaderType::Particle);
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
void ParticleHPHealControl::Reset()
{
	ClearParticles();
	ClearVertex();
	ClearTimerAndPos();
}


/**
 * @brief HP回復パーティクルリクエスト
 *
 * @param[in] pos 発生位置
 *
 * @return なし
 */
void ParticleHPHealControl::RequestParticleHPHeal(const DirectX::SimpleMath::Vector3& pos)
{
	for (int i = 0; i < HPHEAL_PARTICLE_NUM; i++)
	{

		AddParticle(std::make_unique<ParticleHPHeal>(
			0.3f,																	//	生存時間(s)
			HPHEAL_PARTICLE_POSITION[i],								//	基準座標
			DirectX::SimpleMath::Vector3{ 0.0f,9.0f,0.0f },						//	速度
			DirectX::SimpleMath::Vector3::One * -0.1f,								//	加速度
			DirectX::SimpleMath::Vector3::One, DirectX::SimpleMath::Vector3::One,	//	初期スケール、最終スケール
			DirectX::SimpleMath::Color{ 1,1,1,1 }, DirectX::SimpleMath::Color{ 1,1,1,1 } 	//	初期カラー、最終カラー
		));
	}

	//	パーティクルの発生位置とタイマーを追加
	AddTimerAndPos(TimerAndPos{ 0.0f, pos });

	m_centerPos = &pos;

}
