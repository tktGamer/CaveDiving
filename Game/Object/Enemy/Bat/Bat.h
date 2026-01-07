/**
 * @file   Bat.h
 *
 * @brief  コウモリの敵に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 * 
 * @date   日付  2026/01/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include "Game/Object/Character.h"
#include"Game/Common/Collision/Sphere.h"
#include "../Bat/Wing.h"
#include"../Bat/State/BatIdling.h"
#include"../Bat/State/BatAttack.h"
#include"../Bat/State/BatMoving.h"
#include"../Bat/State/BatChasing.h"
#include"../Bat/State/BatAttackPreparing.h"
#include"../Bat/State/BatDamaged.h"
#include"Game/Shader/Outline/OutlineRenderer.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief コウモリの敵
  */
class Bat :public Character
{
// クラス定数の宣言 -------------------------------------------------
public:
	//初期体力
	static constexpr int BAT_BASE_HP = 40;
	//初期攻撃力
	static constexpr int BAT_BASE_ATTACK = 30;
	//初期防御力
	static constexpr int BAT_BASE_DIFFENCE = 8;
	//球の当たり判定サイズ
	static constexpr float BAT_SPHERE_SIZE = 2.0f;

	//左羽の位置
	static constexpr DirectX::SimpleMath::Vector3 LEFTWING_INIT_POS  = { -0.5f,0.0f,0.0f };
	//右羽の位置
	static constexpr DirectX::SimpleMath::Vector3 RIGHTWING_INIT_POS = {  0.5f,0.0f,0.0f };
	static constexpr float RIGHT_WING_INIT_ANGLE = DirectX::XMConvertToRadians(180.0f);


	//接触時のダメージ割りあい
	static constexpr float CONTACT_DAMAGE_MODIFIRE = 0.1f;

	//感知範囲
	static constexpr  float CHASE_RANGE = 15.0f;

	//コウモリのアウトラインの太さ
	static constexpr  float BAT_OUTLINE_THICKNESS = 0.04f;
	
// データメンバの宣言 -----------------------------------------------
private:

	// メッセージID
	Message::MessageID m_messageID;

	//当たり判定
	Sphere m_sphere;


	//状態
	std::unique_ptr<IState> m_pCurrentState; // 現在の状態
	std::unique_ptr<IState> m_idlingState; // 待機状態 
	std::unique_ptr<IState> m_movingState; // 移動状態
	std::unique_ptr<IState> m_attackState; // 攻撃状態
	std::unique_ptr<IState> m_chasingState; //追跡状態
	std::unique_ptr<IState> m_attackPreaparing; //攻撃準備状態
	std::unique_ptr<IState> m_damagedState;//ダメージ状態
	//羽
	std::unique_ptr<Wing> m_rightWing; //右翼
	std::unique_ptr<Wing> m_leftWing;//左翼

	//経過時間
	float m_frameCount = 0;

	DirectX::SimpleMath::Quaternion m_motionAngle;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Bat(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~Bat();

	//初期化
	void Initialize();
	//更新
	void Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;

	//描画
	void Draw() override;

	//終了
	void Finalize();

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);
	//衝突応答分岐
	void CollisionResponce(GameObject* other);

//　取得・設定
public:
	//経過時間取得
	const float GetFrameCount() const ;
	//経過時間リセット
	void ResetFrameCount();

	//モーション用角度取得
	const DirectX::SimpleMath::Quaternion& GetMotionAngle() const;
	//モーション用角度設定
	void SetMotionAngle(const DirectX::SimpleMath::Quaternion& angle);


//　内部操作
private:

};

