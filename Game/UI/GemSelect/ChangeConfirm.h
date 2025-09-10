/**
 * @file   ChangeConfirm.h
 *
 * @brief  入れ替え確認UIに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "../UserInterface.h"

#include"Game/Interface/IUI.h"
#include"../Menu/Menu.h"
// クラスの宣言 ===============================================================
class GemSelectUIManager;

// クラスの定義 ===============================================================
/**
  * @brief 入れ替え確認UI
  */
class ChangeConfirm : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:
	GemSelectUIManager* m_pUIManager;

	std::unique_ptr<UserInterface> m_changeMessage;
	
	std::unique_ptr<Menu> m_menu;

	int m_windowWidth, m_windowHeight;


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	ChangeConfirm(int width, int height, GemSelectUIManager* pUIManager);
	~ChangeConfirm();
	// 操作
public:
	void Initialize() ;
	void Update() override;
	void Render() override;

//　取得・設定
public:


//　内部操作
private:

};
