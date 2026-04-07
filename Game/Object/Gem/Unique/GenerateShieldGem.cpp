/**
 * @file   GenerateShieldGem.cpp
 *
 * @brief  盾生成宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/19
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GenerateShieldGem.h"
#include"Game/Message/Messenger.h"
#include"Game/Factory/GemFactory.h"
#include"Game/Particle/ParticleManager.h"
#include"Game/Object/Character.h"
//ファクトリクラスへの登録
REGISTER_GEM_CLASS("GenerateShieldGem", GenerateShieldGem);

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] ability  宝石の詳細
 * @param[in] image 　 選択時の画像
 */
GenerateShieldGem::GenerateShieldGem(const GemAbility& ability, const GemImagePath& image)
	:
	Gem{ ability,image }
{
}

/**
 * @brief デストラクタ
 */
GenerateShieldGem::~GenerateShieldGem()
{
}

/**
 * @brief 多態コピー
 *
 * @param[in] なし
 *
 * @return コピー
 */
std::unique_ptr<Gem> GenerateShieldGem::Clone() const
{
	return std::make_unique<GenerateShieldGem>(*this);
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GenerateShieldGem::Initialize()
{
}

/**
 * @brief 毎フレーム更新効果
 *
 * @param[in] owner  宝石の所有者
 *
 * @return なし
 */
void GenerateShieldGem::OnUpdate(Character& owner)
{
	//盾を生成
	int shield = GenerateShield();
	if (shield == NO_SHILD)
	{
		return;
	}
	owner.AddInvincibleCount(shield);
	//盾エフェクト生成
	ParticleManager::GetInstance()->RequestShieldParticle(owner.GetObjectNumber());

}

/**
 * @brief 盾生成
 *
 * @param[in] なし
 *
 * @return 攻撃無効の回数
 */
int GenerateShieldGem::GenerateShield()
{
	m_generateIntervalTimer += Messenger::GetInstance()->GetElapsedTime();
	//生成間隔に達していなかったら処理を飛ばす
	if (m_generateIntervalTimer <= GetAbility().interval)
	{
		return 0;
	}

	m_generateIntervalTimer = 0.0f;

	//値分攻撃無効
	return GetAbility().value;
}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GenerateShieldGem::Finalize()
{
}