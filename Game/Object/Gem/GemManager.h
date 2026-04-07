/**
 * @file   GemManager.h
 *
 * @brief  宝石の管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/19
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
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
private:
	static constexpr char ATTACK[] = "攻撃力";
	static constexpr char DIFFENCE[] = "防御力";
	static constexpr char HP[] = "体力";

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//id番の宝石を取得
	const Gem* GetIDNumberedGem(const int& id);
// デストラクタ
	~GemManager();
// 操作
	// GemManagerクラスのインスタンスを取得する
	static GemManager* const GetInstance();
	// 宝石データの読み込み
	void LoadGemData();
	//ランダムに宝石を取得する
	const Gem* RandomSelection();

	//所持している宝石を外部ファイルに保存
	bool SaveHoldGem(const std::string& savePath, const std::vector<int>& gemID);
	//所持している宝石を外部ファイルから読み込み
	bool LoadHoldGem(const std::string& loadPath, std::vector<int>& gemID);

// コンストラクタ
private:
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
//　内部操作
private:
	//宝石の種類を決定する
	Gem::Type DecisinType(const std::string& type);
// データメンバの宣言 -----------------------------------------------
private:
	// GemManagerクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<GemManager> s_gemManager;
	// 宝石の配列
	std::vector<std::unique_ptr<Gem>> m_gemList;
};