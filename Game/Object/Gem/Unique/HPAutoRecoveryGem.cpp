/**
 * @file   HPAutoRecoveryGem.cpp
 *
 * @brief  宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/19
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "HPAutoRecoveryGem.h"
#include"Game/Message/Messenger.h"
#include"Game/Factory/GemFactory.h"
#include"Game/Particle/ParticleManager.h"
#include"Game/Object/Character.h"
//ファクトリクラスへの登録
REGISTER_GEM_CLASS("HPAutoRecoveryGem", HPAutoRecoveryGem);

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] ability  宝石の詳細
 * @param[in] image 　 選択時の画像
 */
HPAutoRecoveryGem::HPAutoRecoveryGem(const GemAbility& ability, const GemImagePath& image)
	:
	Gem{ability,image}
{
}

/**
 * @brief デストラクタ
 */
HPAutoRecoveryGem::~HPAutoRecoveryGem()
{
}

/**
 * @brief 多態コピー
 *
 * @param[in] なし
 *
 * @return コピー
 */
std::unique_ptr<Gem> HPAutoRecoveryGem::Clone() const
{
	return std::make_unique<HPAutoRecoveryGem>(*this);
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void HPAutoRecoveryGem::Initialize()
{
	//タイマーリセット
	m_recoveryIntervalTimer = RESET;
}


/**
 * @brief 毎フレーム更新効果
 *
 * @param[in] owner  宝石の所有者
 *
 * @return なし
 */
void HPAutoRecoveryGem::OnUpdate(Character& owner)
{
	int heal = RecoveryHP();
	if (heal <= NO_HEAL) return;
	//所有者を回復させる
	owner.SetCurrentHP(std::min(owner.GetCurrentHP() + heal, owner.GetMaxHP()));
	//回復エフェクトを出す
	ParticleManager::GetInstance()->RequestHPHealParticle(owner.GetCurrentPosition());
}

/**
 * @brief HP回復
 *
 * @param[in] なし
 *
 * @return 回復量
 */
int HPAutoRecoveryGem::RecoveryHP()
{
	//タイマー進行
	m_recoveryIntervalTimer += Messenger::GetInstance()->GetElapsedTime();
	//回復間隔に達していなかったら処理を飛ばす
	if (m_recoveryIntervalTimer <= GetAbility().interval) 
	{
		return NO_HEAL;
	}
	//タイマーリセット
	m_recoveryIntervalTimer = RESET;

	//回復量を返す
	return GetAbility().value;
}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void HPAutoRecoveryGem::Finalize()
{
}