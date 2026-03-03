/**
 * @file   GolemWalkMotion.h
 *
 * @brief  ゴーレムの歩行モーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/03
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Motion.h"
#include"Game/Object/Enemy/Golem/Golem.h"
// クラスの宣言 ===============================================================
class Sound;
class GolemArm;
class GolemFot;
// クラスの定義 ===============================================================
/**
  * @brief 叩きつけの攻撃のモーション
  */
class GolemWalkMotion : public Motion
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//モーションのZ軸座標
	static constexpr float MOTION_Z_POS_MIN = -1.06f;
	static constexpr float MOTION_Z_POS_MAX = 1.1f;
	//モーションスピード
	static constexpr float WALK_MOTION_SPEED = 2.0f;
	//モーション開始角度
	static constexpr float ARM_START_MOTION_X_ANGLE = DirectX::XMConvertToRadians(140.0f);
	//モーション終了角度
	static constexpr float ARM_END_MOTION_X_ANGLE = DirectX::XMConvertToRadians(75.0f);

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	GolemWalkMotion(const int& golemObjectID);
	// デストラクタ
	~GolemWalkMotion();
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
	//ゴーレム本体のポインタ
	Golem* m_pGolem;
	//右腕のポインタ
	GolemArm* m_pRightGolemArm;
	//左腕のポインタ
	GolemArm* m_pLeftGolemArm;
	//右足のポインタ
	GolemFot* m_pRightGolemFot;
	//左足のポインタ
	GolemFot* m_pLeftGolemFot;
	//モーション方向 + -
	int m_operate;

	//腕の開始角度
	DirectX::SimpleMath::Vector3 m_startAngle;
	//拳の始まりの位置
	DirectX::SimpleMath::Vector3 m_handStartPosition;
	//拳の終わりの位置
	DirectX::SimpleMath::Vector3 m_handGoalPosition;
	//攻撃後の隙の時間
	float m_coolTime = 0.0f;
	//攻撃音
	std::unique_ptr<Sound> m_attackSound;
};

