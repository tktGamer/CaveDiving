/**
 * @file   Gem.h
 *
 * @brief  宝石に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/01/08
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include <string>
#include<memory>
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 宝石
  */
class Gem
{
// クラス定数の宣言 -------------------------------------------------
public:
	//空白を表すID
	static constexpr int BLANK_ID = -1;
	//強化する項目
	enum class Type
	{
		HP = 0, //体力
		STR,    //攻撃力
		DEF,    //防御力
		UNIQUE, //特殊
	};
	//宝石の情報
	struct GemAbility
	{
		int id; //データ番号
		std::string type; // 宝石の種類
		Type powerUp; // 宝石の強化項目
		int value; // 宝石の効果値
		int interval; //効果適用間隔
	};

	//文字画像
	struct GemImagePath
	{
		//宝石の画像パス
		const wchar_t* panel;
	};

// データメンバの宣言 -----------------------------------------------
private:
	// 宝石の画像のパス
	GemImagePath m_gemImage; 
	// 宝石の能力値
	GemAbility m_ability; 
	// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Gem(const GemAbility& ability, const GemImagePath& image);
	Gem(const Gem& other) = default;

	// デストラクタ
	virtual ~Gem();


//操作
public:
	//宝石のコピー
	virtual std::unique_ptr<Gem> Clone() const = 0;
//取得・設定
public:
	//宝石情報の取得
	const GemAbility& GetAbility() const;
	//取得選択時の画像パス取得
	const GemImagePath& GetImagePath() const;
//内部操作
private:

};

