/**
 * @file   Gem.h
 *
 * @brief  宝石に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/19
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
// メンバ関数の宣言 -------------------------------------------------
//取得・設定
public:
	//宝石情報の取得
	const GemAbility& GetAbility() const;
	//取得選択時の画像パス取得
	const GemImagePath& GetImagePath() const;
// コンストラクタ/デストラクタ
	// コンストラクタ
	Gem(const GemAbility& ability, const GemImagePath& image);
	//コピー用
	Gem(const Gem& other) = default;
	// デストラクタ
	virtual ~Gem();
//操作
	//宝石のコピー
	virtual std::unique_ptr<Gem> Clone() const = 0;
//内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	// 宝石の画像のパス
	GemImagePath m_gemImage; 
	// 宝石の能力値
	GemAbility m_ability; 
};