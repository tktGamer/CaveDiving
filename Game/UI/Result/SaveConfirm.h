/**
 * @file   SaveConfirm.h
 *
 * @brief  宝石保存確認UIに関するヘッダファイル
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
class SaveConfirm : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:
	//選択項目
	enum Command  : int
	{
		Yes = 0,
		No
	};
// データメンバの宣言 -----------------------------------------------
private:
	

	std::unique_ptr<UserInterface> m_saveMessage;
	
	std::unique_ptr<Menu> m_menu;

	int m_windowWidth, m_windowHeight;

	//決定したか
	bool m_isDecide;

	const std::vector<int>& m_gemID;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	SaveConfirm(int width, int height, const std::vector<int>& gemID);
	~SaveConfirm();
	// 操作
public:
	void Initialize();
	void Update();
	void Render();

//　取得・設定
public:
	bool IsDecide() const;

//　内部操作
private:

};
