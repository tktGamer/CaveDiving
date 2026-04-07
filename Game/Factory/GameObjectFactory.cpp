/**
 * @file   GameObjectFactory.cpp
 *
 * @brief  オブジェクト生成に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/14
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GameObjectFactory.h"
 // メンバ関数の定義 ===========================================================
/**
 * @brief 「カメラ」の生成
 *
 * @param[in] initialPosition　初期位置
 * @param[in] initialDistance  ターゲットとの距離
 * @param[in] target　　　　　 ターゲット
 *
 * @return カメラクラス
 */
std::unique_ptr<Camera> GameObjectFactory::CreateCamera(const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialDistance, const Character* target)
{
	//Cameraクラスのインスタンスを生成する
	std::unique_ptr<Camera> camera = CreateObject<Camera>(initialPosition);
	//注視点との距離を設定
	camera->SetDistance(initialDistance);
	//注視点となるターゲットを設定
	camera->SetTarget(target->GetCurrentPosition(), target->GetQuaternion(), target->GetVelocity());
	// Cameraクラスのインスタンスを返す
	return camera;
}

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
	//Playerクラスのインスタンスを生成する
	auto player = CreateObject<Player>(pBuffUIControl, data, parent, initialPosition, initialAngle); 
	// Playerクラスのインスタンスを返す
	return player;
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
	Character* root, const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//Handクラスのインスタンスを生成する
	std::unique_ptr<Hand> hand = CreateObject<Hand>(root,parent, initialPosition, initialAngle);
	// Handクラスのインスタンスを返す
	return hand;
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
std::unique_ptr<Pikel> GameObjectFactory::CreatePikle(Character* owner, const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//Pikelクラスのインスタンスを生成する
	std::unique_ptr<Pikel> pikel = CreateObject<Pikel>(owner, parent, initialPosition, initialAngle);
	// Pikelクラスのインスタンスを返す
	return pikel;
}

/**
 * @brief 「コウモリの敵」の生成
 *
 * @param[in] parent           親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　 初期角度
 *
 * @return コウモリの敵クラス
 */
