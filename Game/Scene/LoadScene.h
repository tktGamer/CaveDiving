/**
 * @file   LoadScene.h
 *
 * @brief  ロードシーンに関するヘッダファイル
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
#include"math.h"
#include"Game/UI/UserInterface.h"
#include"../UI/Animation2D.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
 * @brief ロゴシーン
 */
class LoadScene : public  Scene<GameData>
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//==NowLoading画像のデータ==//
	//総フレーム数
	static constexpr int NOWLOADING_FRAME_COUNT = 4;
	//横の数
	static constexpr int NOWLOADING_FRAME_WIDTH = 1;
	//縦の数
	static constexpr int NOWLOADING_FRAME_HEIGHT = 4;
	//アニメーション時間
	static constexpr float NOWLOADING_ANIMATION_TIME = 8;
	//位置
	static constexpr DirectX::SimpleMath::Vector2 NOWLOADING_POSITON = { 800.0f,590.0f };
	//サイズ
	static constexpr DirectX::SimpleMath::Vector2 NOWLOADING_SCALE = { 1.0f,1.0f };

	//背景テクスチャの位置
	static constexpr DirectX::SimpleMath::Vector2 BACK_TEXTURE_POS = { 0.0f, 0.0f };
	//背景テクスチャのサイズ
	static constexpr DirectX::SimpleMath::Vector2 BACK_TEXTURE_SCALE = { 0.7f, 0.7f };

// メンバ関数の宣言 -------------------------------------------------
// 取得/設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	LoadScene();
	// デストラクタ
	~LoadScene();
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
	//NowLoading画像
	std::unique_ptr<Animation2D> m_nowloadingTexture;	
	// 背景画像
	std::unique_ptr<UserInterface> m_backTexture;	
};
