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
#include"Game/GameData.h"
#include"Game/Object/Character.h"
#include"Game/Object/Player/HolderGem.h"
#include "Game/Object/Light.h"
#include"../Player/State/PlayerIdling.h"
#include"../Player/State/PlayerMoving.h"
#include"../Player/State/PlayerGroundAttack.h"
#include"../Player/State/PlayerAirAttack.h"
#include"../Player/State/PlayerJumping.h"
#include"../Player/State/PlayerAvoidance.h"
#include"../Player/State/PlayerDamaged.h"
#include"Game/Common/Collision/Sphere.h"
#include "Game/Object/Player/Hand.h"
#include"../Item/Item.h"
// クラスの宣言 ===============================================================
class IState;
class Sound;
class BuffUIControl;
// クラスの定義 ===============================================================
/**
  * @brief プレイヤー
  */
class Player : public Character
{
// クラス定数の宣言 -------------------------------------------------
public:

	//初期HP
	static constexpr int PLAYER_BASE_HP = 100;
	//初期攻撃力
	static constexpr int PLAYER_BASE_ATTACK = 20;
	//初期防御力
	static constexpr int PLAYER_BASE_DIFFENCE = 7;

	struct  ItemInfo
	{
		Item::EffectType effectType;
		int increase;
		float time;
	};

	//右手の角度
	static constexpr float RIGHT_HAND_Z_ANGLE = DirectX::XMConvertToRadians(-50.0f);

	//右手のオブジェクト番号 プレイヤーの番号を基準に
	static constexpr int RIGHT_HAND_OBJ_NUMBER = 1;
	//左手のオブジェクト番号 プレイヤーの番号を基準に
	static constexpr int LEFT_HAND_OBJ_NUMBER = 2;
	//ピッケルのオブジェクト番号 プレイヤーの番号を基準に
	static constexpr int PIKEL_OBJ_NUMBER = 3;

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
	std::unique_ptr<IState> m_groundAttackState; // 地上攻撃状態
	std::unique_ptr<IState> m_airAttackState; // 空中攻撃状態
	std::unique_ptr<IState> m_jumpingState; // ジャンプ状態
	std::unique_ptr<IState> m_avoidState;   // 回避状態
	std::unique_ptr<IState> m_damagedState; // 回避状態

	// プレイヤーの体のパーツ
	std::vector<std::unique_ptr<GameObject>> m_bodyParts; 
	//プレイヤーの向き
	DirectX::SimpleMath::Vector3 m_initialeDirection;

	//重力
	float m_gravity = 9.8f; // 重力加速度

	//ジャンプできる残り回数
	int m_remainingJumpCount;

	//ダメージを無効化できる回数
	int m_invincibleCount = 1;

	DirectX::SimpleMath::Quaternion m_motionAngle;

	//手に入れたアイテム
	std::list<ItemInfo> m_gotItems;

	std::unique_ptr<Sound> m_getItemSound;

	//バフを表示するクラスのポインタ
	BuffUIControl* m_pBuffUIControl;

	//プレイヤーの持つジェム
	std::unique_ptr<HolderGem> m_holderGem;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Player(BuffUIControl* pBuffUIControl,const GameData::PlayerData& data,const GameObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~Player();


// 操作
public:
	void Initialize();

	void Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

	void Finalize();

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);
	//衝突応答分岐
	void CollisionResponce(GameObject* other) override;


	int TakeDamage(const Character* attacker) override;
//　取得・設定
public:
	
	DirectX::SimpleMath::Vector3 GetVelocity();
	void SetVelocity(const DirectX::SimpleMath::Vector3& v);

	// 体力の取得
	const int GetMaxHP() const override;
	// 攻撃力の取得
	const int GetAttackPower() const override;
	// 防御力の取得
	const int GetDiffence() override;



	//ジャンプ出来る残り回数取得
	const int GetRemainingJumpCount() const;
	//ジャンプ出来る残り回数減少
	bool ReduceJumpCount();
	//ジャンプ出来る残り回数をリセット
	void ResetJumpCount();


	DirectX::SimpleMath::Quaternion GetMotionAngle() const;
	void SetMotionAngle(const DirectX::SimpleMath::Quaternion& angle);

	const HolderGem& GetHolderGem();


//　内部操作
private:
	//アイテムの強化制限時間経過
	void UpdateGotItems();

	//方向転換
	void ChangeDirection();
	//宝石で強化された分のステータスを取得
	int GemPlusStatus(const Gem::Type type) const;
	//アイテムで強化された分のステータスを取得
	int ItemBuff(const Item::EffectType& effectType) const;


};

