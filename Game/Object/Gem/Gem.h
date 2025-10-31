/**
 * @file   Gem.h
 *
 * @brief  宝石に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/08/27
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#include <string>

// ヘッダファイルの読み込み ===================================================

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 宝石
  */
class Gem
{
// クラス定数の宣言 -------------------------------------------------
public:
	enum class Type
	{
		HP = 0, //体力
		STR,    //攻撃力
		DEF,    //防御力
		UNIQUE, //特殊
	};

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
	// 宝石の種類と効果値を指定して初期化
	Gem(int id,std::string type, Type powerUp,int value);
	Gem(GemAbility ability,GemImagePath image);

	// デストラクタ
	virtual ~Gem();


//操作
public:
	void Initialize();

	virtual void ApplyEffect();

	void Finalize();
//取得・設定
public:
	GemAbility GetAbility() const;
	GemImagePath GetImagePath() const;
//内部操作
private:

};

