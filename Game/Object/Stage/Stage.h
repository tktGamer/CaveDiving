/**
 * @file   Stage.h
 *
 * @brief  ステージに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/22
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Stage/RumiRock.h"
// クラスの宣言 ===============================================================
class RumiRock;
// クラスの定義 ===============================================================
/**
  * @brief ステージ
  */
class Stage
{
// クラス定数の宣言 -------------------------------------------------
public:
	//地面の初期位置
	static constexpr DirectX::SimpleMath::Vector3 INITIAL_GROUND_POS = { 0.0f, -1.5f, 0.0f };
	//地面の初期サイズ
	static constexpr DirectX::SimpleMath::Vector3 INITIAL_GROUND_SCALE = { 70.0f, 1.0f, 70.0f };
	//壁の初期位置
	static constexpr DirectX::SimpleMath::Vector3 INITIAL_WALL_POS = { 0.0f, 0.0f, 0.0f };
	//壁の初期サイズ
	static constexpr DirectX::SimpleMath::Vector3 INITIAL_WALL_SCALE = { 60.0f, 50.0f, 60.0f };

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//岩を取得
	std::list<std::unique_ptr<RumiRock>>& GetRocks();
// コンストラクタ/デストラクタ
	// コンストラクタ
	Stage(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);
	// デストラクタ
	~Stage();
// 操作
	//初期化
	void Initialize(bool* isOnLight, int size);
	//終了
	void Finalize();
	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);
//　内部操作
private:
	void GenerateIlumiRock(bool* isOnLight, int size);
// データメンバの宣言 -----------------------------------------------
private:
	// メッセージID
	Message::MessageID m_messageID;
	//発光する岩
	std::list<std::unique_ptr<RumiRock>> m_rocks;
};

