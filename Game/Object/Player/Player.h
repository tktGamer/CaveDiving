/**
 * @file   Player.h
 *
 * @brief  自キャラに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/Object/GameObject.h"
#include"Game/Object/Character.h"
#include "Game/Object/Gem/Gem.h"
#include "Game/Object/Light.h"
#include"../Player/State/PlayerIdling.h"
#include"../Player/State/PlayerMoving.h"
#include"../Player/State/PlayerAttack.h"
#include"../Player/State/PlayerJumping.h"
#include"../Player/State/PlayerAvoidance.h"
#include"Game/Common/Collision/Sphere.h"
#include "Game/Object/Player/Hand.h"
// クラスの宣言 ===============================================================
class IState;
// クラスの定義 ===============================================================
/**
  * @brief プレイヤー
  */
class Player : public Character
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

	// メッセージID
	Message::MessageID m_messageID;


	DirectX::SimpleMath::Vector3 m_velocity; // 速度 

	std::unique_ptr<Light> m_light;

	//当たり判定
	Sphere m_sphere;
	//状態
	std::unique_ptr<IState> m_pCurrentState; // 現在の状態
	std::unique_ptr<IState> m_idlingState; // 待機状態 
	std::unique_ptr<IState> m_movingState; // 移動状態
	std::unique_ptr<IState> m_attackState; // 攻撃状態
	std::unique_ptr<IState> m_jumpingState; // ジャンプ状態
	std::unique_ptr<IState> m_avoidState; // 回避状態

	// プレイヤーの体のパーツ
	std::vector<std::unique_ptr<GameObject>> m_bodyParts; 
	//プレイヤーの向き
	DirectX::SimpleMath::Vector3 m_initialeDirection;

	//重力
	float m_gravity = 9.8f; // 重力加速度

	//ジャンプできる残り回数
	int m_remainingJumpCount;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Player(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// デストラクタ
	~Player();


// 操作
public:
	void Initialize();

	void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

	void Finalize();

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);
	//衝突応答分岐
	void CollisionResponce(GameObject* other) override;

//　取得・設定
public:
	
	DirectX::SimpleMath::Vector3 GetVelocity();
	void SetVelocity(DirectX::SimpleMath::Vector3 v);

	// 体力の取得
	const int& GetMaxHP() override;
	// 攻撃力の取得
	const int GetAttackPower() override;
	// 防御力の取得
	const int GetDiffence() override;

	//ジャンプ出来る残り回数取得
	const int GetRemainingJumpCount() const;
	//ジャンプ出来る残り回数減少
	bool ReduceJumpCount();
	//ジャンプ出来る残り回数をリセット
	void ResetJumpCount();
//　内部操作
private:
	//方向転換
	void ChangeDirection();
	//宝石で強化された分のステータスを取得
	int GetPlusStatus(const Gem::Type type);
};

