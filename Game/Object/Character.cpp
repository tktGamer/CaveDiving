/**
 * @file   Character.cpp
 *
 * @brief  キャラのステータスに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/04/09
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Character.h"
#include"../Common/DamageSystem.h"
#include"../Common/Collision/CollisionManager.h"
#include"Game/Particle/ParticleManager.h"
#include"../Common/Collision/Sphere.h"
#include"../Common/Sound.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] hp 体力
 * @param[in] attack　攻撃力
 * @param[in] deffence　防御力
 * @param[in] type　オブジェクトの種類
 * @param[in] parent　親クラスのポインタ
 * @param[in] transform　トランスフォーム
 */
Character::Character(const int& hp,const int& attack,const int& diffence, const Tag::ObjectType& type,
	const GameObject3D* parent, const Transform& transform,const std::vector<int>& gemID)
	:
	GameObject3D{type,parent,transform},
	m_hp{hp},
	m_currentHp{hp},
	m_attackPower{attack},
	m_diffence{diffence},
	m_isInvincible{false},
	m_motionAttackRate{ 0.0f },
	m_damageFlash{ NO_DAMAGE_FLASH },
	m_isOnGround{ false },
	m_holderGem{std::make_unique<HolderGem>(gemID)}
{
	//ダメージ時の音　　
	m_damageSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound( ResourcePath::SOUND::ATTACK_HIT));
	m_damageSound->SetVolume(0.5f);
}

/**
 * @brief デストラクタ
 */
Character::~Character()
{
}

/**
 * @brief 攻撃を受けたときの処理
 *
 * @param[in] other 攻撃してきたオブジェクト
 *
 * @return なし
 */
void Character::OnDamage(GameObject3D* attacker)
{
	//無敵なら処理を飛ばす
	if (IsInvincible())
	{
		return;
	}
	//当たった攻撃の方向
	m_damageDirection = GetCurrentPosition() - attacker->GetCurrentPosition();
	m_damageDirection.Normalize();

	// ダメージを受ける
	int damage = TakeDamage(attacker->Cast<Character>());
	//ダメージ数値描画をリクエストする
	ParticleManager::GetInstance()->RequestDamageParticle(CollisionManager::GetInstance()->CheckContactPoint(this->GetShape(),
															attacker->GetShape()),{2,2,1},damage);
	//ダメージ状態へ遷移
	OnMessegeAccepted(Message::DAMAGED);
	//無敵になる
	SetInvincible(true);

	SetDamageFlash();
}

/**
 * @brief ダメージをうける
 *
 * @param[in] うけるダメージ
 *
 * @return なし
 */
int Character::TakeDamage(const Character* attacker)
{
	int damage = DamageSystem::GetInstance()->DamageToCharacter(attacker, this);
	//ダメージがマイナスなら0にする
	if (damage < 0) 
	{
		return 0;
	}
	//体力を減らす
	m_currentHp -= damage;

	m_damageSound->Play(false);
	
	if (m_currentHp < 0) 
	{
		m_currentHp = 0;
	}

	return damage;
}


/**
 * @brief ダメージフラッシュの更新
 *
 * @param[in] なし
 *
 * @return true  点滅中
 * @return false なし
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
	//マイナスにならないように
	if (m_damageFlash < NO_DAMAGE_FLASH) 
	{
		m_damageFlash = NO_DAMAGE_FLASH;
	}

	return true;
}

/**
 * @brief 移動方向の計算
 *
 * @param[in] なし
 *
 * @return 移動方向
 */
