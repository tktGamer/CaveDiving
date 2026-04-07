/**
 * @file   EnemyManager.cpp
 *
 * @brief  敵管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/03
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "EnemyManager.h"
#include"Game/Factory/GameObjectFactory.h"
#include<fstream>
#include<sstream>
#include"Game/Common/Sound.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
EnemyManager::EnemyManager()
	:
	m_enemyCount{},
	m_vanishSound{}
{
	m_vanishSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::ENEMY_VANISH));
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
 * @return 敵リスト
 */
std::vector<std::unique_ptr<Character>> EnemyManager::Spawn(const std::string& spawnData)
{
	std::vector<std::unique_ptr<Character>> enemies;

	//ファイルのオープン
	std::ifstream ifs{ spawnData };
	if (!ifs.is_open())
	{
		//読み込み失敗
		return enemies;
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
		std::getline(ss, type, ',');
		//座標
		std::string x, y, z;
		std::getline(ss, x, ',');
		std::getline(ss, y, ',');
		std::getline(ss, z, ',');
		//宝石の番号
		std::string gemID1, gemID2, gemID3;
		std::getline(ss, gemID1, ',');
		std::getline(ss, gemID2, ',');
		std::getline(ss, gemID3, ',');

		//数値に変換
		DirectX::SimpleMath::Vector3 spawnPos;
		spawnPos.x = std::stof(x);
		spawnPos.y = std::stof(y);
		spawnPos.z = std::stof(z);
		std::vector<int> gemID;
		gemID.push_back(std::stoi(gemID1));
		gemID.push_back(std::stoi(gemID2));
		gemID.push_back(std::stoi(gemID3));

		//読み込んだ種類を生成
		if (type == BAT)
		{
			//生成
			enemies.emplace_back(GameObjectFactory::CreateBat(this,nullptr,spawnPos,DirectX::SimpleMath::Quaternion::Identity,gemID));
		}
		//読み込んだ種類を生成
		else if (type == GOLEM)
		{
			//生成
			enemies.emplace_back(GameObjectFactory::CreateGolem(this,nullptr,spawnPos,DirectX::SimpleMath::Quaternion::Identity, gemID));
		}

	}
	//ファイルを閉じる
	ifs.close();
	return enemies;
}


/**
 * @brief 敵がステージ外にいるか
 *
 * @param[in] なし
 *
 * @return true  ステージ外
 *         false ステージ内
 */
bool EnemyManager::IsOutOfStage(const Character* enemy)
{
	return (enemy->GetCurrentPosition().y < DEAD_LINE);
}



/**
 * @brief 敵の数取得
 *
 * @param[in] なし
 *
 * @return 敵の数
 */
const int EnemyManager::GetEnemyCount() const
{
	return m_enemyCount;
}
/**
 * @brief 敵の数設定
 *
 * @param[in] count  敵の数
 *
 * @return なし
 */
void EnemyManager::SetEnemyCount(const int& count)
{
	m_enemyCount = count;
}
/**
 * @brief 敵の数を減らす
 *
 * @param[in] なし
 *
 * @return なし
 */
void EnemyManager::DecreaseEnemyCount()
{
	m_enemyCount--;
}
