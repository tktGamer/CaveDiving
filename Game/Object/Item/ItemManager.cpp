/**
 * @file   ItemManager.cpp
 *
 * @brief  アイテム管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/17
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ItemManager.h"
#include<fstream>
#include<sstream>

#include"Game/Common/Collision/CollisionManager.h"
#include"Game/Factory/GameObjectFactory.h"
#include"Game/Particle/ParticleManager.h"
 // メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
ItemManager::ItemManager()
	:
	m_itemInfoList{},
	m_itemCreater{}
{
	ItemFactory createItemFunction = [&]
	(const Item::ItemInfo& info, const GameObject* parent, const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Quaternion& angle)
	{ return GameObjectFactory::CreateItem(info, parent, pos, angle); };
	
	//攻撃力アップアイテムの定義
	m_itemCreater.insert(std::make_pair(Item::EffectType::Attack,
		createItemFunction));
	//防御力アップアイテムの定義
	m_itemCreater.insert(std::make_pair(Item::EffectType::Diffece,
		createItemFunction));
	//速度アップアイテムの定義
	m_itemCreater.insert(std::make_pair(Item::EffectType::Speed,
		createItemFunction));
	//アウトラインアイテムの定義
	m_itemCreater.insert(std::make_pair(Item::EffectType::Outline,
		[&]
		(const Item::ItemInfo& info, const GameObject* parent, const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Quaternion& angle)
		{ return GameObjectFactory::CreateOutlineItem(info, parent, pos, angle); }));

}



/**
 * @brief デストラクタ
 */
ItemManager::~ItemManager()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ItemManager::Initialize()
{

	//GenerateItem(ResourcePath::DATA::ITEM_POSTION);
	LoadItemData();
}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ItemManager::Finalize()
{

}

/**
 * @brief アイテムの生成
 *
 * @param[in] なし
 *
 * @return なし
 */
std::vector<std::unique_ptr<Item>> ItemManager::GenerateItem(const std::string& spawnData)
{
	std::vector<std::unique_ptr<Item>> itemList;

	//ファイルのオープン
	std::ifstream ifs{ spawnData };
	if (!ifs.is_open())
	{
		//読み込み失敗
		return itemList;
	}
	//読み込んだ文字列を入れる
	std::string line;
	//一行飛ばす
	std::getline(ifs, line);

	while (std::getline(ifs, line))
	{
		std::stringstream ss(line);
		//アイテムの種類
		std::string id;
		std::getline(ss, id, ',');
		//座標
		std::string x, y, z;
		std::getline(ss, x, ',');
		std::getline(ss, y, ',');
		std::getline(ss, z, ',');

		//数値に変換
		DirectX::SimpleMath::Vector3 spawnPos;
		spawnPos.x = std::stof(x);
		spawnPos.y = std::stof(y);
		spawnPos.z = std::stof(z);

		//読み込んだ種類を生成
		itemList.push_back(m_itemCreater[m_itemInfoList[std::stoi(id)].type]
		(m_itemInfoList[std::stoi(id)],nullptr, spawnPos, DirectX::SimpleMath::Quaternion::Identity));

	}
	//ファイルを閉じる
	ifs.close();
	return (itemList); 

}
/**
 * @brief アイテムデータの読み込み
 *
 * @param[in] なし
 *
 * @return なし
 */
void ItemManager::LoadItemData()
{
	std::string path = ResourcePath::DATA::ITEM_DATA;
	//ファイルのオープン
	std::ifstream ifs{ path};
	if (!ifs.is_open())
	{
		//読み込み失敗
		return;
	}
	//一行飛ばす
	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	while (ifs)
	{
		//ID
		int id = 0;
		//アイテム情報
		Item::ItemInfo itemInfo;
		//文字列
		std::string line;

		// 1行まるごと取得
		if (!std::getline(ifs, line))
			break; // ファイルの終わり

		if (line.empty())
			continue;

		std::stringstream ss(line);
		std::string token;

		// ID
		std::getline(ss, token, ',');
		id = std::stoi(token);
		if (id <= 0)
			continue;

		// アイテム効果
		std::getline(ss, token, ',');
		if (token == ATTACK) 
		{
			itemInfo.type = Item::EffectType::Attack;
		}
		else if (token == DIFFENCE) 
		{
			itemInfo.type = Item::EffectType::Diffece;

		}
		else if (token == OUTLINE) 
		{
			itemInfo.type = Item::EffectType::Outline;

		}
		// 効果量
		std::getline(ss, token, ',');
		itemInfo.increase = std::stoi(token);
		// 効果時間
		std::getline(ss, token, ',');
		itemInfo.time =static_cast<float>(std::stoi(token));

		//リストに登録
		m_itemInfoList.insert(std::make_pair(id, itemInfo));
	}
	//ファイルを閉じる
	ifs.close();

	return;

}