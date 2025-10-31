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
class UserResources
{
public:
	enum Stage
	{
		FIRST,
		BOSS
	};
private:
	//ゲームをクリアしたか
	bool m_isGameClear;
	//プレイヤーのステージクリア時HP
	int m_playerHP;
	//次のステージ
	Stage m_nextStage;
	//ステージで灯した明かり
	bool m_isOnLights[10];
public:

	// コンストラクタ
	UserResources()
		:m_isGameClear{false}
		,m_nextStage{Stage::FIRST}
		,m_playerHP{}
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

	void SetNextStage(const Stage& nextStage) 
	{
		m_nextStage = nextStage;
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

