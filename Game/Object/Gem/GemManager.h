/**
 * @file   GemManager.h
 *
 * @brief  宝石の管理に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"Game/Object/Gem/Gem.h"
#include<fstream>
#include<sstream>
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief GemManager
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
		// 説明
		std::string description;	

		//宝石の画像パス
		std::string  gem;
		//名前の画像パス
		std::string  name;
		//説明の画像パス
		std::string  explanation;

	};

// データメンバの宣言 -----------------------------------------------
private:
	// GemManagerクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<GemManager> s_gemManager;

	Graphics* m_graphics;	// グラフィックスクラスのポインタ

	std::vector<std::unique_ptr<Gem>> m_gemList;	// 宝石のリスト
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

	//ランダムに宝石を選択する
	Gem* RandomSelection();
//　取得・設定
public:
	//宝石の種類を決定する
	Gem::Type DecisinType(const std::string& type);
//　内部操作
private:
};

