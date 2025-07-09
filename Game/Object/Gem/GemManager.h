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
		int id=0;		// 名前
		std::string type;	// 種類
		std::string item;   //強化項目
		int			effect=0;		// 効果
		std::string description;	// 説明
	};

// データメンバの宣言 -----------------------------------------------
private:
	Graphics* m_graphics;	// グラフィックスクラスのポインタ

	std::vector<std::unique_ptr<Gem>> m_gemList;	// 宝石のリスト
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GemManager();

	// デストラクタ
	~GemManager();


// 操作
public:
	void Initialize();

	void Update();

	void Draw();

	void Finalize();

	
//　取得・設定
public:
	//宝石の種類を決定する
	Gem::Type DecisinType(const std::string& type);
//　内部操作
private:
	// 宝石データの読み込み
	void LoadGemData();
};

