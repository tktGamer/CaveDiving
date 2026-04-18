/**
 * @file   GameObject3D.cpp
 *
 * @brief  ゲーム内のオブジェクトの基底クラスに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/25
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GameObject3D.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in]  objectType オブジェクトの種類
 * @param[in]  parent     親オブジェクト
 * @param[in]  transform  トランスフォーム
 * 
 */
GameObject3D::GameObject3D(const Tag::ObjectType& objectType,const GameObject3D* parent,const Transform& transform)
	: 
	GameObject{objectType},
	m_shape{},
	m_model{ nullptr },
	m_pCurrentState{ nullptr },
	m_pNextState{nullptr},
	m_parent{ parent },
	m_transform{transform},
	m_currentPosition{transform.GetPosition()},
	m_currentAngle{transform.GetQuaternion()},
	m_currentScale{transform.GetScale()}
{
}

/**
 * @brief デストラクタ
 */
GameObject3D::~GameObject3D()
{
	// メッセンジャーから登録解除
	Messenger::GetInstance()->UnRegister(GetObjectNumber());
}


/**
 * @brief 状態の更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameObject3D::UpdateState()
{
	//次の状態への予約があるなら
	if (m_pNextState) 
	{
		//現在の状態の更新後処理をする
		m_pCurrentState->PostUpdate();
		//現在の状態のポインタを更新する
		m_pCurrentState = m_pNextState;
		//現在の状態の更新前処理をする
		m_pCurrentState->PreUpdate();
		m_pNextState = nullptr;
	}
	//現在の状態を更新する
	m_pCurrentState->Update();
}

/**
 * @brief 最終行列計算
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameObject3D::CalculationWorldMatrix()
{
	//親オブジェクトがあるなら
	if (m_parent)
	{
		//親のマトリックスとかける
		m_parent->GetWorldMatrix() * m_transform.GetLocalMatrix();
		return;
	}
	m_transform.GetLocalMatrix();
}

/**
 * @brief 行列から要素を分解
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameObject3D::DecomposeMatrix()
{
	// 行列から分解
	DirectX::SimpleMath::Vector3 scale;
	DirectX::SimpleMath::Quaternion rotation;
	DirectX::SimpleMath::Vector3 position;

	m_worldMatrix.Decompose(m_currentScale, m_currentAngle, m_currentPosition);
}
