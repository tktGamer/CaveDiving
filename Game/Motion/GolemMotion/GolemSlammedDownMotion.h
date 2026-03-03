/**
 * @file   GolemSlammedDownMotion.h
 *
 * @brief  叩きつけの攻撃のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/02
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../AttackMotion.h"
#include"Game/Object/Enemy/Golem/Golem.h"
#include"Game/Object/Enemy/Golem/GolemHand.h"
// クラスの宣言 ===============================================================
class Sound;
class GolemHand;
class GolemArm;
// クラスの定義 ===============================================================
/**
  * @brief 叩きつけの攻撃のモーション
  */
class GolemSlammedDownMotion : public AttackMotion
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//モーションの攻撃力補正値
	static constexpr float GOLEM_SLAMMED_DOWN_MOTION_MODIFIER = 1.5f;
	//クールタイム
	static constexpr float COOL_TIME = 0.5f;
	//拳の移動量
	static constexpr DirectX::SimpleMath::Vector3 SLAMMED_DOWN_MOVE = { -0.0f,-8.0f,0.0f };
	//モーションスピード
	static constexpr float SLAMMED_MOTION_SPEED = 2.0f;
	//モーション開始角度
	static constexpr float ARM_START_MOTION_X_ANGLE = DirectX::XMConvertToRadians(140.0f);
	//モーション終了角度
	static constexpr float ARM_END_MOTION_X_ANGLE = DirectX::XMConvertToRadians(75.0f);

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	GolemSlammedDownMotion(const int& golemObjectID);
	// デストラクタ
	~GolemSlammedDownMotion();
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
	//右手のポインタ
	GolemHand* m_pRightGolemHand;
	//左腕のポインタ
	GolemArm* m_pLeftGolemArm;
	//左手のポインタ
	GolemHand* m_pLeftGolemHand;

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

