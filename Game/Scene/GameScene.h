/**
 * @file   GameScene.h
 *
 * @brief  ゲームシーンに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Scene.h"
#include"Game/Common/Sound.h"
#include"Game/Object/Camera.h"
#include"Game/Object/Player/Player.h"
#include"Game/Object/Stage.h"
#include"Game/Common/Collision/DisplayCollision.h"

// クラスの宣言 ===============================================================
class ResourceManager;    ///< リソースマネージャ
class SceneManager;       ///< シーンマネージャ




// クラスの定義 ===============================================================
/**
 * @brief ゲームシーン
 */
class GameScene : public Scene
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:
	// システム関連
	ResourceManager* m_pResourceManager;    ///< リソースマネージャ
	//衝突表示オブジェクト
	std::unique_ptr<Ito::DisplayCollision> m_displayCollision;

	// オブジェクト関連
	std::unique_ptr<Camera> m_camera;    ///< カメラオブジェクト
	std::unique_ptr<Player> m_player;    ///< プレイヤーオブジェクト
	std::unique_ptr<Stage> m_stage;    ///< ステージオブジェクト
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GameScene(SceneManager* pSceneManager);

	// デストラクタ
	~GameScene();


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
