/**
 * @file   ItemManager.cpp
 *
 * @brief  アイテム管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/08/27
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ItemManager.h"
#include"Game/Common/Collision/CollisionManager.h"
#include"Game/Fuctory/GameObjectFactory.h"
#include"Game/Particle/ParticleManager.h"
 // メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
ItemManager::ItemManager()
	:m_graphics{Graphics::GetInstance()}
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
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();

	//アイテムの消去
	DeleteItem();

	//アイテムの更新
	for (std::unique_ptr<Item>& item : m_items)
	{
		item->Update(elapsedTime, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);	
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
	m_items.emplace_back(std::make_unique<Item>(Item::UpStatus::Attack, 10, nullptr, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity));
	m_items.back()->Initialize();
	m_items.back()->SetPosition({ -10.0f,2.0f,0.0f });
	
	m_items.emplace_back(std::make_unique<Item>(Item::UpStatus::Diffece, 10, nullptr, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity));
	m_items.back()->Initialize();
	m_items.back()->SetPosition({ -20.0f,2.0f,20.0f });
	//m_itemss.emplace_back(GameObjectFactory::CreateBat());
	//m_itemss.back()->SetPosition({ 0.0f, 1.0f, -8.0f });
	//CollisionManager::GetInstance()->Register(m_itemss.back().get());
	//Messenger::GetInstance()->Register(m_itemss.back()->GetObjectNumber(), m_itemss.back().get());

	//m_itemss.emplace_back(GameObjectFactory::CreateBat());
	//m_itemss.back()->SetPosition({ 6.0f,1.0f,33.0f });
	//CollisionManager::GetInstance()->Register(m_itemss.back().get());
	//Messenger::GetInstance()->Register(m_itemss.back()->GetObjectNumber(), m_itemss.back().get());
	//m_itemss.emplace_back(std::make_unique<Bat>( nullptr, DirectX::SimpleMath::Vector3::Zero, DirectX::XMConvertToRadians(0.0f)));
	//m_itemss.back()->Initialize();
	//m_itemss.back()->SetPosition({ 9.0f,1.0f,-33.0f });
	//CollisionManager::GetInstance()->Register(m_itemss.back().get());
	//Messenger::GetInstance()->Register(m_itemss.back()->GetObjectNumber(), m_itemss.back().get());
	//m_itemss.emplace_back(std::make_unique<Bat>(nullptr, DirectX::SimpleMath::Vector3::Zero, DirectX::XMConvertToRadians(0.0f)));
	//m_itemss.back()->Initialize();
	//m_itemss.back()->SetPosition({ -1.0f,1.0f,-36.0f });
	//CollisionManager::GetInstance()->Register(m_itemss.back().get());
	//Messenger::GetInstance()->Register(m_itemss.back()->GetObjectNumber(), m_itemss.back().get());
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
    for (std::list<std::unique_ptr<Item>>::iterator it = m_items.begin(); it != m_items.end(); )
    {
		//生きているか確認
        if ((*it)->IsGet())
        {
            // 死亡している場合はリストから削除
            CollisionManager::GetInstance()->UnRegister(it->get());


			ParticleManager::GetInstance()->RequestItemGetParticle((*it)->GetCurrentPosition(),(*it)->GetItemGetObjectPos(),(*it)->GetColor());
            it = m_items.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
