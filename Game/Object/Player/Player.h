/**
 * @file   Player.h
 *
 * @brief  自キャラに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/08
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/GameData.h"
#include"Game/Object/Character.h"
#include"Game/Common/Collision/Sphere.h"
#include "Game/Object/Player/Hand.h"
#include"Game/Object/Gem/HolderGem.h"
#include "Game/Object/Light.h"
#include"../Item/Item.h"
#include"../Player/State/PlayerIdling.h"
#include"../Player/State/PlayerMoving.h"
#include"../Player/State/PlayerGroundAttack.h"
#include"../Player/State/PlayerAirAttack.h"
#include"../Player/State/PlayerJumping.h"
#include"../Player/State/PlayerAvoidance.h"
#include"../Player/State/PlayerDamaged.h"

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
	//ジャンプ可能回数
	static constexpr int REMAINING_JUMP = 1;

	//プレイヤーの初期位置
	static constexpr DirectX::SimpleMath::Vector3 PLAYER_INIT_POS = { 0.0f,0.0f,0.0f };
	//右手の初期位置
	static constexpr DirectX::SimpleMath::Vector3 RIGHT_HAND_INIT_POS = { 1.5f,0.0f,0.0f };
	//右手の角度
	static constexpr float RIGHT_HAND_Z_ANGLE = DirectX::XMConvertToRadians(-50.0f);
	//左手の初期位置
	static constexpr DirectX::SimpleMath::Vector3 LEFT_HAND_INIT_POS = { -1.5f,0.0f,0.0f };

	//右手のオブジェクト番号 プレイヤーの番号を基準に
	static constexpr int RIGHT_HAND_OBJ_NUMBER = 1;
	//左手のオブジェクト番号 プレイヤーの番号を基準に
	static constexpr int LEFT_HAND_OBJ_NUMBER = 2;
	//ピッケルのオブジェクト番号 プレイヤーの番号を基準に
	static constexpr int PIKEL_OBJ_NUMBER = 3;

	//待機状態に遷移するベクトルの条件
	static constexpr float MIN_LENGTH = 0.0001f;
private:
	//プレイヤーの球状当たり判定サイズ
	static constexpr float PLAYER_SPHERE_SIZE = 1.2f;
	//プレイヤーのアウトラインの太さ
	static constexpr  float PLAYER_OUTLINE_THICKNESS = 0.04f;
	//１秒あたりの回転量
	static constexpr  float ROTATION_SPEED_Y_ANGLE = DirectX::XMConvertToRadians(180.0f);
	
// データメンバの宣言 -----------------------------------------------
private:

	// メッセージID
	Message::MessageID m_messageID;


	//プレイヤーの所持ライト
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
	std::unique_ptr<IState> m_damagedState; // ダメージ状態

	// プレイヤーの体のパーツ
	std::vector<std::unique_ptr<GameObject>> m_bodyParts; 


	//ジャンプできる残り回数
	int m_remainingJumpCount = REMAINING_JUMP;

	//ダメージを無効化できる回数
	int m_invincibleCount = 0;

	DirectX::SimpleMath::Quaternion m_motionAngle;

	//手に入れたアイテム
	std::list<Item::ItemInfo> m_gotItems;
	//アイテム取得音
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
	void CollisionResponce(GameObject* other) override;

	//ダメージ処理
	int TakeDamage(const Character* attacker) override;
//　取得・設定
public:
	
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

	//所持宝石を取得
	const HolderGem& GetHolderGem();


//　内部操作
private:
	//アイテムの強化制限時間経過
	void UpdateGotItems();

	//方向転換
	void ChangeDirection();
	//宝石で強化された分のステータスを取得
	int GemPlusStatus(const Gem::Type& type) const;
	//アイテムで強化された分のステータスを取得
	int ItemBuff(const Item::EffectType& effectType) const;


};

