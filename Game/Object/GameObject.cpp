/**
 * @file   GameObject.cpp
 *
 * @brief  ゲーム内のオブジェクトの基底クラスに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/25
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GameObject.h"
#include"Game/Common/ResourceManager.h"
// オブジェクト番号
int GameObject::s_objectNumber = 0;
// オブジェクトをカウントアップする
int GameObject::CountUpNumber() { return s_objectNumber++; }
//オブジェクト番号をリセットする
void GameObject::ResetObjectNumber() { s_objectNumber = 0; }
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in]  objectType オブジェクトの種類
 * 
 */
GameObject::GameObject(const Tag::ObjectType& objectType)
	: 
	m_objectType{objectType},
	m_objectNumber{CountUpNumber()},
	m_texture{ ResourceManager::GetInstance()->RequestTexture(ResourcePath::TEXTURE::WHITE) }
{
}

/**
 * @brief デストラクタ
 */
GameObject::~GameObject()
{
	m_texture = nullptr;
	// メッセンジャーから登録解除
	Messenger::GetInstance()->UnRegister(m_objectNumber);
}


