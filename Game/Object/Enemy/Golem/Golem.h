/**
 * @file   Golem.h
 *
 * @brief  ゴーレムボスに関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 * 
 * @date   日付  2025/09/12
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include "Game/Object/Character.h"
#include"Game/Common/Collision/Sphere.h"

#include"../Golem/State/GolemIdling.h"
#include"../Golem/State/GolemAttack.h"
#include"../Golem/State/GolemMoving.h"
#include"../Golem/State/GolemChasing.h"
#include"../Golem/State/GolemAttackPreparing.h"
//#include"../Golem/State/GolemDamaged.h"
 
#include"../EnemyPart.h"
#include"../Golem/GolemHand.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief ゴーレムボス敵
  */
class Golem :public Character
{
// クラス定数の宣言 -------------------------------------------------
public:
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
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
	std::unique_ptr<IState> m_damagedState;


	//手
	std::unique_ptr<GolemHand> m_rightHand; //
	std::unique_ptr<GolemHand> m_leftHand;//

	std::unique_ptr<GameObject> m_part;

	//経過時間
	float m_frameCount=0;

	DirectX::SimpleMath::Quaternion m_motionAngle;


	Ito::DisplayCollision m_display;

	Message::AttackMesssage m_attackMessage;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Golem(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~Golem();


	void Initialize();

	void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

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

	//攻撃メッセージ
	const Message::AttackMesssage GetAttackMessage();
	void SetAttackMessage(const Message::AttackMesssage& message);
	//　内部操作
private:

};

