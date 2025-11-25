/**
 * @file   Bat.h
 *
 * @brief  コウモリの敵に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 * 
 * @date   日付  2025/09/04
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
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief Bat
  */
class Bat :public Character
{
// クラス定数の宣言 -------------------------------------------------
public:
	static constexpr DirectX::SimpleMath::Vector3 LEFTWING_INIT_POS  = { -0.5f,0.0f,0.0f };
	static constexpr DirectX::SimpleMath::Vector3 RIGHTWING_INIT_POS = {  0.5f,0.0f,0.0f };
	static constexpr float RIGHT_WING_INIT_DEGREE = 180.0f;

	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4 color;

	};


// データメンバの宣言 -----------------------------------------------
private:
	Graphics* m_graphics;	// グラフィックスクラスのポインタ

	// メッセージID
	Message::MessageID m_messageID;

	//当たり判定
	Sphere m_sphere;

	DirectX::SimpleMath::Vector3 m_velocity; // 速度 

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
	float m_frameCount=0;

	DirectX::SimpleMath::Quaternion m_motionAngle;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Bat(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

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

	DirectX::SimpleMath::Quaternion GetMotionAngle();
	void SetMotionAngle(DirectX::SimpleMath::Quaternion angle);


	DirectX::SimpleMath::Vector3 GetVelocity();
	void SetVelocity(DirectX::SimpleMath::Vector3 v);
//　内部操作
private:

};

