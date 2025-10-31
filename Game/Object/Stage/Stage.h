/**
 * @file   Stage.h
 *
 * @brief  ステージに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/08/27
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"../Stage/Ground.h"
#include"../Stage/Wall.h"
#include"../Stage/Candlestick.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief Stage
  */
class Stage
{
// クラス定数の宣言 -------------------------------------------------
public:
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;

	};


// データメンバの宣言 -----------------------------------------------
private:
	// メッセージID
	Message::MessageID m_messageID;


	//外壁
	std::unique_ptr<Wall> m_wall;
	//地面
	std::unique_ptr<Ground> m_ground;

	//発光する岩
	std::list<std::unique_ptr<CandleStick>> m_rocks;
	
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Stage(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~Stage();


// 操作
public:
	void Initialize(bool* isOnLight, int size);

	void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle);


	void Draw();

	void Finalize();

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);


	//　取得・設定
public:
	//敵を取得
	std::list<std::unique_ptr<CandleStick>>& GetRocks();


//　内部操作
private:
	void GenerateIlumiRock(bool* isOnLight, int size);
};

