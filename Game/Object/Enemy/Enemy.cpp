/**
 * @file   Enemy.cpp
 *
 * @brief  敵に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/04/02
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Enemy.h"
#include"Game/Particle/ParticleManager.h"
#include"Game/Object/Enemy/EnemyManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] enemyManager  管理クラスのポインタ
 * @param[in] hp			体力
 * @param[in] attack		攻撃力
 * @param[in] diffence		防御力
 * @param[in] parent		親クラスのポインタ
 * @param[in] transform		トランスフォーム
 * @param[in] gemID  　　　	所持宝石のIDリスト
 */
Enemy::Enemy(EnemyManager* enemyManager, int hp, int attack, int diffence,
	const GameObject3D* parent, const Transform& transform,
	const std::vector<int>& gemID)
	:
	Character{hp,attack,diffence,Tag::ObjectType::Enemy,parent,transform,gemID},
	m_pEnemyManager{enemyManager}
{

}

/**
 * @brief デストラクタ
 */
Enemy::~Enemy()
{

}

/**
 * @brief 死亡時処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Enemy::OnDead()
{
	//消滅パーティクル生成をリクエスト
	ParticleManager::GetInstance()->RequestVanishParticle(GetCurrentPosition());
	//
	m_pEnemyManager->DecreaseEnemyCount();
}
