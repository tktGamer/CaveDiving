/**
 * @file   TitleScene.h
 *
 * @brief  ロゴシーンに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Scene.h"
#include"Game/Object/Camera.h"

#include"math.h"

// クラスの宣言 ===============================================================
class ResourceManager;    ///< リソースマネージャ
class SceneManager;       ///< シーンマネージャ




// クラスの定義 ===============================================================
/**
 * @brief ロゴシーン
 */
class TitleScene : public Scene
{
// クラス定数の宣言 -------------------------------------------------
public:



// データメンバの宣言 -----------------------------------------------
private:
	// システム関連
	ResourceManager* m_pResourceManager;    ///< リソースマネージャ
	float m_length;
	float m_angle;

	// オブジェクト関連
	std::unique_ptr<Camera> m_camera;    ///< カメラオブジェクト
	ID3D11ShaderResourceView* m_titleTexture;	///< タイトル画像

	TKTLib::ModelParams m_caveModelParams;    ///< 洞窟モデルパラメータ
	TKTLib::ModelParams m_demoPlayerModelParams;    ///< プレイヤーモデルパラメータ

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	TitleScene(SceneManager* pSceneManager);

	// デストラクタ
	~TitleScene();


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


// 取得/設定
public:


// 内部実装
private:


};
