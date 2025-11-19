/**
 * @file   ParticleDamageControl.cpp
 *
 * @brief  敵消滅パーティクル管理に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/09/25
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ParticleDamageControl.h"

#include"Game/Common/ResourceManager.h"
#include"Game/Shader.h"
#include"Game/Message/Messenger.h"


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] texturePath テクスチャハンドル
 */
ParticleDamageControl::ParticleDamageControl(const std::string& texturePath)
{
	//m_texture = ResourceManager::GetInstance()->RequestTexture(texturePath);

}

/**
 * @brief デストラクタ
 */
ParticleDamageControl::~ParticleDamageControl()
{
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ParticleDamageControl::Update()
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();
	//	0.1秒ごとに1つパーティクルを生成
	//m_timer += elapsedTime;
	//for (std::vector<TimerAndPos>::iterator ite = m_timerAndPos.begin(); ite != m_timerAndPos.end(); )
	//{
	//	//	タイマーの更新
	//	ite->timer += elapsedTime;
	//	if (ite->timer >= 0.1f)
	//	{
	//		
	//		//	タイマーと位置のリストから、生成したパーティクルの情報を削除する
	//		ite = m_timerAndPos.erase(ite);
	//	}
	//	else
	//	{
	//		//	まだ0.2秒経過していないので、次のタイマーへ
	//		ite++;
	//	}
	//}


	////	timerを渡してm_effectの更新処理を行う
	//for (std::list<ParticleDamage>::iterator ite = m_particleDamage.begin(); ite != m_particleDamage.end(); ite++)
	//{
	//	//	更新結果の戻り値（true / false）をチェック
	//	if (!(ite)->Update())
	//	{
	//		//	falseが返ってきたら、消す
	//		ite = m_particleDamage.erase(ite);

	//		if (ite == m_particleDamage.end())
	//		{
	//			//	最後のオブジェクトを消したので、ループ終了
	//			break;
	//		}
	//	}
	//}
	for (std::unique_ptr<ParticleDamageNumber>& damageNumber : m_particleDamage)
	{
		damageNumber->Update();
	}

	m_particleDamage.remove_if([&](std::unique_ptr<ParticleDamageNumber>& particle) {return particle->IsDelete(); });
}


/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ParticleDamageControl::Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp)
{
	for (std::unique_ptr<ParticleDamageNumber>& damageNumber : m_particleDamage)
	{
		damageNumber->Render(target, cameraPos, cameraUp);
	}

}

/**
 * @brief リセット
 *
 * @param[in] なし
 *
 * @return なし
 */
void ParticleDamageControl::Reset()
{
	m_particleDamage.clear();
}



/**
 * @brief ダメージ数字パーティクルリクエスト
 *
 * @param[in] pos 発生位置
 * @param[in] range ランダムの描画位置のずれの範囲
 * @param[in] damage ダメージ量
 *
 * @return なし
 */
void ParticleDamageControl::RequestParticleDamage(const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector3& range,int damage)
{
	//マイナス値を入れられたときの対策
	DirectX::SimpleMath::Vector3 absRange = { std::abs(range.x),std::abs(range.y),std::abs(range.z) };
	//描画位置のずれをランダムに出す
	float offsetX = TKTLib::GetRand(-absRange.x, absRange.x);
	float offsetY = TKTLib::GetRand(-absRange.y, absRange.y);
	float offsetZ = TKTLib::GetRand(-absRange.z, absRange.z);


	m_particleDamage.emplace_back(
		std::make_unique< ParticleDamageNumber>(
			"number.png",
			pos +DirectX::SimpleMath::Vector3{offsetX,offsetY,offsetZ},
			damage
		)
	);
	
}


