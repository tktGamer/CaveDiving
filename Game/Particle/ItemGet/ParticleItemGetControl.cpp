/**
 * @file   ParticleItemGetControl.cpp
 *
 * @brief  パーティクル管理に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/11/25
 */		

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ParticleItemGetControl.h"

#include"Game/Shader/Shader.h"
#include"Game/Message/Messenger.h"


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] texturePath テクスチャハンドル
 */
ParticleItemGetControl::ParticleItemGetControl(const std::string& texturePath)
	:ParticleControl{ texturePath }
{

}

/**
 * @brief デストラクタ
 */
ParticleItemGetControl::~ParticleItemGetControl()
{
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ParticleItemGetControl::Update()
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
 * @param[in] target  　 カメラの注視点
 * @param[in] cameraPos　カメラの座標
 * @param[in] cameraUp　 カメラの上ベクトル
 *
 * @return なし
 */
void ParticleItemGetControl::Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp)
{
	Shader* shader = Shader::GetInstance();

	//	頂点情報の作成
	CreateVertex(target, cameraPos);

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
void ParticleItemGetControl::Reset()
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
void ParticleItemGetControl::RequestItemGetParticle(const DirectX::SimpleMath::Vector3& pos,const DirectX::SimpleMath::Vector3& targetPos,const DirectX::SimpleMath::Color& color)
{
	//ランダムな数のパーティクルを発生させる
	int particleNum = static_cast<int>(TKTLib::GetRand(10, 15));

	for (int i = 0; i < particleNum; i++)
	{
		//ランダムにポジションをずらす
		DirectX::SimpleMath::Vector3 randomPos = 
		{
			static_cast<float>(TKTLib::GetRand(-2.0f,2.0f)),
			static_cast<float>(TKTLib::GetRand(-3.0f,3.0f)),
			static_cast<float>(TKTLib::GetRand(-2.0f,2.0f))
	
	
		};

		AddParticle(
			std::make_unique<ParticleItemGet>(
				targetPos,
				0.7f,																							//	生存時間(s)
				pos + randomPos,																				//	基準座標
				DirectX::SimpleMath::Vector3{ 0.0f,3.0f,0.0f },													//	速度
				DirectX::SimpleMath::Vector3::One,																//	加速度
				DirectX::SimpleMath::Vector3::One*0.5f, DirectX::SimpleMath::Vector3::One * 0.5f,				//	初期スケール、最終スケール
				color,color	//	初期カラー、最終カラー
			)
		);
	}
	
	//	パーティクルの発生位置とタイマーを追加
	AddTimerAndPos(TimerAndPos{ 0.0f, pos });
}
