/**
 * @file   GemSelectUIManager.h
 *
 * @brief  宝石選択のUI群の管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/02/01
 */
// 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Common/SceneManager.h"
#include"Game/GameData.h"
#include"Game/Interface/IUI.h"
#include"Game/UI/Menu/Menu.h"
#include"Game/UI/GemSelect/ChangeConfirm.h"
#include"Game/UI/GemSelect/GemSelect.h"
#include"../UI/HoldGem/HoldGem.h"
#include"Game/UI/GemSelect/ChangeGem.h"
#include"../UI/HoldGem/HoldGemInfoDraw.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
 * @brief 宝石選択のUI群の管理
 */
class GemSelectUIManager
{
// クラス定数の宣言 -------------------------------------------------
public:
	enum UI 
	{
		NONE,
		GEMSELECT, //宝石選択
		CHANGECOFIRM, //入れ替え確認
		CHANGEGEM     //宝石入れ替え
	};
	//所持宝石表示位置
	static constexpr DirectX::SimpleMath::Vector2 HOLD_GEM_UI_POS = { 80.0f,680.0f };
// メンバ関数の宣言 -------------------------------------------------
// 取得/設定
public:

	void PushUI();

	//UIの追加リクエスト
	void RequestPushUI(UI pushUI, bool onlyDraw = false);
	//UIの消去リクエスト
	void RequestPopUI();
	//UIの全消去リクエスト
	void RequestClearUI();

	//宝石の選択が終了したか
	bool IsFinishSelect() const;

	//宝石選択終了通知
	void SelectFinishNotice(int slotNum);
	//入れ替え先宝石の設定
	void SetHoldGem(const Gem* pGem);
	//入れ替え先宝石の取得
	const Gem* GetHoldGem();
	//入れ替えるスロット番号の取得
	int GetSlot() const;
// コンストラクタ/デストラクタ
	// コンストラクタ
	GemSelectUIManager(const std::vector<int>& gemID);
	// デストラクタ
	~GemSelectUIManager();
// 操作
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();
// 内部実装
private:
	void PopUI();

	void ClearUI();

// データメンバの宣言 -----------------------------------------------
private:
	// システム関連
	//選択が終了
	bool m_isFinishSelect;

	//現在更新中のUIのみ描画するか
	bool m_isDrawOnlyCurrentUI;
	
	//UIを追加するか
	bool m_isPushUI;
	//UIを破棄するか
	bool m_isPopUI;
	//UIを全消去するか
	bool m_isClearUI;
	//追加するUI
	std::vector<UI> m_pushUI;

	//UIのスタック
	std::vector<std::unique_ptr<IUI>> m_uiStack;

	const std::vector<int> m_gemID;
	//入れ替え予定の宝石
	const Gem* m_pReplacementGem;
	//入れ替えるスロット番号
	int m_slot = 0;
};
