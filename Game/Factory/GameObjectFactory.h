/**
 * @file   GameObjectFactory.h
 *
 * @brief  ゲームオブジェクトの生成に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/17
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef GAMEOBJECT_FACTORY_DEFINED
#define GAMEOBJECT_FACTORY_DEFINED
// ヘッダファイルの読み込み ===================================================
#include"../Object/Camera.h"
#include"../Object/Character.h"
#include"../Object/Player/Player.h"
#include"../Object/Player/Hand.h"
#include"../Object/Player/Pikel.h"
#include"../Object/Enemy/Bat/Bat.h"
#include"../Object/Enemy/Bat/Wing.h"
#include"../Object/Enemy/Golem/Golem.h"
#include"../Object/Enemy/Golem/GolemHand.h"
#include"../Object/Enemy/Golem/GolemArm.h"
#include"../Object/Enemy/Golem/GolemFot.h"
#include"../Object/Stage/Stage.h"
#include"../Object/Stage/Ground.h"
#include"../Object/Stage/Wall.h"
#include"../Object/Stage/RumiRock.h"
#include"../Object/Item/Item.h"
#include"../Object/Item/UniquItem/OutlineItem.h"
#include"Game/GameData.h"
// クラスの宣言 ===============================================================
class BuffUIControl;
// クラスの定義 ===============================================================
/**
  * @brief ゲームオブジェクトの生成
  */
class GameObjectFactory 
{
public:
	// 「カメラ」を生成する
	static std::unique_ptr<Camera> CreateCamera(
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialDistance,
		const Character* target
	);

	// 「プレイヤー」を生成する
	static std::unique_ptr<Player> CreatePlayer(
		BuffUIControl* pBuffUIControl,
		const GameData::PlayerData& data,
		const GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);

	// 「プレイヤーの手」を生成する
	static std::unique_ptr<Hand> CreateHand(
		Character* root = nullptr,
		const GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);

	// 「ピッケル」を生成する
	static std::unique_ptr<Pikel> CreatePikle(
		Character* owner = nullptr,
		const GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
		);

	// 「コウモリの敵」を生成する
	static std::unique_ptr<Bat> CreateBat(
		EnemyManager* enemyManager,
		const GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity,
		const std::vector<int>& gemID = std::vector<int>(HolderGem::MAX_GEM, Gem::BLANK_ID)
	);

	// 「コウモリの羽」を生成する
	static std::unique_ptr<Wing> CreateBatWing(
		Character* root = nullptr,
		const GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);

	// 「ゴーレム」を生成する
	static std::unique_ptr<Golem> CreateGolem(
		EnemyManager* enemyManager,
		const GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity,
		const std::vector<int>& gemID = std::vector<int>(HolderGem::MAX_GEM, Gem::BLANK_ID)
	);

	// 「ゴーレムの手」を生成する
	static std::unique_ptr<GolemHand> CreateGolemHand(
		Character* root,
		const GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);

	// 「ゴーレムの腕」を生成する
	static std::unique_ptr<GolemArm> CreateGolemArm(
		Character* root,
		const GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity,
		const PartObject::RotationLimit& rotationlimit = PartObject::RotationLimit::OFF
	);

	// 「ゴーレムの足」を生成する
	static std::unique_ptr<GolemFot> CreateGolemFot(
		Character* root,
		const GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity,
		const PartObject::RotationLimit& rotationlimit = PartObject::RotationLimit::OFF
	);

	// 「ステージ」を生成する
	static std::unique_ptr<Stage> CreateStage(
		const GameObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition ,
		const DirectX::SimpleMath::Quaternion& initialAngle ,
		bool* isOnLight,
		int size
	);

	// 「地面」を生成する
	static std::unique_ptr<Ground> CreateGround(
		const GameObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition ,
		const DirectX::SimpleMath::Quaternion& initialAngle ,
		const DirectX::SimpleMath::Vector3& scale
	);

	// 「壁」を生成する
	static std::unique_ptr<Wall> CreateWall(
		const GameObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition ,
		const DirectX::SimpleMath::Quaternion& initialAngle,
		const DirectX::SimpleMath::Vector3& scale
	);

	// 「光る石」を生成する
	static std::unique_ptr<RumiRock> CreateRumiRock(
		const GameObject* parent,
		const int& id,
		const DirectX::SimpleMath::Vector3& initialPosition ,
		const DirectX::SimpleMath::Quaternion& initialAngle,
		const ModelShader::PointLightCB& lightData,
		const bool& isOnLight
	);

	// 「アイテム」を生成する
	static std::unique_ptr<Item> CreateItem(
		const Item::ItemInfo& itemInfo,
		const GameObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);

	// 「アウトラインアイテム」を生成する
	static std::unique_ptr<OutlineItem> CreateOutlineItem(
		const Item::ItemInfo& itemInfo,
		const GameObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity

	);

private:
	/**
	 * @brief 指定した型のゲームオブジェクトを生成する
	 *
	 * コンストラクタ引数を受け取りオブジェクトを生成し、
	 * 生成後に Initialize() を呼び出して初期化を行う。
	 *
	 * @tparam T        生成するオブジェクトの型
	 * @tparam Args     コンストラクタに渡す引数の型
	 * @param args      オブジェクト生成時に渡す引数
	 *
	 * @return 生成されたオブジェクト
	 */
	template<class T, class... Args>
	static std::unique_ptr<T> CreateObject(Args&&... args)
	{
		auto obj = std::make_unique<T>(std::forward<Args>(args)...);
		obj->Initialize();
		return obj;
	}
};

#endif		// GAMEOBJECT_FACTORY_DEFINED