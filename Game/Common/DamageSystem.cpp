/**
 * @file   DamageSystem.cpp
 *
 * @brief  ダメージシステムに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/08/29
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "DamageSystem.h"

// クラスの静的メンバ変数の初期化
std::unique_ptr<DamageSystem> DamageSystem::s_damageSystem = nullptr;

// メンバ関数の定義 ===========================================================
/**
 * @brief インスタンスを取得する
 *
 * @param[in] なし
 *
 * @return 当たり判定管理クラスのポインタ
 */
DamageSystem* const DamageSystem::GetInstance()
{
	//一度も生成されていなかったら
	if (s_damageSystem == nullptr)
	{
		//ResourceManagerオブジェクトを生成し、そのポインタをs_collisionManagerに格納する
		s_damageSystem.reset(new DamageSystem());
	}
	return s_damageSystem.get();
}
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
DamageSystem::DamageSystem()
{

}



/**
 * @brief デストラクタ
 */
DamageSystem::~DamageSystem()
{

}




/**
 * @brief ダメージ処理
 *
 * @param[in] attacker 攻撃側
 * @param[in] defender 防御側
 *
 * @return ダメージ量
 */
int DamageSystem::DamageToCharacter(Character* attacker, Character* defender)
{
	int attackerPower = attacker->GetAttackPower();
	int defenderDiffence = defender->GetDiffence();
	
	int damage = DamageCalculation(attackerPower, defenderDiffence);

	defender->TakeDamage(damage);

	return damage;
}

/**
 * @brief ダメージ計算
 *
 * @param[in] attackPower 攻撃力
 * @param[in] diffence 　 防御力
 *
 * @return ダメージ
 */
int DamageSystem::DamageCalculation(const int attackPower, const int diffence)
{
	///要改良///
	int damage = attackPower / 2 - diffence/ 4 ;

	//０より大きいならdamageを返す
	return std::max(damage,0);
}