DirectX::SimpleMath::Vector3 Character::CalcMoveDirection() const
{

	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;
	//ビット演算から入力された方向に進む
	if (m_moveFlags & MOVE_FRONT) 
	{
		direction += MOVE::FRONT;
	}
	if (m_moveFlags & MOVE_BACK) 
	{
		direction += MOVE::BACK;
	}
	if (m_moveFlags & MOVE_LEFT) 
	{
		direction += MOVE::LEFT;
	}
	if (m_moveFlags & MOVE_RIGHT) 
	{ 
		direction += MOVE::RIGHT;
	}

	// 反対方向同時押しの打ち消しは自然にゼロになる

	if (direction.LengthSquared() > 0.0f)
	{
		direction.Normalize(); // 斜め移動の速度補正
	}

	return direction;
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
const int Character::GetMaxHP() const
{
	return  m_holderGem->ApplyStatus(Gem::Type::HP, *this) + m_hp;
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
const int Character::GetAttackPower() const
{
	return m_holderGem->ApplyStatus(Gem::Type::STR, *this) + m_attackPower;
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
const int Character::GetDiffence() const
{
	return m_holderGem->ApplyStatus(Gem::Type::DEF, *this) +  m_diffence;
}

/**
 * @brief モーションによる攻撃力補正の取得
 *
 * @param[in] なし
 *
 * @return モーションによる攻撃力補正
 */
void Character::SetMotionAttackRate(const float& rate)
{
	m_motionAttackRate = rate;
}

/**
 * @brief モーションによる攻撃力補正の取得
 *
 * @param[in] なし
 *
 * @return モーションによる攻撃力補正
 */
const float& Character::GetMotionAttackRate() const
{
	return m_motionAttackRate;
}

/**
 * @brief 速度の取得
 *
 * @param[in] なし
 *
 * @return 速度
 */
DirectX::SimpleMath::Vector3 Character::GetVelocity() const
{
	return m_velocity;
}

/**
 * @brief 速度の設定
 *
 * @param[in] velocity 速度
 *
 * @return なし
 */
void Character::SetVelocity(const DirectX::SimpleMath::Vector3& velocity)
{
	m_velocity = velocity;
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
 * @brief 地上にいるか
 *
 * @param[in] なし
 *
 * @return true　地上
 * @return false 空中
 */
bool Character::IsOnGround() const
{
	return m_isOnGround;
}

/**
 * @brief 地上にいるかの設定
 *
 * @param[in] isOnGround　　地上にいるか
 *
 * @return　なし
 */
void Character::SetIsOnGround(const bool& isOnGround)
{
	m_isOnGround = isOnGround;
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
 * @brief ダメージ無効回数の追加
 *
 * @param[in] addCount　追加回数  
 *
 * @return なし
 */
void Character::AddInvincibleCount(const int& addCount)
{
	m_invincibleCount += addCount;
}

/**
 * @brief ダメージ無効回数の取得
 *
 * @param[in] なし
 *
 * @return ダメージ無効回数
 */
const int Character::GetInvincibleCount() const
{
	return m_invincibleCount;
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

/**
 * @brief ダメージを受けた方向を設定
 *
 * @param[in] damageDirection ダメージを受けた方向
 *
 * @return なし
 */
void Character::SetDamageDirection(const DirectX::SimpleMath::Vector3& damageDirection)
{
	m_damageDirection = damageDirection;
}

/**
 * @brief ダメージフラッシュの設定
 *
 * @param[in] flash 光加減 0.0～1.0
 *
 * @return なし
 */
void Character::SetDamageFlash(const float& flash)
{
	m_damageFlash = flash;
}

/**
 * @brief ダメージフラッシュの取得
 *
 * @param[in] なし
 *
 * @return ダメージフラッシュ
 */
const float& Character::GetDamageFlash() const
{
	return m_damageFlash;
}

/**
 * @brief 移動方向の設定
 *
 * @param[in] moveFlags 移動フラグ
 *
 * @return なし
 */
void Character::SetMoveFlags(const uint32_t& moveFlags)
{
	m_moveFlags = moveFlags;
}

/**
 * @brief 移動方向の取得
 *
 * @param[in] なし
 *
 * @return 移動フラグ
 */
const uint32_t& Character::GetMoveFlags() const
{
	return m_moveFlags;
}
/**
 * @brief 所持宝石を取得
 *
 * @param[in] なし
 *
 * @return 所持宝石リスト
 */
const HolderGem& Character::GetHolderGem() const
{
	return *m_holderGem;
}
