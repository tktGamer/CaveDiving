/**
 * @file   UIManager.h
 *
 * @brief  UIの管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/17
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
class ResourceManager;    ///< リソースマネージャ
// クラスの定義 ===============================================================
/**
 * @brief ロゴシーン
 */
class UIManager
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
	
	//UI配置の基準ウィンドウサイズ
	static constexpr int WINDOW_SIZE_X = 1280;
	static constexpr int WINDOW_SIZE_Y = 720;

// メンバ関数の宣言 -------------------------------------------------
// 取得/設定
public:
	//インスタンスを取得
	static  UIManager* const GetInstance();

	void PushUI();

	//UIの追加リクエスト
	void RequestPushUI(std::unique_ptr<IUI> ui, bool isOnlyDraw);
	//UIの消去リクエスト
	void RequestPopUI();
	//UIの全消去リクエスト
	void RequestClearUI();
//　デストラクタ
public:
	//デストラクタ
	~UIManager();
// 操作
public:
	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Render();

	// 終了処理
	void Finalize();

	//UI全消去
	void ClearUI();

// コンストラクタ
private:
	// コンストラクタ
	UIManager();
	// インスタンスをコピーすることを禁止する
	void operator=(const UIManager&) = delete;
	// インスタンスをムーブすることを禁止する
	UIManager& operator= (UIManager&&) = delete;
	// コピーコンストラクタは禁止する
	UIManager(const UIManager&) = delete;
	// ムーブコンストラクタは禁止する
	UIManager(UIManager&&) = delete;
// 内部実装
private:

	// データメンバの宣言 -----------------------------------------------
private:
	// UIManagerクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<UIManager> s_uiManager;

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

};
