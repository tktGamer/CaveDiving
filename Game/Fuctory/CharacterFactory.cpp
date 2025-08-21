#include "pch.h"
#include "CharacterFactory.h"
#include"../Object/Player/Player.h"
#include"../Object/Player/Hand.h"
#include"../Object/Player/Pikel.h"
#include"../Object/Enemy/Bat/Bat.h"
#include"../Object/Enemy/Bat/Wing.h"
// 「砲塔」を生成する
//std::unique_ptr<IComponent> Component::CreateTurret(
//	IComponent* parent,
//	const DirectX::SimpleMath::Vector3& initialPosition,
//	const float& initialAngle,
//	const float& mass
//)
//{
//	// 「砲塔」を宣言する
//	std::unique_ptr<IComponent> turret;
//	// 部品番号をリセットする
//	NodeBase::ResetComponentNumber();
//	// Turret クラスのインスタンスを生成する
//	turret.reset(new Turret(parent, initialPosition, initialAngle, mass));
//	// 初期化する
//	turret->Initialize();
//
//	// Turretクラスのインスタンスを返す
//	return std::move(turret);
//}

/**
 * @brief 「プレイヤー」の生成
 *
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　初期角度
 *
 * @return プレイヤークラス
 */
std::unique_ptr<Character> CharacterFactory::CreatePlayer(Character* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	//「プレイヤー」を宣言する
	std::unique_ptr<Character> player;
	//Playerクラスのインスタンスを生成する
	player = std::make_unique<Player>(parent, initialPosition, initialAngle);
	//初期化する
	player->Initialize();

	// Playerクラスのインスタンスを返す
	return std::move(player);
}

/**
 * @brief 「プレイヤーの手」の生成
 *
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　初期角度
 *
 * @return プレイヤーの手クラス
 */

std::unique_ptr<GameObject> CharacterFactory::CreateHand(Character* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	//「プレイヤーの手」を宣言する
	std::unique_ptr<GameObject> hand;
	//Playerクラスのインスタンスを生成する
	hand = std::make_unique<Hand>(parent, initialPosition, initialAngle);
	//初期化する
	hand->Initialize();

	// Handクラスのインスタンスを返す
	return std::move(hand);
}

/**
 * @brief 「ピッケル」の生成
 *
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　初期角度
 *
 * @return ピッケルクラス
 */
std::unique_ptr<GameObject> CharacterFactory::CreatePikle(Character* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	//「ピッケル」を宣言する
	std::unique_ptr<GameObject> pikel;
	//Pikelクラスのインスタンスを生成する
	pikel = std::make_unique<Pikel>(parent, initialPosition, initialAngle);
	//初期化する
	pikel->Initialize();

	// Pikelクラスのインスタンスを返す
	return std::move(pikel);
}

/**
 * @brief 「コウモリの敵」の生成
 *
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　初期角度
 *
 * @return コウモリの敵クラス
 */
std::unique_ptr<Character> CharacterFactory::CreateBat(Character* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	//「コウモリ」を宣言する
	std::unique_ptr<Character> bat;
	//Pikelクラスのインスタンスを生成する
	bat = std::make_unique<Bat>(parent, initialPosition, initialAngle);
	//初期化する
	bat->Initialize();

	// Batクラスのインスタンスを返す
	return std::move(bat);
}

/**
 * @brief 「コウモリの羽」の生成
 *
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　初期角度
 *
 * @return コウモリの羽クラス
 */
std::unique_ptr<GameObject> CharacterFactory::CreateBatWing(Character* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	//「コウモリの羽」を宣言する
	std::unique_ptr<GameObject> wing;
	//Wingクラスのインスタンスを生成する
	wing = std::make_unique<Wing>(parent, initialPosition, initialAngle);
	//初期化する
	wing->Initialize();

	// Wingクラスのインスタンスを返す
	return std::move(wing);
}
