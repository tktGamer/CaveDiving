/**
 * @file   Gem.h
 *
 * @brief  宝石に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

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
		Type m_type; ///< 宝石の種類
		int m_value; ///< 宝石の効果値
		std::string m_discription; ///< 宝石の効果説明

	};
// データメンバの宣言 -----------------------------------------------
private:
	GemAbility m_ability; ///< 宝石の能力値
	// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Gem();
	// 宝石の種類と効果値を指定して初期化
	Gem(Type type,int value,std::string discription);
	Gem(GemAbility ability);

	// デストラクタ
	~Gem();


//操作
public:
	void Initialize();

	void Update();

	void Draw();

	void Finalize();
//取得・設定
public:
	GemAbility GetAbility() const;
//内部操作
private:

};

