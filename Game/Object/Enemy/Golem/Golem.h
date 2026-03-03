/**
 * @file   Golem.h
 *
 * @brief  ゴーレムボスに関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 * 
 * @date   日付  2026/03/02
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
#include"../Golem/GolemArm.h"
#include"../Golem/GolemFot.h"
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
	//接触時のダメージ割りあい
	static constexpr float CONTACT_DAMAGE_MODIFIRE = 0.1f;
	//感知範囲
	static constexpr  float CHASE_RANGE = 20.0f;

	//左腕の位置
	static constexpr DirectX::SimpleMath::Vector3 GOLEM_LEFT_ARM_INIT_POS = { -4.5f ,3.0f,0.0f };
	//右腕の位置
	static constexpr DirectX::SimpleMath::Vector3 GOLEM_RIGHT_ARM_INIT_POS = { 4.5f ,3.0f,0.0f };
	static constexpr float LEFT_HAND_INIT_ANGLE = DirectX::XMConvertToRadians(180.0f);
	//足の向き
	static constexpr float FOT_INIT_ANGLE = DirectX::XMConvertToRadians(90.0f);
	//右足の位置
	static constexpr DirectX::SimpleMath::Vector3 GOLEM_RIGHT_FOT_INIT_POS = { 2.0f,-4.6f,0.0f };
	//左足の位置
	static constexpr DirectX::SimpleMath::Vector3 GOLEM_LEFT_FOT_INIT_POS =  { -2.0f,-4.6f,0.0f };

	//右腕のオブジェクト番号 ゴーレムの番号を基準に
	static constexpr int RIGHT_ARM_OBJ_NUMBER  = 1;
	//右手のオブジェクト番号 ゴーレムの番号を基準に
	static constexpr int RIGHT_HAND_OBJ_NUMBER = 2;
	//左腕のオブジェクト番号 ゴーレムの番号を基準に
	static constexpr int LEFT_ARM_OBJ_NUMBER   = 3;
	//左手のオブジェクト番号 ゴーレムの番号を基準に
	static constexpr int LEFT_HAND_OBJ_NUMBER  = 4;
	//右足のオブジェクト番号 ゴーレムの番号を基準に
	static constexpr int RIGHT_FOT_OBJ_NUMBER  = 5;
	//左足のオブジェクト番号 ゴーレムの番号を基準に
	static constexpr int LEFT_FOT_OBJ_NUMBER  = 6;
//非公開定数
private:
	//当たり判定サイズ
	static constexpr DirectX::SimpleMath::Vector3 GOLEM_COLLISION_SIZE = { 2.5f,3.8f,2.5f };
	//ゴーレムのアウトラインの太さ
	static constexpr  float GOLEM_OUTLINE_THICKNESS = 0.04f;
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//経過時間取得
	const float GetFrameCount() const;
	//経過時間リセット
	void ResetFrameCount();

	const DirectX::SimpleMath::Quaternion& GetMotionAngle() const;
	void SetMotionAngle(const DirectX::SimpleMath::Quaternion& angle);

	//攻撃メッセージ
	const Message::AttackMesssage GetAttackMessage() const;
	void SetAttackMessage(const Message::AttackMesssage& message);
// コンストラクタ/デストラクタ
	// コンストラクタ
	Golem(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);
	// デストラクタ
	~Golem();
//　操作
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
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	// メッセージID
	Message::MessageID m_messageID;
	//当たり判定
	Box m_box;
	//状態
	std::unique_ptr<IState> m_idlingState; // 待機状態 
	std::unique_ptr<IState> m_movingState; // 移動状態
	std::unique_ptr<IState> m_attackState; // 攻撃状態
	std::unique_ptr<IState> m_chasingState; //追跡状態
	std::unique_ptr<IState> m_attackPreaparing; //攻撃準備状態
	std::unique_ptr<IState> m_damagedState;
	//経過時間
	float m_frameCount = 0;

	DirectX::SimpleMath::Quaternion m_motionAngle;


	Ito::DisplayCollision m_display;
	//攻撃方法メッセージ
	Message::AttackMesssage m_attackMessage;
	//ゴーレムのパーツ配列
	std::vector<std::unique_ptr<PartObject>> m_parts;
};

