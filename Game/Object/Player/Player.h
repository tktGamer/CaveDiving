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
#include "Game/Object/Gem/Gem.h"
#include "Game/Object/Light.h"
#include"Game/Object/Player/State/PlayerIdling.h"
#include"Game/Object/Player/State/PlayerMoving.h"
#include"Game/Object/Player/State/PlayerAttack.h"
#include"Game/Common/Collision/Sphere.h"
#include "Game/Object/Player/Hand.h"
// クラスの宣言 ===============================================================
class IState;
// クラスの定義 ===============================================================
/**
  * @brief Player
  */
class Player : public GameObject
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

	// オブジェクト番号
	int m_objectNumber;
	// メッセージID
	Message::MessageID m_messageID;

	Gem* m_pGem[3]; // 所持している宝石
	DirectX::SimpleMath::Vector3 m_velocity; // 速度 

	//ステータス
	int m_hp; // HP
	int m_power; // 攻撃力
	int m_diffence; // 防御力
	std::unique_ptr<Light> m_light;

	//当たり判定
	Sphere m_sphere;
	//状態
	std::unique_ptr<IState> m_pCurrentState; // 現在の状態
	std::unique_ptr<IState> m_idlingState; // 待機状態 
	std::unique_ptr<IState> m_movingState; // 移動状態
	std::unique_ptr<IState> m_attackState; // 攻撃状態

	// プレイヤーの体のパーツ
	std::vector<std::unique_ptr<GameObject>> m_bodyParts; 
	//プレイヤーの向き
	DirectX::SimpleMath::Vector3 m_initialeDirection;

	//重力
	float m_gravity = 9.8f; // 重力加速度
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

//　取得・設定
public:
	
	//宝石をセット
	void SetGem(Gem* gem,int index);
	int GetObjectNumber() override;
	DirectX::SimpleMath::Vector3 GetVelocity();
	void SetVelocity(DirectX::SimpleMath::Vector3 v);
//　内部操作
private:

};

