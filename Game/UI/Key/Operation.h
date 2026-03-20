/**
 * @file   Operation.h
 *
 * @brief  操作方法UIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/30
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Interface/IUI.h"
#include <Keyboard.h>
#include <vector>
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 操作方法UI
  */
class Operation : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
// メンバ関数の宣言 -------------------------------------------------
// 取得/設定
public:
	//UI設定
	void AddUI(std::unique_ptr<IUI> newUI);

// コンストラクタ/デストラクタ
	// コンストラクタ
	Operation();
	// デストラクタ
	~Operation();
// 操作
	//初期化処理
	void Initialize();
	//更新
	void Update() override;
	//描画
	void Render() override;
	
//内部処理
private:

// データメンバの宣言 -----------------------------------------------
private:
	//操作方法を示すUI群
	std::vector<std::unique_ptr<IUI>> m_uis;
};
