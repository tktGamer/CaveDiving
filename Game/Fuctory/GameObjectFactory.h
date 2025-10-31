/**
 * @file   GameObjectFactory.h
 *
 * @brief  ゲームオブジェクトの生成に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/15
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef GAMEOBJECT_FACTORY_DEFINED
#define GAMEOBJECT_FACTORY_DEFINED
// ヘッダファイルの読み込み ===================================================
#include"../Object/Character.h"
#include"../Object/Player/Player.h"
#include"../Object/Player/Hand.h"
#include"../Object/Player/Pikel.h"
#include"../Object/Enemy/Bat/Bat.h"
#include"../Object/Enemy/Bat/Wing.h"
#include"../Object/Enemy/Golem/Golem.h"
#include"../Object/Enemy/Golem/GolemHand.h"
#include"../Object/Stage/Stage.h"
// クラスの宣言 ===============================================================
class BuffUIControl;
// クラスの定義 ===============================================================
/**
  * @brief ゲームオブジェクトの生成
  */
class GameObjectFactory 
{
public:
	// 「プレイヤー」を生成する
	static std::unique_ptr<Player> CreatePlayer(
		BuffUIControl* pBuffUIControl,
		GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);

	// 「プレイヤーの手」を生成する
	static std::unique_ptr<Hand> CreateHand(
		Character* root = nullptr,
		GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);

	// 「ピッケル」を生成する
	static std::unique_ptr<Pikel> CreatePikle(
		Character* owner = nullptr,
		GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
		);

	// 「コウモリの敵」を生成する
	static std::unique_ptr<Bat> CreateBat(
		GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);

	// 「コウモリの羽」を生成する
	static std::unique_ptr<Wing> CreateBatWing(
		Character* root = nullptr,
		GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);

	// 「ゴーレム」を生成する
	static std::unique_ptr<Golem> CreateGolem(
		GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);

	// 「ゴーレムの手」を生成する
	static std::unique_ptr<GolemHand> CreateGolemHand(
		Character* root,
		GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);

	// 「ステージ」を生成する
	static std::unique_ptr<Stage> CreateStage(
		GameObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition ,
		const DirectX::SimpleMath::Quaternion& initialAngle ,
		bool* isOnLight,
		int size
	);


};

#endif		// CHARACTER_FACTORY_DEFINED