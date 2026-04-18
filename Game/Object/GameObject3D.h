/**
 * @file   GameObject3D.h
 *
 * @brief  3Dのオブジェクトの基底クラスに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/04/09
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
#include"Game/Interface/IState.h"
#include"Game/Common/Collision/Shape.h"
#include"Game/Tag.h"
#include"Game/World.h"
#include"Game/Object/GameObject.h"
#include"Game/Object/Transform.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief オブジェクトの基底
  */
class GameObject3D : public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//親オブジェクトを取得
	const GameObject3D* GetParentObject() const { return m_parent; };
	//モデルの設定
	void SetModel(const DirectX::Model& model) { m_model = &model; };
	// モデルデータの取得
	const DirectX::Model* GetModel() const { return m_model; }
	//座標の設定
	void SetLocalPosition(const DirectX::SimpleMath::Vector3& position) {m_transform.SetPosition(position); }
	//座標の取得
	const DirectX::SimpleMath::Vector3& GetLocalPosition() const { return m_transform.GetPosition(); }
	//回転の設定
	void SetLocalQuaternion(const DirectX::SimpleMath::Quaternion& quaternion) { m_transform.SetQuaternion(quaternion); }
	//回転の取得
	const DirectX::SimpleMath::Quaternion& GetLocalQuaternion() const { return m_transform.GetQuaternion(); }
	//拡大率の設定
	void SetLocalScale(const DirectX::SimpleMath::Vector3& scale) { m_transform.SetScale(scale); }
	//拡大率の取得
	const DirectX::SimpleMath::Vector3& GetLocalScale() const { return m_transform.GetScale(); }
	//現在位置の取得
	const DirectX::SimpleMath::Vector3& GetCurrentPosition() const { return m_currentPosition; }
	//現在角度の取得
	const DirectX::SimpleMath::Quaternion& GetCurrentQuaternion() const { return m_currentAngle; }
	//拡大率の取得
	const DirectX::SimpleMath::Vector3& GetCurrentScale() const { return m_currentScale; }
	//最終座標計算
	const DirectX::SimpleMath::Matrix& GetWorldMatrix() const { return m_worldMatrix; };
	//ローカルトランスフォーム取得
	const Transform& GetLocalTransform() const { return m_transform; };
	// 当たり判定用の形状を設定
	void SetShape(Shape* shape) { m_shape = shape; }
	// 当たり判定用の形状を取得
	Shape* GetShape() const { return m_shape; }

	// 状態を取得する
	IState* GetState() const { return m_pCurrentState; }
	// 状態を設定する
	void SetState(IState* state) { m_pCurrentState = state; }
	// 現在の状態を変更予約をする
	void RequestChangeState(IState* state) { m_pNextState = state; };

	//ブルーム処理するか
	virtual bool IsBloom() { return false; };
// コンストラクタ/デストラクタ
	// コンストラクタ
	GameObject3D(const Tag::ObjectType& objectType,const GameObject3D* parent,const Transform& transform);
	// デストラクタ
	virtual ~GameObject3D();
// 操作
	//初期化
	virtual void Initialize() = 0;
	//更新
	virtual void Update()=0;
	//状態の更新
	void UpdateState();
	//描画
	virtual void Draw()=0;
	//終了
	virtual void Finalize() = 0;
	//衝突応答分岐
	virtual void CollisionResponce(GameObject3D* other)=0;
	//最終行列計算
	virtual void CalculationWorldMatrix();
	//行列から各要素を分解
	void DecomposeMatrix();
//　内部操作
private:
// データメンバの宣言 -----------------------------------------------
private:
	// 親オブジェクトへのポインタ
	const GameObject3D* m_parent;

	// 現在の状態
	IState* m_pCurrentState;
	// 次の状態
	IState* m_pNextState;
	// 当たり判定用の形状
	Shape* m_shape;

	// モデルデータ
	const DirectX::Model* m_model;
	//トランスフォーム
	Transform m_transform;
	//ワールド行列
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// 現在の位置
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// 現在の回転角
	DirectX::SimpleMath::Quaternion m_currentAngle;
	// 現在のサイズ
	DirectX::SimpleMath::Vector3 m_currentScale;
};
