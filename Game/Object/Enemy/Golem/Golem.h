/**
 * @file   Golem.h
 *
 * @brief  ゴーレムボスに関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 * 
 * @date   日付  2026/01/07
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include "Game/Object/Character.h"
#include"Game/Common/Collision/Box.h"

#include"../Golem/State/GolemIdling.h"
#include"../Golem/State/GolemAttack.h"
#include"../Golem/State/GolemMoving.h"
#include"../Golem/State/GolemChasing.h"
#include"../Golem/State/GolemAttackPreparing.h"
#include"../Golem/State/GolemDamaged.h"
 
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
	enum Mode 
	{
		Normal,
		Angry,
	};
	//初期HP
	static constexpr int GOLEM_BASE_HP = 150;
	//初期攻撃力
	static constexpr int GOLEM_BASE_ATTACK = 70;
	//初期防御力
	static constexpr int GOLEM_BASE_DIFFENCE = 20;
	//球の当たり判定サイズ
	static constexpr float GOLEM_SPHERE_SIZE = 4.0f;

	//接触時のダメージ割りあい
	static constexpr float CONTACT_DAMAGE_MODIFIRE = 0.1f;
	//感知範囲
	static constexpr  float CHASE_RANGE = 20.0f;

	//左手の位置
	static constexpr DirectX::SimpleMath::Vector3 LEFTHAND_INIT_POS = { -4.5f ,2.0f,0.0f };
	//右手の位置
	static constexpr DirectX::SimpleMath::Vector3 RIGHTHAND_INIT_POS = { 4.5f ,2.0f,0.0f };
	static constexpr float LEFT_HAND_INIT_ANGLE = DirectX::XMConvertToRadians(180.0f);
private:
	//ゴーレムのアウトラインの太さ
	static constexpr  float GOLEM_OUTLINE_THICKNESS = 0.04f;

// データメンバの宣言 -----------------------------------------------
private:

	// メッセージID
	Message::MessageID m_messageID;

	//当たり判定
	Box m_box;


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
	Golem(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~Golem();

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

	const DirectX::SimpleMath::Quaternion& GetMotionAngle() const;
	void SetMotionAngle(const DirectX::SimpleMath::Quaternion& angle);

	//攻撃メッセージ
	const Message::AttackMesssage GetAttackMessage() const;
	void SetAttackMessage(const Message::AttackMesssage& message);
//　内部操作
private:

};

