/**
 * @file   UserInterface.h
 *
 * @brief  ユーザーインターフェイスに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/02/01
 */
 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"Game/Object/GameObject2D.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief ユーザーインターフェイス
  */
class UserInterface : public GameObject2D
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:

// コンストラクタ/デストラクタ
	// コンストラクタ
	UserInterface(const GameObject2D* parent = nullptr,
		const DirectX::SimpleMath::Vector2& initialPosition = DirectX::SimpleMath::Vector2::Zero,
		const DirectX::SimpleMath::Vector2& initialScale = DirectX::SimpleMath::Vector2::Zero);
	// デストラクタ
	~UserInterface();
// 操作
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//終了
	void Finalize() override;

//　内部操作
private:
	
// データメンバの宣言 -----------------------------------------------
private:

};