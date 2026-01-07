/**
 * @file   GameObject.cpp
 *
 * @brief  ゲーム内のオブジェクトの基底クラスに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/11/26
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GameObject.h"


// オブジェクト番号
int GameObject::s_objectNumber = 0;

// オブジェクトをカウントアップする
int GameObject::CountUpNumber() { return s_objectNumber++; }

void GameObject::ResetObjectNumber() { s_objectNumber = 0; }

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in]  objectType オブジェクトの種類
 * @param[in]  modelParams モデルパラメータ
 * 
 */
GameObject::GameObject(Tag::ObjectType objectType,const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	: m_objectType{ objectType }
	, m_graphics{ Graphics::GetInstance() }
	, m_objectNumber{CountUpNumber()}
	, m_texture{ResourceManager::GetInstance()->RequestTexture("white.png")}
	, m_model{ nullptr }
	, m_pCurrentState{ nullptr }
	, m_currentMessage{}
	, m_position{} // 初期位置を設定
	, m_quaternion{ DirectX::SimpleMath::Quaternion::Identity } // 初期クォータニオンを設定
	, m_scale{ 1.0f, 1.0f, 1.0f } // 初期拡大率を設定
	, m_parent{ parent }
	, m_initialPosition{ initialPosition }
	, m_initialAngle{ initialAngle }
	, m_currentPosition{}
	, m_currentAngle{}
{
}


/**
 * @brief デストラクタ
 */
GameObject::~GameObject()
{
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
 * @brief テクスチャを設定する
 *
 * @param[in] tex テクスチャ
 *
 * @return なし
 */
void GameObject::SetTexture(ID3D11ShaderResourceView** tex)
{
	m_texture = tex;
}

/**
 * @brief テクスチャを取得する
 *
 * @param[in] なし
 *
 * @return テクスチャ
 */
ID3D11ShaderResourceView** GameObject::GetTexture()
{
	return m_texture;
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
const int GameObject::GetObjectNumber()
{
	return m_objectNumber;
}
