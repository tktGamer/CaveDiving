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
std::unique_ptr<Player> GameObjectFactory::CreatePlayer(BuffUIControl* pBuffUIControl, const GameData::PlayerData& data,const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//「プレイヤー」を宣言する
	std::unique_ptr<Player> player;
	//Playerクラスのインスタンスを生成する
	player = std::make_unique<Player>(pBuffUIControl,data, parent, initialPosition, initialAngle);
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
std::unique_ptr<Hand> GameObjectFactory::CreateHand(
	Character* root,GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//「プレイヤーの手」を宣言する
	std::unique_ptr<Hand> hand;
	//Handクラスのインスタンスを生成する
	hand = std::make_unique<Hand>(root,parent, initialPosition, initialAngle);
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


/**
 * @brief 「ゴーレム」の生成
 *
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　初期角度
 *
 * @return ゴーレムクラス
 */
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

/**
 * @brief 「ゴーレムの手」の生成
 *
 * @param[in] 大元のオブジェクトポインタ
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　初期角度
 *
 * @return ゴーレムの手クラス
 */
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

/**
 * @brief 「ステージ」の生成
 *
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　初期角度
 * @param[in] isOnLight　　ライトのオン・オフの配列
 * @param[in] size　　　　　配列のサイズ
 *
 * @return ステージクラス
 */
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

/**
 * @brief 「地面」の生成
 *
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　初期角度
 * @param[in] scale　　拡大率
 *
 * @return 地面クラス
 */
std::unique_ptr<Ground> GameObjectFactory::CreateGround(GameObject* parent, 
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle,
	const DirectX::SimpleMath::Vector3& scale)
{
	//「地面」を宣言する
	std::unique_ptr<Ground> ground;
	//Groundクラスのインスタンスを生成する
	ground = std::make_unique<Ground>(parent, initialPosition, initialAngle);
	//初期化する
	ground->Initialize();
	ground->SetScale(scale);
	// Groundクラスのインスタンスを返す
	return std::move(ground);
}

/**
 * @brief 「壁」の生成
 *
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　初期角度
 * @param[in] scale　　       拡大率
 *
 * @return 壁クラス
 */
std::unique_ptr<Wall> GameObjectFactory::CreateWall(GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle,
	const DirectX::SimpleMath::Vector3& scale)
{
	//「壁」を宣言する
	std::unique_ptr<Wall> wall;
	//Wallクラスのインスタンスを生成する
	wall = std::make_unique<Wall>(parent, initialPosition, initialAngle);
	//初期化する
	wall->Initialize();
	wall->SetScale(scale);
	// Wallクラスのインスタンスを返す
	return std::move(wall);
}

/**
 * @brief 「アイテム」の生成
 *
 * @param[in] itemInfo　　　　 アイテムの情報
 * @param[in] parent   　　　　親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　 初期角度
 *
 * @return アイテムクラス
 */
std::unique_ptr<Item> GameObjectFactory::CreateItem(const Item::ItemInfo& itemInfo, const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//「アイテム」を宣言する
	std::unique_ptr<Item> item;
	//Itemクラスのインスタンスを生成する
	item = std::make_unique<Item>(itemInfo, parent, initialPosition, initialAngle);
	//初期化する
	item->Initialize();
	// Itemクラスのインスタンスを返す
	return std::move(item);
}

/**
 * @brief 「アウトラインアイテム」の生成
 *
 * @param[in] itemInfo　　　　 アイテムの情報
 * @param[in] parent   　　　　親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　 初期角度
 *
 * @return アウトラインアイテムクラス
 */
std::unique_ptr<OutlineItem> GameObjectFactory::CreateOutlineItem(const Item::ItemInfo& itemInfo, const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//「アイテム」を宣言する
	std::unique_ptr<OutlineItem> outlineItem;
	//OutlineItemクラスのインスタンスを生成する
	outlineItem = std::make_unique<OutlineItem>(itemInfo, parent, initialPosition, initialAngle);
	//初期化する
	outlineItem->Initialize();
	// OutlineItemクラスのインスタンスを返す
	return std::move(outlineItem);
}

