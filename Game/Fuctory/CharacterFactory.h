/**
 * @file   CharacterFactory.h
 *
 * @brief  キャラクターの生成に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef CHARACTER_FACTORY_DEFINED
#define CHARACTER_FACTORY_DEFINED
// ヘッダファイルの読み込み ===================================================
#include"../Object/Character.h"
// 部品ファクトリクラスを定義する
class CharacterFactory 
{
public:
	// 「プレイヤー」を生成する
	static std::unique_ptr<Character> CreatePlayer(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// 「プレイヤーの手」を生成する
	static std::unique_ptr<GameObject> CreateHand(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// 「ピッケル」を生成する
	static std::unique_ptr<GameObject> CreatePikle(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// 「コウモリの敵」を生成する
	static std::unique_ptr<Character> CreateBat(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// 「コウモリの羽」を生成する
	static std::unique_ptr<GameObject> CreateBatWing(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// 「砲塔砲身」を生成する
	static std::unique_ptr<Character> CreateTurretGun(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// 「砲塔プレート」を生成する
	static std::unique_ptr<Character> CreateTurretPlate(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);

	// 「砲塔脚」を生成する
	static std::unique_ptr<Character> CreateTurretFoot(
		Character* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle
		);
};

#endif		// CHARACTER_FACTORY_DEFINED