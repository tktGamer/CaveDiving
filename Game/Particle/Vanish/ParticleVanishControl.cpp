/**
 * @file   ParticleVanishControl.cpp
 *
 * @brief  敵消滅パーティクル管理に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/11/25
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ParticleVanishControl.h"

#include"Game/Common/ResourceManager.h"
#include"Game/Shader/ShaderManager.h"
#include"Game/Message/Messenger.h"


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] texturePath テクスチャハンドル
 */
ParticleVanishControl::ParticleVanishControl(const wchar_t* texturePath)
	:ParticleControl{texturePath}
{

}

/**
 * @brief デストラクタ
 */
ParticleVanishControl::~ParticleVanishControl()
{
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ParticleVanishControl::Update()
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();
	//	0.1秒ごとに1つパーティクルを生成
	for (std::vector<TimerAndPos>::iterator ite = GetTimerAndPos().begin(); ite != GetTimerAndPos().end(); )
	{
		//	タイマーの更新
		ite->timer += elapsedTime;
		if (ite->timer >= 0.1f)
		{
			//	0.2秒経過したら、パーティクルを生成
			for (int i = 6; i < VANISH_PARTICLE_NUM; i++)
			{

				AddParticle(std::make_unique<ParticleVanish>(
					0.2f,																					//	生存時間(s)
					ite->pos,																				//	基準座標
					VANISH_PARTICLE_DIRECTION[i] * 7.0f,													//	速度
					DirectX::SimpleMath::Vector3::One * -0.4f,												//	加速度
					DirectX::SimpleMath::Vector3::One * 0.1f, DirectX::SimpleMath::Vector3::One * 0.5f,		//	初期スケール、最終スケール
					DirectX::SimpleMath::Color(1.f, 1.f, 1.f, 1.f), DirectX::SimpleMath::Color(1.f, 1.f, 1.f, 1.f)	//	初期カラー、最終カラー
				));
			}
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
void ParticleVanishControl::Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp)
{
	ShaderManager* shader = ShaderManager::GetInstance();
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext1* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();

	//	頂点情報の作成
	CreateVertex(target, cameraPos);

	//	頂点情報がない場合は描画を終わる
	if (!HasVertex()) 
	{
		return;
	}

	//カメラの情報を渡す
	ParticleShader::CameraCB cameraBuff;
	cameraBuff.cameraPos = cameraPos;
	cameraBuff.cameraUp  = cameraUp;
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
void ParticleVanishControl::Reset()
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
void ParticleVanishControl::RequestVanishParticle(DirectX::SimpleMath::Vector3 pos)
{
	for (int i = 0; i < 6; i++)
	{

		//m_particleVanish.push_back(
		//	ParticleVanish(
		//		0.2f,																							//	生存時間(s)
		//		pos,																							//	基準座標
		//		VANISH_PARTICLE_DIRECTION[i]*7.0f,													//	速度
		//		DirectX::SimpleMath::Vector3::One*-0.4f,																//	加速度
		//		DirectX::SimpleMath::Vector3::One*0.1f, DirectX::SimpleMath::Vector3::One*0.5f,							//	初期スケール、最終スケール
		//		DirectX::SimpleMath::Color(1.f, 1.f, 1.f, 1.f), DirectX::SimpleMath::Color(1.f, 1.f, 1.f, 1.f)	//	初期カラー、最終カラー
		//	)
		//);

		AddParticle(std::make_unique<ParticleVanish>(
			0.2f,																							//	生存時間(s)
			pos,																							//	基準座標
			VANISH_PARTICLE_DIRECTION[i] * 7.0f,															//	速度
			DirectX::SimpleMath::Vector3::One * -0.4f,														//	加速度
			DirectX::SimpleMath::Vector3::One * 0.1f, DirectX::SimpleMath::Vector3::One * 0.5f,				//	初期スケール、最終スケール
			DirectX::SimpleMath::Color(1.f, 1.f, 1.f, 1.f), DirectX::SimpleMath::Color(1.f, 1.f, 1.f, 1.f)	//	初期カラー、最終カラー
		));
	}
	//	パーティクルの発生位置とタイマーを追加
	//m_timerAndPos.push_back({ 0.0f, pos });
	AddTimerAndPos(TimerAndPos{ 0.0f, pos });
}
