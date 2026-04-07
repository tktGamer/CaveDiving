/**
 * @file   BatAttackPreparingMotion.h
 *
 * @brief  コウモリの攻撃準備のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Motion.h"
// クラスの宣言 ===============================================================
class Sound;
class Wing;
// クラスの定義 ===============================================================
/**
  * @brief コウモリの攻撃準備のモーション
  */
class BatAttackPreparingMotion : public Motion
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//モーションを繰り返す回数
	static constexpr int MOTION_LOOP = 3;
	//羽の角度
	static constexpr float WING_ANGLE_MIN = DirectX::XMConvertToRadians(-20.0f);
	static constexpr float WING_ANGLE_MAX = DirectX::XMConvertToRadians(20.0f);
	//モーションの速度
	static constexpr float MOTION_SPEED =  3.0f;

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	BatAttackPreparingMotion(Wing* pRightWing,Wing* pLeftWing);
	// デストラクタ
	~BatAttackPreparingMotion();
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
	//右手のポインタ
	Wing* m_pRightWing;
	//左手のポインタ
	Wing* m_pLeftWing;
	//現在のモーションの回数
	int m_numLoop = 0;
	//羽ばたきの音
	std::unique_ptr<Sound> m_wingSound;
};

