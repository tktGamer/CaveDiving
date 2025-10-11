/**
 * @file   EnemyManager.cpp
 *
 * @brief  敵管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/10/08
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "EnemyManager.h"
#include"Game/Common/Collision/CollisionManager.h"
#include"Game/Fuctory/GameObjectFactory.h"
#include"Game/Particle/ParticleManager.h"
#include<fstream>
#include<sstream>

 // メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
EnemyManager::EnemyManager()
	:m_graphics{Graphics::GetInstance()}
{

}



/**
 * @brief デストラクタ
 */
EnemyManager::~EnemyManager()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void EnemyManager::Initialize()
{
	
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void EnemyManager::Update()
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();

	//敵の消去
	DeleteEnemy();

	//敵の更新
	for (std::unique_ptr<Character>& enemy : m_enemies)
	{
		enemy->Update(elapsedTime, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);	
	}
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void EnemyManager::Draw()
{

	//敵の描画
	for (std::unique_ptr<Character>& enemy : m_enemies)
	{
		enemy->Draw();
	}

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void EnemyManager::Finalize()
{

}

/**
 * @brief 敵の生成
 *
 * @param[in] なし
 *
 * @return なし
 */
void EnemyManager::Spawn()
{


	//スポーン位置
	DirectX::SimpleMath::Vector3 spawnPos = DirectX::SimpleMath::Vector3::Zero;

	//パスの生成
	std::string path = "Resources/Data/EnemySpawnData.csv";
	//ファイルのオープン
	std::ifstream ifs{ path };
	if (!ifs.is_open())
	{
		//読み込み失敗
		return;
	}

	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	while (ifs)
	{
		//敵の種類を読み込む
		std::string line;
		std::getline(ifs, line, ',');
		
		//座標を読み込む
		ifs >> spawnPos.x;
		ifs.ignore(); //カンマを読み飛ばす
		ifs >> spawnPos.y;
		ifs.ignore(); //カンマを読み飛ばす
		ifs >> spawnPos.z;
		ifs.ignore(); //カンマを読み飛ばす



		//読み込んだ種類を生成
		if (line == "コウモリ") 
		{
			m_enemies.emplace_back(GameObjectFactory::CreateBat());
			m_enemies.back()->SetPosition(spawnPos);
			CollisionManager::GetInstance()->Register(m_enemies.back().get());
			Messenger::GetInstance()->Register(m_enemies.back()->GetObjectNumber(), m_enemies.back().get());
		}
		
		ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	}
	ifs.close();

	return;
}


void EnemyManager::SpawnBoss()
{
	m_enemies.emplace_back(std::make_unique<Golem>(nullptr, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity));
	m_enemies.back()->Initialize();
	m_enemies.back()->SetPosition({ 0.0f, 1.0f, -8.0f });
	CollisionManager::GetInstance()->Register(m_enemies.back().get());
	Messenger::GetInstance()->Register(m_enemies.back()->GetObjectNumber(), m_enemies.back().get());


}

/**
 * @brief 敵の消去
 *
 * @param[in] なし
 *
 * @return なし
 */
void EnemyManager::DeleteEnemy()
{
    for (std::list<std::unique_ptr<Character>>::iterator it = m_enemies.begin(); it != m_enemies.end(); )
    {
		//生きているか確認
        if (!(*it)->IsAlive())
        {
            // 死亡している場合はリストから削除
            CollisionManager::GetInstance()->UnRegister(it->get());


			ParticleManager::GetInstance()->RequestParticle(ParticleManager::ParticleType::Vanish, (*it)->GetCurrentPosition(),{1.0f,1.0f,1.0f,1.0f});
            it = m_enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
