#include "pch.h"
#include "GameObjectFactory.h"

/**
 * @brief 「プレイヤー」の生成
 *
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　初期角度
 *
 * @return プレイヤークラス
 */
std::unique_ptr<Player> GameObjectFactory::CreatePlayer(BuffUIControl* pBuffUIControl, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//「プレイヤー」を宣言する
	std::unique_ptr<Player> player;
	//Playerクラスのインスタンスを生成する
	player = std::make_unique<Player>(pBuffUIControl,parent, initialPosition, initialAngle);
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
std::unique_ptr<Hand> GameObjectFactory::CreateHand(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//「プレイヤーの手」を宣言する
	std::unique_ptr<Hand> hand;
	//Handクラスのインスタンスを生成する
	hand = std::make_unique<Hand>(parent, initialPosition, initialAngle);
	//初期化する
	hand->Initialize();

	// Handクラスのインスタンスを返す
	return std::move(hand);
}



/**
 * @brief 「ピッケル」の生成
 *
 * @param[in] owner   ピッケルの所有者（攻撃力をもつオブジェクト）のポインタ
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　初期角度
 *
 * @return ピッケルクラス
 */
std::unique_ptr<Pikel> GameObjectFactory::CreatePikle(Character* owner, GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//「ピッケル」を宣言する
	std::unique_ptr<Pikel> pikel;
	//Pikelクラスのインスタンスを生成する
	pikel = std::make_unique<Pikel>(owner, parent, initialPosition, initialAngle);
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
std::unique_ptr<Bat> GameObjectFactory::CreateBat(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//「コウモリ」を宣言する
	std::unique_ptr<Bat> bat;
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
std::unique_ptr<Wing> GameObjectFactory::CreateBatWing(Character* root, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//「コウモリの羽」を宣言する
	std::unique_ptr<Wing> wing;
	//Wingクラスのインスタンスを生成する
	wing = std::make_unique<Wing>(root,parent, initialPosition, initialAngle);
	//初期化する
	wing->Initialize();

	// Wingクラスのインスタンスを返す
	return std::move(wing);
}

std::unique_ptr<Golem> GameObjectFactory::CreateGolem(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//「ゴーレム」を宣言する
	std::unique_ptr<Golem> golem;
	//Golemクラスのインスタンスを生成する
	golem = std::make_unique<Golem>(parent, initialPosition, initialAngle);
	//初期化する
	golem->Initialize();

	// Golemクラスのインスタンスを返す
	return std::move(golem);
}

std::unique_ptr<GolemHand> GameObjectFactory::CreateGolemHand(Character* root, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//「ゴーレムの手」を宣言する
	std::unique_ptr<GolemHand> golem;
	//GolemHandクラスのインスタンスを生成する
	golem = std::make_unique<GolemHand>(root, parent, initialPosition, initialAngle);
	//初期化する
	golem->Initialize();

	// GolemHandクラスのインスタンスを返す
	return std::move(golem);
}

std::unique_ptr<Stage> GameObjectFactory::CreateStage(GameObject* parent, 
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Quaternion& initialAngle,
	bool* isOnLight,
	int size
)
{
	//「ステージ」を宣言する
	std::unique_ptr<Stage> stage;
	//Stageクラスのインスタンスを生成する
	stage = std::make_unique<Stage>(parent, initialPosition, initialAngle);
	//初期化する
	stage->Initialize(isOnLight,size);

	// Stageクラスのインスタンスを返す
	return std::move(stage);
}

