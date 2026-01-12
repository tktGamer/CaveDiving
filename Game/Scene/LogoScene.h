/**
 * @file   LogoScene.h
 *
 * @brief  ロゴシーンに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/10
 */
// 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Common/SceneManager.h"
#include"Game/GameData.h"
#include"Game/Object/Camera.h"

#include"math.h"
#include"Game/UI/Animation2D.h"
#include"Game/Transitor/Transitor.h"
// クラスの宣言 ===============================================================
class ResourceManager;    ///< リソースマネージャ
class Sound;

// クラスの定義 ===============================================================
/**
 * @brief ロゴシーン
 */
class LogoScene : public Scene<GameData>
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
// 取得/設定
public:

// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	LogoScene();
	// デストラクタ
	~LogoScene();
// 操作
public:
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
	// アニメーションするクラス
	std::unique_ptr<Animation2D> m_logoAnimation;


};
