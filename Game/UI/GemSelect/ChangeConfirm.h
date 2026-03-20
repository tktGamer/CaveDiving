/**
 * @file   ChangeConfirm.h
 *
 * @brief  入れ替え確認UIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/30
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "../UserInterface.h"
#include"Game/Interface/IUI.h"
#include"../Menu/Menu.h"
// クラスの宣言 ===============================================================
class GemSelectUIManager;
class Sound;
// クラスの定義 ===============================================================
/**
  * @brief 入れ替え確認UI
  */
class ChangeConfirm : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//「入れ替えるか」のメッセージの位置
	static constexpr DirectX::SimpleMath::Vector2 CHANGE_MESSAGE_POSITION = { 650.0f,200.0f };
	//「入れ替えるか」のメッセージの大きさ
	static constexpr DirectX::SimpleMath::Vector2 CHANGE_MESSAGE_SCALE = { 1.0f,1.0f };
	//「はい」のメッセージの位置
	static constexpr DirectX::SimpleMath::Vector2 YES_MESSAGE_POSITION = { 350.0f,500.0f };
	//「はい」のメッセージの大きさ
	static constexpr DirectX::SimpleMath::Vector2 YES_MESSAGE_SCALE = { 1.0f,1.0f };
	//「いいえ」のメッセージの位置
	static constexpr DirectX::SimpleMath::Vector2 NO_MESSAGE_POSITION = { 950.0f,500.0f };
	//「いいえ」のメッセージの大きさ
	static constexpr DirectX::SimpleMath::Vector2 NO_MESSAGE_SCALE = { 1.0f,1.0f };
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//コンストラクタ
	ChangeConfirm(int width, int height, GemSelectUIManager* pUIManager);
	//デストラクタ
	~ChangeConfirm();
// 操作
	//初期化
	void Initialize() ;
	//更新
	void Update() override;
	//描画
	void Render() override;
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	GemSelectUIManager* m_pUIManager;
	//「入れ替えますか」のUI
	std::unique_ptr<UserInterface> m_changeMessage;
	//選択肢
	std::unique_ptr<Menu> m_menu;

	int m_windowWidth, m_windowHeight;

	//効果音
	std::unique_ptr<Sound> m_cursorSound;
	std::unique_ptr<Sound> m_showUISound;
};
