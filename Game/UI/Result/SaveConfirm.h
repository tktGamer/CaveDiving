/**
 * @file   SaveConfirm.h
 *
 * @brief  宝石保存確認UIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/02/01
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

	//「はい」のメッセージの位置
	static constexpr DirectX::SimpleMath::Vector2 YES_MESSAGE_POSITION = { 350.0f,600.0f };
	//「はい」のメッセージの大きさ
	static constexpr DirectX::SimpleMath::Vector2 YES_MESSAGE_SCALE = { 0.9f,0.9f };
	//「いいえ」のメッセージの位置
	static constexpr DirectX::SimpleMath::Vector2 NO_MESSAGE_POSITION = { 950.0f,600.0f };
	//「いいえ」のメッセージの大きさ
	static constexpr DirectX::SimpleMath::Vector2 NO_MESSAGE_SCALE = { 0.9f,0.9f };

// データメンバの宣言 -----------------------------------------------
private:
	//セーブするかのUI
	std::unique_ptr<UserInterface> m_saveMessage;
	//選択肢
	std::unique_ptr<Menu> m_menu;

	int m_windowWidth, m_windowHeight;

	//決定したか
	bool m_isDecide;
	//宝石のID
	const std::vector<int>& m_gemID;
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//決定したか
	bool IsDecide() const;
// コンストラクタ/デストラクタ
	//コンテキスト
	SaveConfirm(int width, int height, const std::vector<int>& gemID);
	//デストラクタ
	~SaveConfirm();
// 操作
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Render();
//　内部操作
private:

};
