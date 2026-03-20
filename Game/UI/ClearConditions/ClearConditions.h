/**
 * @file   ClearConditions.h
 *
 * @brief  クリア条件UIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/30
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "../UserInterface.h"
#include"../Number/NumberControl.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief クリア条件UI
  */
class ClearConditions
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//アイコンテクスチャの位置
	static constexpr float OFFSET_X = -100.0f;
	//アイコンサイズ
	static constexpr DirectX::SimpleMath::Vector2 ICON_SIZE = { 0.05f,0.05f };
	//数字サイズ
	static constexpr DirectX::SimpleMath::Vector2 NUMBER_SIZE = { 0.3f, 0.3f };
	//数字の色
	static constexpr DirectX::SimpleMath::Vector4 NUMBER_COLOR = { 1.0f,1.0f,1.0f,1.0f };
	//数字の桁
	static constexpr int NUMBER_DIGIT = 2;
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:

//コンテキスト・デストラクタ
	//コンストラクタ
	ClearConditions(const DirectX::SimpleMath::Vector2& pos);
	//デストラクタ
	~ClearConditions();
//操作
	//初期化
	void Initialize();
	//更新
	void Update(const int& drawNumber );
	//描画
	void Render();
// データメンバの宣言 -----------------------------------------------
private:
	//描画座標
	DirectX::SimpleMath::Vector2 m_position;
	//残りの敵の数
	std::unique_ptr<NumberControl> m_restEnemy;
	//敵のアイコン
	std::unique_ptr<UserInterface> m_enemyIcon;
};
