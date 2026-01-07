/**
 * @file   BatDamageMotion.h
 *
 * @brief  コウモリのダメージリアクションモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/25
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Motion.h"
// クラスの宣言 ===============================================================
class Sound;
class Bat;
// クラスの定義 ===============================================================
/**
  * @brief コウモリのダメージリアクションモーション
  */
class BatDamageMotion : public Motion
{
// クラス定数の宣言 -------------------------------------------------
private:
	//斜めに向ける角度
	static constexpr float DIAGONAL_ANGLE = DirectX::XMConvertToRadians(5.0f);
	//ダメージリアクションの1秒間の回転スピード
	static constexpr float BAT_DAMAGE_REACTION_ROTATE_SPEED = DirectX::XMConvertToRadians(360.0f);
public:

// データメンバの宣言 -----------------------------------------------
private:
	//コウモリのポインタ
	Bat* m_pBat;

	//羽音
	std::unique_ptr<Sound> m_wingSound;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	BatDamageMotion(Bat* pBat);

	// デストラクタ
	~BatDamageMotion();


// 操作
public:
	//初期化
	void Initialize();
	//更新
	bool Update();

	//リセット
	void Reset();

//　取得・設定
public:

//　内部操作
private:

};

