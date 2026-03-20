/**
 * @file   GameData.h
 *
 * @brief  シーンをまたいでも保持したいデータの管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/02/01
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#include<unordered_map>
#include<string>
#include<vector>
#include"Game/ResourcePath.h"
// 各シーンに渡す共通リソースを記述してください
class GameData
{
// クラス定数の宣言 -------------------------------------------------
public:
	//ステージ番号
	enum  Stage :int
	{
		NONE = -1,
		FIRST,
		SECOND,
		THIRD,
		FORTH,
		BOSS,

		NUM,//合計ステージ数
	};
	//ステージに対応した敵生成データを保持する配列
	using EnemyData = std::unordered_map<GameData::Stage, std::string>;


	//スコアに必要な情報
	struct ScoreInfo
	{
		//プレイヤーの残りHP
		int playerCurrentHp = 0;
		//プレイヤーが与えた総ダメージ
		int totalDamage = 0;
		//かかった時間
		float totalTime = 0;
	};

	//プレイヤーのデータ
	struct PlayerData 
	{
		//ステージクリア時のHP
		int currentHP = 0;
		//ステージクリア時の最大HP
		int maxHP = 0;
		//所持宝石　空欄の値で初期化
		std::vector<int> gemID = std::vector<int>(3, -1);

		bool IsBlankSlot() 
		{
			for (int i = 0; i < gemID.size(); i++) 
			{
				if (gemID[i] == -1) 
				{
					return true;
				}
			}

			return false;
		}
	};

// データメンバの宣言 -----------------------------------------------
private:
	//スコア計算に必要な情報
	ScoreInfo m_scoreInfo;
	//クリアタイム
	float m_clearTime;
	//ゲームをクリアしたか
	bool m_isGameClear;
	//次のステージ
	Stage m_nextStage;
	//ステージをクリアしたか
	bool m_isStageClear;
	//プレイヤーのデータ
	PlayerData m_playerData;
	//ステージで灯した明かり
	bool m_isOnLights[10];
	//敵生成データ
	EnemyData m_enemyData;
public:

	// コンストラクタ
	GameData()
		:
		m_isGameClear{false},
		m_isStageClear{false},
		m_nextStage{Stage::FIRST},
		m_clearTime{0.0f},
		m_isOnLights{false},
		
		m_scoreInfo{}
	{
		//ステージに対応したデータを配列に入れる
		m_enemyData.insert(std::make_pair(GameData::Stage::FIRST, ResourcePath::DATA::ENEMY_SPAWN::FIRST));
		m_enemyData.insert(std::make_pair(GameData::Stage::SECOND, ResourcePath::DATA::ENEMY_SPAWN::SECOND));
		m_enemyData.insert(std::make_pair(GameData::Stage::THIRD, ResourcePath::DATA::ENEMY_SPAWN::THIRD));
		m_enemyData.insert(std::make_pair(GameData::Stage::FORTH, ResourcePath::DATA::ENEMY_SPAWN::FORTH));
		m_enemyData.insert(std::make_pair(GameData::Stage::BOSS, ResourcePath::DATA::ENEMY_SPAWN::BOSS));
	}

	/**
	 * @brief ゲームクリアか
	 *
	 * @param[in] なし
	 *
	 * @return true  ゲームクリア
	 * @return false　まだ
	 */
	const bool IsGameClear() const  
	{
		return m_isGameClear;
	}

	/**
	 * @brief ゲームクリアを設定
	 *
	 * @param[in] isGameClear  ゲームクリアか
	 *
	 * @return なし
	 */
	void SetIsGameClear(const bool& isGameClear)
	{
		m_isGameClear = isGameClear;

		//ライトをすべて消す
		for (int i = 0; i < 10; i++)
		{
			m_isOnLights[i] = false;
		}
	}

	/**
	 * @brief ステージクリアか
	 *
	 * @param[in] なし
	 *
	 * @return true  ステージクリア
	 * @return false　未クリア
	 */
	const bool IsStageClear() const
	{
		return m_isStageClear;
	}

	/**
	 * @brief ステージクリアを設定
	 *
	 * @param[in] isStageClear  ステージクリアか
	 *
	 * @return なし
	 */
	void SetIsStageClear(const bool& isStageClear)
	{
		m_isStageClear = isStageClear;

	}

	/**
	 * @brief 次のステージを設定
	 *
	 * @param[in] nextStage  次のステージ
	 *
	 * @return なし
	 */
	void SetNextStage(const GameData::Stage& nextStage = GameData::Stage::NONE)
	{
		if (nextStage == GameData::Stage::NONE) 
		{
			// 列挙型Stageをintにキャストしてインクリメントし、Stageに戻す
			m_nextStage = static_cast<Stage>(static_cast<int>(m_nextStage) + 1);
		}
		else
		{
			m_nextStage = nextStage;
		}
	}

	/**
	 * @brief プレイヤーの情報を取得
	 *
	 * @param[in] なし
	 *
	 * @return プレイヤーの情報
	 */
	const PlayerData& GetPlayerData() const
	{
		return m_playerData;
	}

	/**
	 * @brief プレイヤーの情報を設定
	 *
	 * @param[in] data  プレイヤーの情報
	 *
	 * @return なし
	 */
	void SetPlayerData(const PlayerData& data)
	{
		//現在HP
		m_playerData.currentHP = data.currentHP;
		//最大HP
		m_playerData.maxHP = data.maxHP;
		//所持宝石ID
		m_playerData.gemID = data.gemID;
	}
	/**
	 * @brief 次のステージを取得
	 *
	 * @param[in] なし
	 *
	 * @return 次のステージ
	 */
	const GameData::Stage& GetNextStage() const
	{
		return m_nextStage;
	}

	/**
	 * @brief ライトの状態を設定
	 *
	 * @param[in] isOn  オンか
	 * @param[in] number  ライト番号
	 *
	 * @return なし
	 */
	void SetIsOnLightNumber(bool isOn, int number)
	{
		m_isOnLights[number] = isOn;
	}


	/**
	 * @brief ライトの状態配列を取得
	 *
	 * @param[in] なし
	 *
	 * @return ライトの状態配列
	 */
	bool* GetIsOnLights() 
	{
		return m_isOnLights;
	}

	/**
	* @brief スコアに必要な情報を取得
	*
	* @param[in] なし
	*
	* @return スコアに必要な情報
	*/
	const ScoreInfo& GetScoreInfo() const
	{
		return m_scoreInfo;
	}

	/**
	 * @brief 合計ダメージを設定
	 *
	 * @param[in] totalDamage  合計ダメージ
	 *
	 * @return なし
	 */
	void SetTotalDamage(const int& totalDamage)
	{
		m_scoreInfo.totalDamage = totalDamage;
	}
	/**
	 * @brief プレイヤーの現在HPを設定
	 *
	 * @param[in] currentHp  現在HP
	 *
	 * @return なし
	 */
	void SetPlayerCurrentHP(const int& currentHp)
	{
		m_scoreInfo.playerCurrentHp = currentHp;
	}
	/**
	 * @brief 経過時間を設定
	 *
	 * @param[in] totalTime  合計時間
	 *
	 * @return なし
	 */
	void SetTotalTime(const float& totalTime)
	{
		m_scoreInfo.totalTime = totalTime;
	}

	/**
	 * @brief 時間経過
	 *
	 * @param[in] elapsedTime  フレーム間時間
	 *
	 * @return なし
	 */
	void AddTime(const float& elapsedTime)
	{
		m_scoreInfo.totalTime += elapsedTime;
	}

	/**
	 * @brief 敵データの取得
	 *
	 * @param[in] なし
	 *
	 * @return 敵データ
	 */
	const std::string& GetEnemySpawnDataPath()
	{
		return m_enemyData[m_nextStage];
	}
};

