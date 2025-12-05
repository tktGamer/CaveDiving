/**
 * @file   GameData.h
 *
 * @brief  シーンをまたいでも保持したいデータの管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/12
 */

 // 多重インクルードの防止 =====================================================
#pragma once



// 各シーンに渡す共通リソースを記述してください
class GameData
{
public:
	enum  Stage :int
	{
		NONE,
		FIRST,
		//SECOND,
		//THIRD,
		BOSS
	};
private:
	//与えたトータルダメージ
	int m_totalDamage;
	//クリアタイム
	float m_clearTime;
	//ゲームをクリアしたか
	bool m_isGameClear;
	//プレイヤーのステージクリア時HP
	int m_playerHP;
	//次のステージ
	Stage m_nextStage;
	//ステージをクリアしたか
	bool m_isStageClear;
	//ステージで灯した明かり
	bool m_isOnLights[10];
public:

	// コンストラクタ
	GameData()
		:m_isGameClear{false}
		,m_isStageClear{false}
		,m_nextStage{Stage::FIRST}
		,m_playerHP{}
		,m_totalDamage{0}
		,m_clearTime{0.0f}
		,m_isOnLights{false}
	{
	}


	const bool IsGameClear() const  
	{
		return m_isGameClear;
	}

	void SetIsGameClear(const bool& isGameClear) 
	{
		m_isGameClear = isGameClear;

		//ライトをすべて消す
		for (int i = 0; i < 10; i++)
		{
			m_isOnLights[i] = false;
		}
	}
	const bool IsStageClear() const  
	{
		return m_isStageClear;
	}

	void SetIsStageClear(const bool& isStageClear) 
	{
		m_isStageClear = isStageClear;

	}

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


	const Stage GetNextStage() const
	{
		return m_nextStage;
	}

	void SetIsOnLightNumber(bool isOn, int number)
	{

		m_isOnLights[number] = isOn;
	}



	bool* GetIsOnLights()
	{
		return m_isOnLights;
	}
};

