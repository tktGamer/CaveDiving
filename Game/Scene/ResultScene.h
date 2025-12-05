/**
 * @file   ResultScene.h
 *
 * @brief  リザルトシーンに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include"../Common/SceneManager.h"
#include"Game/GameData.h"
#include"Game/Object/Camera.h"

#include"math.h"
#include"Game/UI/Menu/Menu.h"

#include"../UI/Result/TotalDamage.h"
#include"Game/UI/GemSelect/GemSelect.h"
#include"../UI/HoldGem/HoldGem.h"
// クラスの宣言 ===============================================================
class ResourceManager;    ///< リソースマネージャ
class Sound;



// クラスの定義 ===============================================================
/**
 * @brief ロゴシーン
 */
class ResultScene : public Scene<GameData>
{
// クラス定数の宣言 -------------------------------------------------
public:



// データメンバの宣言 -----------------------------------------------
private:
	// システム関連
	ResourceManager* m_pResourceManager;    ///< リソースマネージャ

	// オブジェクト関連
	std::unique_ptr<Camera> m_camera;    ///< カメラオブジェクト

	std::vector<std::unique_ptr<IUI>> m_uiStack;

	//背景
	std::unique_ptr<UserInterface> m_backTexture;

	std::unique_ptr<HoldGem> m_holdGem;

	//ゲームクリア　ゲームオーバーを表示するUI
	std::unique_ptr<UserInterface> m_gameover;
	//トータル与ダメージUI
	std::unique_ptr<TotalDamage> m_totalDamageUI;

	std::unique_ptr<UserInterface> m_saveMessage;
	std::unique_ptr<Menu> m_menu;

	std::unique_ptr<Sound> m_decideMenuSound;
	std::unique_ptr<Sound> m_clearSound;
	// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	ResultScene();

	// デストラクタ
	~ResultScene();


// 操作
public:
	// 初期化処理
	void Initialize() override;

	// 更新処理
	void Update(float elapsedTime) override;

	// 描画処理
	void Render() override;

	// 終了処理
	void Finalize() override;

	// デバイスに依存するリソースを作成する関数
	void CreateDeviceDependentResources() override;

	// ウインドウサイズに依存するリソースを作成する関数
	void CreateWindowSizeDependentResources() override;

	// デバイスロストした時に呼び出される関数
	void OnDeviceLost() override;

// 取得/設定
public:


// 内部実装
private:


};
