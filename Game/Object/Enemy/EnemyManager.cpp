/**
 * @file   EnemyManager.cpp
 *
 * @brief  敵管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/04
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "EnemyManager.h"
#include"Game/Common/Collision/CollisionManager.h"
#include"Game/Factory/GameObjectFactory.h"
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

	//敵の消去
	DeleteEnemy();

	//敵の更新
	for (std::unique_ptr<Character>& enemy : m_enemies)
	{
		enemy->Update(DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);	
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
 * @param[in] spawnData 敵生成データのパス
 *
 * @return なし
 */
void EnemyManager::Spawn(const std::string& spawnData)
{

	//ファイルのオープン
	std::ifstream ifs{ spawnData };
	if (!ifs.is_open())
	{
		//読み込み失敗
		return;
	}
	//読み込んだ文字列を入れる
	std::string line;
	//一行飛ばす
	std::getline(ifs, line);

	while (std::getline(ifs,line))
	{
		std::stringstream ss(line);
		//敵の種類
		std::string type;
		//座標
		std::string x, y, z;

		std::getline(ss, type, ',');
		std::getline(ss, x, ',');
		std::getline(ss, y, ',');
		std::getline(ss, z, ',');

		//数値に変換
		DirectX::SimpleMath::Vector3 spawnPos;
		spawnPos.x = std::stof(x);
		spawnPos.y = std::stof(y);
		spawnPos.z = std::stof(z);




		//読み込んだ種類を生成
		if (type == "コウモリ")
		{
			//生成
			m_enemies.emplace_back(GameObjectFactory::CreateBat());
		}
		//読み込んだ種類を生成
		else if (type == "ゴーレム")
		{
			//生成
			m_enemies.emplace_back(GameObjectFactory::CreateGolem());
		}

		//座標設定
		m_enemies.back()->SetPosition(spawnPos);
		//当たり判定クラスに登録
		CollisionManager::GetInstance()->Register(m_enemies.back().get());
		//メッセンジャークラスに登録
		Messenger::GetInstance()->Register(m_enemies.back()->GetObjectNumber(), m_enemies.back().get());

		//残りを飛ばす
		//ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	}
	//ファイルを閉じる
	ifs.close();

	return;

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

			//消滅パーティクル生成をリクエスト
			ParticleManager::GetInstance()->RequestVanishParticle((*it)->GetCurrentPosition());

            it = m_enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
