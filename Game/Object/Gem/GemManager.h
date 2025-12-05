/**
 * @file   GemManager.h
 *
 * @brief  宝石の管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/10/22
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"Game/Object/Gem/Gem.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 宝石管理
  */
class GemManager
{
// クラス定数の宣言 -------------------------------------------------
public:
	//宝石データ項目
	struct GemData
	{
		// ID
		int id=0;		
		// 種類
		std::string type;	
		//強化項目
		std::string item;   
		// 効果
		int			effect=0;		
		//効果適用間隔
		int interval=0;

		// 説明
		std::string description;	

		//宝石の画像パス
		std::string  gem;
		//名前の画像パス
		std::string  name;
		//説明の画像パス
		std::string  explanation;

	};

	static constexpr int PLAYER_HOLD_GEM_NUM = 3;
// データメンバの宣言 -----------------------------------------------
private:
	// GemManagerクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<GemManager> s_gemManager;


	// 宝石の配列
	std::vector<std::unique_ptr<Gem>> m_gemList;	

	//プレイヤーの持つジェム
	Gem* m_playerKeepGem[PLAYER_HOLD_GEM_NUM];

	//入れ替え予定の宝石
	Gem* m_pReplacementGem;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GemManager();
	// インスタンスをコピーすることを禁止する
	void operator=(const GemManager&) = delete;
	// インスタンスをムーブすることを禁止する
	GemManager& operator= (GemManager&&) = delete;
	// コピーコンストラクタは禁止する
	GemManager(const GemManager&) = delete;
	// ムーブコンストラクタは禁止する
	GemManager(GemManager&&) = delete;


	// デストラクタ
	~GemManager();


// 操作
public:
	// GemManagerクラスのインスタンスを取得する
	static GemManager* const GetInstance();

	// 宝石データの読み込み
	void LoadGemData();

	void Update();


	void Finalize();

	//ランダムに宝石を取得する
	Gem* RandomSelection();

	//プレイヤーの所持している宝石を外部ファイルに保存
	bool SavePlayerHoldGem();

	//プレイヤーの所持している宝石を外部ファイルから読み込み
	bool LoadPlayerHoldGem();

	//プレイヤーの所持している宝石を空にする
	void EmptyPlayerHoldGem();
//　取得・設定
public:
	//id番の宝石を取得
	Gem* GetIDNumberedGem(const int& id);

	//空のスロットがあるか
	bool IsBlankSlot() const;

	//プレイヤーの持つ宝石を取得
	const Gem* const* GetPlayerHoldGem() const;

	//指定の宝石をもっているか
	template<typename T>
	std::vector<T*>  IsHasGem();

	//プレイヤーの持つ宝石をセット
	void SetHoldGem(Gem* pGem, int index=-1);

	//入れ替え先の宝石の設定
	void SetReplacementGem(Gem* pGem);

	//入れ替え先の宝石の取得
	Gem* GetReplacementGem();
//　内部操作
private:
	//宝石の種類を決定する
	Gem::Type DecisinType(const std::string& type);
};

template<typename T>
inline std::vector<T*> GemManager::IsHasGem()
{
	std::vector<T*> result;

	for (int i = 0; i < PLAYER_HOLD_GEM_NUM; ++i)
	{
		if (auto gem = m_playerKeepGem[i])
		{
			if (auto targetGem = dynamic_cast<T*>(gem))
			{
				//T型のGemを追加
				result.push_back(targetGem);
			}
		}
	}
	return result;
}
