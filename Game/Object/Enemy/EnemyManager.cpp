/**
 * @file   EnemyManager.cpp
 *
 * @brief  敵管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/08/27
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "EnemyManager.h"
#include"Game/Common/Collision/CollisionManager.h"
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
	m_enemies.emplace_back(std::make_unique<Bat>( nullptr, DirectX::SimpleMath::Vector3::Zero, DirectX::XMConvertToRadians(0.0f)));
	m_enemies.back()->Initialize();
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
            it = m_enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
