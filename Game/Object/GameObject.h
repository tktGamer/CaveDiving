/**
 * @file   GameObject.h
 *
 * @brief  オブジェクトの基底クラスに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
#include"Game/Interface/IState.h"
#include"Game/Shader.h"
#include"Game/Common/Collision/Shape.h"
#include"Game/Tag.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief GameObject
  */
class GameObject : public IObserver
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:
	// ステート
	IState* m_pCurrentState; 
	// オブジェクト番号
	static int s_objectNumber;
	// 現在のメッセージ
	Message m_currentMessage;
	// オブジェクトの種類
	Tag::ObjectType m_objectType;
	// グラフィックスクラスのポインタ
	Graphics* m_graphics; 
	// 当たり判定用の形状
	Shape* m_shape; 



	//テクスチャ
	ID3D11ShaderResourceView** m_texture;
	// モデルデータ
	DirectX::Model* m_model;	
	// モデルの位置
	DirectX::SimpleMath::Vector3 m_position = { 0.0f,0.0f,0.0f };	
	// モデルの回転
	DirectX::SimpleMath::Quaternion m_quaternion = { 0.0f,0.0f,0.0f,1.0f }; // モデルのクォータニオン回転
	// モデルの拡大率
	DirectX::SimpleMath::Vector3 m_scale = { 1.0f,1.0f,1.0f };	

protected:
	// 親オブジェクトへのポインタ
	GameObject* m_parent; 
	//初期座標
	DirectX::SimpleMath::Vector3 m_initialPosition;
	//初期回転角
	DirectX::SimpleMath::Quaternion m_initialAngle;
	// 現在の位置
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// 現在の回転角
	DirectX::SimpleMath::Quaternion m_currentAngle;


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GameObject(Tag::ObjectType m_objectType, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// デストラクタ
	~GameObject();


// 操作
public:
	virtual void Initialize();

	virtual void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)=0;

	virtual void Draw()=0;

	void Finalize();

	//衝突応答分岐
	void CollisionResponce(GameObject* other) {};
//　取得・設定
public:
	
	//テクスチャの設定
	void SetTexture(ID3D11ShaderResourceView** tex);
	//テクスチャの取得
	ID3D11ShaderResourceView** GetTexture();
	//モデルの設定
	void SetModel(DirectX::Model* model) { m_model = model; };
	//座標の設定
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	//回転の設定
	void SetQuaternion(const DirectX::SimpleMath::Quaternion& q) { m_quaternion = q; }
	//拡大率の設定
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }

	// 当たり判定用の形状を設定
	void SetShape(Shape* shape) { m_shape = shape; }
	// 当たり判定用の形状を取得
	Shape* GetShape() const { return m_shape; }

	// モデルデータの取得
	DirectX::Model* GetModel() { return m_model; }
	// モデルの位置の取得
	DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }
	// モデルの回転の取得
	DirectX::SimpleMath::Quaternion& GetQuaternion() { return m_quaternion; }
	// モデルの拡大率の取得
	DirectX::SimpleMath::Vector3& GetScale()  { return m_scale; }
	//
	DirectX::SimpleMath::Vector3& GetCurrentPosition() { return m_currentPosition; }
	DirectX::SimpleMath::Quaternion& GetCurrentQuaternion() { return m_currentAngle; }
	
	// オブジェクトの種類を取得する
	Tag::ObjectType GetObjectType() const; 
	// グラフィックスクラスのポインタを取得する
	Graphics* GetGraphics() const; 

	// オブジェクトをカウントアップする
	static int CountUpNumber();
	// 状態を取得する
	IState* GetState() { return m_pCurrentState; }
	// 状態を設定する
	void SetState(IState* state) { m_pCurrentState = state; }
	// 現在の状態を変更する
	void ChangeState(IState* state)
	{
		// 新規の状態遷移前に事後更新を行う
		m_pCurrentState->PostUpdate();
		// 新規の状態を現在の状態に設定する
		m_pCurrentState = state;
		// 新規の状態遷移後に事前更新を行う
		m_pCurrentState->PreUpdate();
	}
	// メッセージを取得する
	Message GetCurrentMessage() const { return m_currentMessage; }
	// メッセージを設定する
	void SetCurrentMessage(Message currentMessage) { m_currentMessage = currentMessage; }

	virtual int GetObjectNumber()=0;

//　内部操作
private:

};

