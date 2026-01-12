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
#include"../Stage/RumiRock.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief ステージ
  */
class Stage
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:
	// メッセージID
	Message::MessageID m_messageID;


	//外壁
	std::unique_ptr<Wall> m_wall;
	//地面
	std::unique_ptr<Ground> m_ground;

	//発光する岩
	std::list<std::unique_ptr<RumiRock>> m_rocks;
	
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Stage(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~Stage();


// 操作
public:
	//初期化
	void Initialize(bool* isOnLight, int size);
	//更新
	void Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle);

	//描画
	void Draw();
	//ブルーム描画
	void BloomDraw();

	//終了
	void Finalize();

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);


//　取得・設定
public:
	//敵を取得
	std::list<std::unique_ptr<RumiRock>>& GetRocks();


//　内部操作
private:
	void GenerateIlumiRock(bool* isOnLight, int size);
};

