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
	m_items{}
{
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
	GenerateItem();
	LoadItemData();
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ItemManager::Update()
{

	//アイテムの消去
	DeleteItem();

	//アイテムの更新
	for (std::unique_ptr<Item>& item : m_items)
	{
		item->Update(DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);	
	}
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void ItemManager::Draw()
{

	//アイテムの描画
	for (std::unique_ptr<Item>& item : m_items)
	{
		item->Draw();
	}

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
void ItemManager::GenerateItem()
{
	Item::ItemInfo info;
	info.type = Item::EffectType::Attack;
	info.increase = 10;
	info.time = 10;
	m_items.emplace_back(GameObjectFactory::CreateItem(info, nullptr, DirectX::SimpleMath::Vector3{ -10.0f,2.0f,0.0f }, DirectX::SimpleMath::Quaternion::Identity));
	m_items.emplace_back(GameObjectFactory::CreateItem(info, nullptr, DirectX::SimpleMath::Vector3{ 45.0f,2.0f,-25.0f }, DirectX::SimpleMath::Quaternion::Identity));

	info.type = Item::EffectType::Diffece;
	info.increase = 10;
	info.time = 10;
	m_items.emplace_back(GameObjectFactory::CreateItem(info, nullptr, DirectX::SimpleMath::Vector3{ -20.0f,2.0f,20.0f }, DirectX::SimpleMath::Quaternion::Identity));

	info.type = Item::EffectType::Outline;
	info.increase = 0;
	info.time = 10;
	m_items.emplace_back(GameObjectFactory::CreateOutlineItem(info, nullptr, DirectX::SimpleMath::Vector3{ 0.0f,2.0f,30.0f }, DirectX::SimpleMath::Quaternion::Identity));
}


/**
 * @brief アイテムの消去
 *
 * @param[in] なし
 *
 * @return なし
 */
void ItemManager::DeleteItem()
{
  //  for (std::list<std::unique_ptr<Item>>::iterator it = m_items.begin(); it != m_items.end(); )
  //  {
		////生きているか確認
  //      if ((*it)->IsAlive())
  //      {
  //          // 死亡している場合はリストから削除
  // //         CollisionManager::GetInstance()->UnRegister(it->get());


		//	//ParticleManager::GetInstance()->RequestItemGetParticle((*it)->GetCurrentPosition(),(*it)->GetItemGetObjectPos(),(*it)->GetColor());
  // //         it = m_items.erase(it);
  //      }
  //      else
  //      {
  //          ++it;
  //      }
  //  }
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

