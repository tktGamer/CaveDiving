/**
 * @file   GemSelectScene.h
 *
 * @brief  宝石選択シーンに関するヘッダファイル
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
#include"Game/UI/GemSelect/GemSelect.h"
#include"../UI/HoldGem/HoldGem.h"
#include"Game/UI/GemSelectUIManager.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
 * @brief ロゴシーン
 */
class GemSelectScene : public Scene<GameData>
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//背景テクスチャの位置
	static constexpr DirectX::SimpleMath::Vector2 BACK_TEXTURE_POS   = { 650.0f, 360.0f };
	//背景テクスチャのサイズ
	static constexpr DirectX::SimpleMath::Vector2 BACK_TEXTURE_SCALE = { 1.0f, 1.0f };
// メンバ関数の宣言 -------------------------------------------------
// 取得/設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	GemSelectScene();
	// デストラクタ
	~GemSelectScene();
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
	//宝石の選択UI群
	std::unique_ptr<GemSelectUIManager> m_gemSelectManager;
	//背景
	std::unique_ptr<UserInterface> m_backTexture;
};
