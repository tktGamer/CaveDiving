/**
 * @file   HPAutoRecoveryGem.cpp
 *
 * @brief  宝石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/10/27
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "HPAutoRecoveryGem.h"
#include"Game/Message/Messenger.h"
#include"Game/Factory/GemFactory.h"
#include"Game/Particle/ParticleManager.h"
//ファクトリクラスへの登録
REGISTER_GEM_CLASS("HPAutoRecoveryGem", HPAutoRecoveryGem);

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] type  宝石の種類
 * @param[in] powerUp 宝石の強化項目
 * @param[in] value 宝石の効果値
 */
HPAutoRecoveryGem::HPAutoRecoveryGem(int id, std::string type, Type powerUp, int value)
	:Gem{id,type,powerUp,value}
	,m_recoveryIntervalTimer{0.0f}
{
}

HPAutoRecoveryGem::HPAutoRecoveryGem(GemAbility ability, GemImagePath image)
	:Gem{ability,image}
	,m_recoveryIntervalTimer{0.0f}
{
}




/**
 * @brief デストラクタ
 */
HPAutoRecoveryGem::~HPAutoRecoveryGem()
{

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
	m_recoveryIntervalTimer += Messenger::GetInstance()->GetElapsedTime();
	//回復間隔に達していなかったら処理を飛ばす
	if (m_recoveryIntervalTimer <= GetAbility().interval) 
	{
		return 0;
	}

	m_recoveryIntervalTimer = 0.0f;

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


