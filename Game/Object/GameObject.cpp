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
 * @param[in]  parent 
 * @param[in]  initialPosition 
 * @param[in]  initialAngle 
 * 
 */
GameObject::GameObject(Tag::ObjectType objectType,const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	: 
	m_objectType{ objectType },
	m_objectNumber{CountUpNumber()},
	m_texture{ResourceManager::GetInstance()->RequestTexture(ResourcePath::TEXTURE::WHITE)},
	m_model{ nullptr },
	m_pCurrentState{ nullptr },
	m_currentMessage{},
	m_position{initialPosition} ,
	m_quaternion{ initialAngle }, // 初期クォータニオンを設定
	m_scale{ DirectX::SimpleMath::Vector3::One }, // 初期拡大率を設定
	m_parent{ parent },
	m_currentPosition{m_position},
	m_currentAngle{m_quaternion}
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

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameObject::Initialize()
{
}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameObject::Finalize()
{
}

/**
 * @brief オブジェクトの種類を取得する
 *
 * @param[in] なし
 *
 * @return オブジェクトの種類
 */
Tag::ObjectType GameObject::GetObjectType() const
{
	return m_objectType;
}

/**
 * @brief オブジェクトの番号を取得する
 *
 * @param[in] なし
 *
 * @return オブジェクトの番号
 */
const int GameObject::GetObjectNumber() const
{
	return m_objectNumber;
}
