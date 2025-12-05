/**
 * @file   ItemManager.cpp
 *
 * @brief  アイテム管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/11/27
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
	m_items.emplace_back(std::make_unique<StatusUpItem>(Item::EffectType::Attack, 10, nullptr, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity));
	m_items.back()->Initialize();
	m_items.back()->SetPosition({ -10.0f,2.0f,0.0f });

	m_items.emplace_back(std::make_unique<StatusUpItem>(Item::EffectType::Attack, 10, nullptr, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity));
	m_items.back()->Initialize();
	m_items.back()->SetPosition({ 40.0f,2.0f,-20.0f });

	m_items.emplace_back(std::make_unique<StatusUpItem>(Item::EffectType::Diffece, 10, nullptr, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity));
	m_items.back()->Initialize();
	m_items.back()->SetPosition({ -20.0f,2.0f,20.0f });


	m_items.emplace_back(std::make_unique<OutlineItem>(Item::EffectType::Outline, 10, nullptr, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity));
	m_items.back()->Initialize();
	m_items.back()->SetPosition({ 0.0f,2.0f,30.0f });
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
