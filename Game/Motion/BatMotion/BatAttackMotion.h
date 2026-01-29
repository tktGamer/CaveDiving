/**
 * @file   BatAttackMotion.h
 *
 * @brief  コウモリの攻撃のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/18
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../AttackMotion.h"
// クラスの宣言 ===============================================================
class Bat;
class Wing;
// クラスの定義 ===============================================================
/**
  * @brief コウモリの攻撃のモーション
  */
class BatAttackMotion : public AttackMotion
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//モーションの攻撃力補正値
	static constexpr float BAT_ATTACK_MOTION_MODIFIER = 1.0f;
	//コウモリの姿勢
	static constexpr float BAT_ATTACK_MOTION_INIT_ANGLE = DirectX::XMConvertToRadians(-20.0f);
	//右羽の姿勢
	static constexpr float RIGHT_WING_ATTACK_MOTION_INIT_ANGLE = DirectX::XMConvertToRadians(-15.0f);;
	//左羽の姿勢
	static constexpr float LEFT_WING_ATTACK_MOTION_INIT_ANGLE = DirectX::XMConvertToRadians(15.0f);;
	//突進速度
	static constexpr float BAT_ATTACK_SPEED = 15.0f;
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	BatAttackMotion(Bat* pBat, Wing* pRightWing, Wing* pLeftWing);
	// デストラクタ
	~BatAttackMotion();
// 操作
	//初期化
	void Initialize();
	//更新
	bool Update();
	//リセット
	void Reset();
//　内部操作
private:
// データメンバの宣言 -----------------------------------------------
private:
	//コウモリのポインタ
	Bat* m_pBat;
	//右手のポインタ
	Wing* m_pRightWing;
	//左手のポインタ
	Wing* m_pLeftWing;
};

