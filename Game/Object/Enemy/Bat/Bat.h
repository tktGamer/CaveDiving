/**
 * @file   Bat.h
 *
 * @brief  コウモリの敵に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include "Game/Object/Character.h"
#include"Game/Common/Collision/Sphere.h"
#include "../Bat/Wing.h"
#include"Game/Object/Enemy/Bat/State/BatIdling.h"
#include"Game/Object/Enemy/Bat/State/BatAttack.h"
#include"Game/Object/Enemy/Bat/State/BatMoving.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief Bat
  */
class Bat :public Character
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

	// オブジェクト番号
	int m_objectNumber;
	// メッセージID
	Message::MessageID m_messageID;

	//当たり判定
	Sphere m_sphere;

	DirectX::SimpleMath::Vector3 m_velocity; // 速度 

	//生きているか
	bool m_isAlive;

	//状態
	std::unique_ptr<IState> m_pCurrentState; // 現在の状態
	std::unique_ptr<IState> m_idlingState; // 待機状態 
	std::unique_ptr<IState> m_movingState; // 移動状態
	std::unique_ptr<IState> m_attackState; // 攻撃状態

	//羽
	std::unique_ptr<Wing> m_rightWing; //右翼
	std::unique_ptr<Wing> m_leftWing;//左翼
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Bat(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// デストラクタ
	~Bat();


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

	int GetObjectNumber() override;
	DirectX::SimpleMath::Vector3 GetVelocity();
	void SetVelocity(DirectX::SimpleMath::Vector3 v);
	//生きているか
	bool IsAlive() const;
	//　内部操作
private:

};

