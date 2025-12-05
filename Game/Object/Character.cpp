/**
 * @file   Character.cpp
 *
 * @brief  キャラのステータスに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Character.h"
#include"../Common/DamageSystem.h"
#include"../Common/Collision/CollisionManager.h"
#include"Game/Particle/ParticleManager.h"
#include"../Common/Collision/Sphere.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] hp 体力
 * @param[in] attack　攻撃力
 * @param[in] deffence　防御力
 * @param[in] type　オブジェクトの種類
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
 */
Character::Character(int hp, int attack, int diffence, Tag::ObjectType type, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:GameObject{type,parent,initialPosition,initialAngle}
	,m_hp{hp}
	,m_currentHp{hp}
	,m_attackPower{attack}
	,m_diffence{diffence}
	,m_isInvincible{false}
	,m_damageFlash{0.0f}
{
}



/**
 * @brief デストラクタ
 */
Character::~Character()
{

}


/**
 * @brief ダメージを受けたときの処理
 *
 * @param[in] other 攻撃してきたオブジェクト
 *
 * @return なし
 */
void Character::OnDamage(GameObject* other)
{
	//無敵なら処理を飛ばす
	if (IsInvincible())
	{
		return;
	}


	//当たった攻撃の方向
	m_damageDirection = GetCurrentPosition() - other->GetCurrentPosition();
	m_damageDirection.Normalize();


	// ダメージを受ける
	int damage = DamageSystem::GetInstance()->DamageToCharacter(other->Cast<Character>(), this);

	

	//ダメージ数値描画をリクエストする
	ParticleManager::GetInstance()->RequestDamageParticle(CollisionManager::GetInstance()->CheckContactPoint(this->GetShape(), other->GetShape()),{2,2,1},damage);
	
	//ダメージ状態へ遷移
	OnMessegeAccepted(Message::DAMAGED);

	//無敵になる
	SetInvincible(true);

}

/**
 * @brief ダメージをうける
 *
 * @param[in] うけるダメージ
 *
 * @return なし
 */
void Character::TakeDamage(const int& damage)
{
	if (damage < 0) 
	{
		return;
	}

	m_currentHp -= damage;

	if (m_currentHp < 0) 
	{
		m_currentHp = 0;
	}
}


/**
 * @brief ダメージフラッシュの更新
 *
 * @param[in] なし
 *
 * @return なし
 */
bool Character::DamageFlashUpdate()
{
	if (m_damageFlash == NO_DAMAGE_FLASH) 
	{
		return false;
	}

	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();
	//経過時間でフラッシュを弱める
	m_damageFlash -= elapsedTime;

	if (m_damageFlash < NO_DAMAGE_FLASH) 
	{
		m_damageFlash = NO_DAMAGE_FLASH;
	}

	return true;
}

/**
 * @brief 現在のHPを取得
 *
 * @param[in] なし
 *
 * @return 現在のHP
 */
const int& Character::GetCurrentHP() const
{
	return m_currentHp;
}


/**
 * @brief 現在のHPを設定
 *
 * @param[in] なし
 *
 * @return なし
 */
void Character::SetCurrentHP(const int& hp)
{
	m_currentHp = hp;
}

/**
 * @brief 最大HPを設定
 *
 * @param[in] hp 最大HP
 *
 * @return なし
 */
void Character::SetMaxHP(const int& hp)
{
	m_hp = hp;
}


/**
 * @brief 最大HPの取得
 *
 * @param[in] なし
 *
 * @return 最大HP
 */
const int Character::GetMaxHP()
{
	return m_hp;
}

/**
 * @brief 攻撃力の設定
 *
 * @param[in] attack 攻撃力
 *
 * @return なし
 */
void Character::SetAttackPower(const int& attack)
{
	m_attackPower = attack;
}

/**
 * @brief 攻撃力の取得
 *
 * @param[in] なし
 *
 * @return 攻撃力
 */
const int Character::GetAttackPower()
{
	return m_attackPower;
}

/**
 * @brief 防御力の設定
 *
 * @param[in] diffence 防御力
 *
 * @return なし
 */
void Character::SetDiffence(const int& diffence)
{
	m_diffence = diffence;
}

/**
 * @brief 防御力の取得
 *
 * @param[in] なし
 *
 * @return 防御力
 */
const int Character::GetDiffence()
{
	return m_diffence;
}

/**
 * @brief 死んでいるか
 *
 * @param[in] なし
 *
 * @return true　生きている
 * @return false 死んでいる
 */
bool Character::IsAlive() const
{
	return (m_currentHp > 0);
}

/**
 * @brief 無敵か
 *
 * @param[in] なし
 *
 * @return true　無敵
 * @return false 無敵ではない
 */
const bool Character::IsInvincible() const
{
	return m_isInvincible;
}

/**
 * @brief 無敵の設定
 *
 * @param[in] isInvinccible  無敵か
 *
 * @return なし
 */
void Character::SetInvincible(const bool& isInvinccible)
{
	m_isInvincible = isInvinccible;
}


/**
 * @brief ダメージを受けた方向を取得
 *
 * @param[in] なし
 *
 * @return ダメージを受けた方向
 */
const DirectX::SimpleMath::Vector3& Character::GetDamageDirection() const
{
	return m_damageDirection;
}

void Character::SetDamageDirection(const DirectX::SimpleMath::Vector3& damageDirection)
{
	m_damageDirection = damageDirection;
}

void Character::SetDamageFlash(const float& flash)
{
	m_damageFlash = flash;
}

const float& Character::GetDamageFlash() const
{
	return m_damageFlash;
}
