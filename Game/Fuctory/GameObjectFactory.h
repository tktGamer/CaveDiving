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
#include"../Object/Stage/Stage.h"
// ゲームオブジェクトファクトリクラスを定義する
class GameObjectFactory 
{
public:
	// 「プレイヤー」を生成する
	static std::unique_ptr<Player> CreatePlayer(
		GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);

	// 「プレイヤーの手」を生成する
	static std::unique_ptr<Hand> CreateHand(
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
		GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);

	// 「ステージ」を生成する
	static std::unique_ptr<Stage> CreateStage(
		GameObject* parent = nullptr,
		const DirectX::SimpleMath::Vector3& initialPosition = DirectX::SimpleMath::Vector3::Zero,
		const DirectX::SimpleMath::Quaternion& initialAngle = DirectX::SimpleMath::Quaternion::Identity
	);


};

#endif		// CHARACTER_FACTORY_DEFINED