std::unique_ptr<Bat> GameObjectFactory::CreateBat(EnemyManager* enemyManager, const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle,
	const std::vector<int>& gemID)
{
	//Batクラスのインスタンスを生成する
	std::unique_ptr<Bat> bat = CreateObject<Bat>(enemyManager, parent, initialPosition, initialAngle,gemID);
	// Batクラスのインスタンスを返す
	return bat;
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
std::unique_ptr<Wing> GameObjectFactory::CreateBatWing(Character* root, const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//Wingクラスのインスタンスを生成する
	std::unique_ptr<Wing> wing = CreateObject<Wing>(root,parent, initialPosition, initialAngle);
	// Wingクラスのインスタンスを返す
	return wing;
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
std::unique_ptr<Golem> GameObjectFactory::CreateGolem(EnemyManager* enemyManager, const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle,
	const std::vector<int>& gemID)
{
	//Golemクラスのインスタンスを生成する
	std::unique_ptr<Golem> golem = CreateObject<Golem>(enemyManager, parent, initialPosition, initialAngle, gemID);
	// Golemクラスのインスタンスを返す
	return golem;
}

/**
 * @brief 「ゴーレムの手」の生成
 *
 * @param[in] root     大元のオブジェクトポインタ
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　 初期角度
 *
 * @return ゴーレムの手クラス
 */
std::unique_ptr<GolemHand> GameObjectFactory::CreateGolemHand(Character* root, const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
{
	//GolemHandクラスのインスタンスを生成する
	std::unique_ptr<GolemHand> golemHand = CreateObject<GolemHand>(root, parent, initialPosition, initialAngle);
	// GolemHandクラスのインスタンスを返す
	return golemHand;
}

/**
 * @brief 「ゴーレムの腕」の生成
 *
 * @param[in] root     大元のオブジェクトポインタ
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　 初期角度
 * @param[in] rotationlimit　　角度制限
 *
 * @return ゴーレムの腕クラス
 */
std::unique_ptr<GolemArm> GameObjectFactory::CreateGolemArm(Character* root, const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle, const PartObject::RotationLimit& rotationlimit)
{
	//GolemArmクラスのインスタンスを生成する
	std::unique_ptr<GolemArm> golemArm = CreateObject<GolemArm>(root, parent, initialPosition, initialAngle);
	//角度制限を設定
	golemArm->SetRotationLimit(rotationlimit);
	// GolemArmクラスのインスタンスを返す
	return golemArm;
}

/**
 * @brief 「ゴーレムの足」の生成
 *
 * @param[in] root     大元のオブジェクトポインタ
 * @param[in] parent   親のポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　 初期角度
 * @param[in] rotationlimit　　角度制限
 *
 * @return ゴーレムの足クラス
 */
std::unique_ptr<GolemFot> GameObjectFactory::CreateGolemFot(Character* root, const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle, const PartObject::RotationLimit& rotationlimit)
{
	//GolemFotクラスのインスタンスを生成する
	std::unique_ptr<GolemFot> golemFot = CreateObject<GolemFot>(root, parent, initialPosition, initialAngle);
	//角度制限を設定
	golemFot->SetRotationLimit(rotationlimit);
	//ゴーレムに対してちょうどいい大きさ
	golemFot->SetScale({ 1.5f,1.5f,1.5f });

	// GolemFotクラスのインスタンスを返す
	return golemFot;
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
std::unique_ptr<Stage> GameObjectFactory::CreateStage(const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Quaternion& initialAngle,
	bool* isOnLight,
	int size
)
{
	//Stageクラスのインスタンスを生成する
	std::unique_ptr<Stage> stage = std::make_unique<Stage>(parent, initialPosition, initialAngle);
	stage->Initialize(isOnLight, size);
	// Stageクラスのインスタンスを返す
	return stage;
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
std::unique_ptr<Ground> GameObjectFactory::CreateGround(const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle,
	const DirectX::SimpleMath::Vector3& scale)
{
	//Groundクラスのインスタンスを生成する
	std::unique_ptr<Ground> ground = CreateObject<Ground>(parent, initialPosition, initialAngle);
	ground->SetScale(scale);
	// Groundクラスのインスタンスを返す
	return ground;
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
std::unique_ptr<Wall> GameObjectFactory::CreateWall(const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle,
	const DirectX::SimpleMath::Vector3& scale)
{
	//Wallクラスのインスタンスを生成する
	std::unique_ptr<Wall> wall = CreateObject<Wall>(parent, initialPosition, initialAngle);
	wall->SetScale(scale);
	// Wallクラスのインスタンスを返す
	return wall;
}

/**
 * @brief 「光る石」の生成
 *
 * @param[in] parent   親のポインタ
 * @param[in] id      石の番号
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　　初期角度
 * @param[in] lightData　　   ライト情報
 * @param[in] isOnLight　　    ライトをオンにするか
 *
 * @return 光る石クラス
 */
std::unique_ptr<RumiRock> GameObjectFactory::CreateRumiRock(const GameObject* parent, const int& id, const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Quaternion& initialAngle, const ModelShader::PointLightCB& lightData, const bool& isOnLight)
{
	//RumiRockクラスのインスタンスを生成する
	std::unique_ptr<RumiRock> rock = CreateObject<RumiRock>(lightData,id, parent, initialPosition, initialAngle);
	if (isOnLight) 
	{
		rock->OnLight();
	}
	//RumiRockクラスのインスタンスを返す
	return rock;
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
	//Itemクラスのインスタンスを生成する
	std::unique_ptr<Item> item = CreateObject<Item>(itemInfo, parent, initialPosition, initialAngle);
	// Itemクラスのインスタンスを返す
	return item;
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
	//OutlineItemクラスのインスタンスを生成する
	std::unique_ptr<OutlineItem> outlineItem = CreateObject<OutlineItem>(itemInfo, parent, initialPosition, initialAngle);
	// OutlineItemクラスのインスタンスを返す
	return outlineItem;
}