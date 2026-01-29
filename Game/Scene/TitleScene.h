/**
 * @file   TitleScene.h
 *
 * @brief  タイトルシーンに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/28
 */
// 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Common/SceneManager.h"
#include"Game/GameData.h"
#include"Game/Object/Camera.h"
#include"math.h"
#include"Game/UI/UserInterface.h"
#include"Game/Transitor/Transitor.h"
#include"Game/Object/Player/Player.h"
// クラスの宣言 ===============================================================
class Sound;
// クラスの定義 ===============================================================
/**
 * @brief タイトルシーン
 */
class TitleScene : public Scene<GameData>
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//宝石ロード確認UIの位置
	static constexpr DirectX::SimpleMath::Vector2 LOAD_CHECK_UI_POS = { 200.0f,400.0f };
	//宝石ロード確認UIのサイズ
	static constexpr DirectX::SimpleMath::Vector2 LOAD_CHECK_UI_SCALE = { 0.8f, 0.8f };
	//チェックマークUIの位置
	static constexpr DirectX::SimpleMath::Vector2 CHECK_MARK_UI_POS = { 200.0f,400.0f };
	//チェックマークUIのサイズ
	static constexpr DirectX::SimpleMath::Vector2 CHECK_MARK_UI_SCALE = { 0.8f, 0.8f };
	//タイトルUIの位置
	static constexpr DirectX::SimpleMath::Vector2 TITLE_UI_POS = { 640.0f,180.0f };
	//タイトルUIのサイズ
	static constexpr DirectX::SimpleMath::Vector2 TITLE_UI_SCALE = { 1.0f, 1.0f };
	//PRESS SPACEUIの位置
	static constexpr DirectX::SimpleMath::Vector2 PRESS_SPACE_UI_POS = { 640.0f,600.0f };
	//PRESS SPACEUIのサイズ
	static constexpr DirectX::SimpleMath::Vector2 PRESS_SPACE_UI_SCALE = { 1.0f, 1.0f };

// メンバ関数の宣言 -------------------------------------------------
// 取得/設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	TitleScene();
	// デストラクタ
	~TitleScene();
// 操作
	// 初期化処理
	void Initialize() override;
	//更新前準備
	void PreUpdate() override;
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
// 内部実装
private:

	// データメンバの宣言 -----------------------------------------------
private:
	//距離	
	float m_length;
	//角度
	float m_angle;
	//経過時間
	float m_time = 0.0f;
	//保存したプレイヤー所持している宝石を読み込むか
	bool m_isLoadPlayerHoldGem;
	
	// カメラオブジェクト
	std::unique_ptr<Camera> m_camera;    

	//タイトル画像
	std::unique_ptr<UserInterface> m_title;
	//PRESS SPACE画像
	std::unique_ptr<UserInterface> m_pressSpace;


	TKTLib::ModelParams m_caveModelParams;    ///< 洞窟モデルパラメータ
	TKTLib::ModelParams m_demoPlayerModelParams;
	std::unique_ptr<Player> m_demoPlayer;

	DirectX::Model* m_skyModel;

	std::unique_ptr<UserInterface> m_loadCheckUI;
	std::unique_ptr<UserInterface> m_checkUI;

	UserInterface m_light;

	std::unique_ptr<Sound> m_titleBGM;
	std::unique_ptr<Sound> m_gemLoadSound;
	std::unique_ptr<Sound> m_gameStartSound;

};
