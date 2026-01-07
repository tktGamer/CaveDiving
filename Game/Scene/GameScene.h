/**
 * @file   GameScene.h
 *
 * @brief  ゲームシーンに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/11/20
 */

// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include"RenderTexture.h"
#include<unordered_map>
#include"../Common/SceneManager.h"
#include"../GameData.h"
#include"../Common/Sound.h"
#include"../Object/Camera.h"
#include"../Common/Collision/DisplayCollision.h"
#include"../Common/Collision/CollisionManager.h"
#include"../UI/Gauge/Gauge.h"
#include"../UI/HoldGem/HoldGem.h"
#include"../UI/Buff/BuffUIControl.h"
#include"../UI/ClearConditions/ClearConditions.h"
#include"../Object/Player/Player.h"
#include"../Object/Stage/Stage.h"
#include"../Object/Enemy/EnemyManager.h"
#include"../Object/Item/ItemManager.h"
#include"../Shader/Bloom.h"
// クラスの宣言 ===============================================================
class ResourceManager;    ///< リソースマネージャ




// クラスの定義 ===============================================================
/**
 * @brief ゲームシーン
 */
class GameScene : public Scene<GameData>
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:
	ResourceManager* m_pResourceManager;    ///< リソースマネージャ
	//衝突表示オブジェクト
	std::unique_ptr<Ito::DisplayCollision> m_displayCollision;
	CollisionManager* m_cM;

	std::unique_ptr<Sound> m_gameBGM;

	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	std::unique_ptr<Bloom> m_bloomEffect;
	//レンダーテクスチャ （シーン全体）
	std::unique_ptr<DX::RenderTexture> m_offScreenRT;

	//レンダーテクスチャ（ブラー）
	std::unique_ptr<DX::RenderTexture> m_blur1RT;
	std::unique_ptr<DX::RenderTexture> m_blur2RT;

	//ポストプロセス
	std::unique_ptr<DirectX::BasicPostProcess> m_basicPostProcess;
	//デュアルポストプロセス
	std::unique_ptr<DirectX::DualPostProcess> m_dualPostProcess;


	std::unique_ptr<EnemyManager> m_enemyManager; //<敵管理オブジェクト
	std::unique_ptr<Camera> m_camera;    ///< カメラオブジェクト
	std::unique_ptr<Player> m_player;    ///< プレイヤーオブジェクト
	std::unique_ptr<Stage> m_stage;    ///< ステージオブジェクト

	std::unique_ptr<Gauge> m_hpGauge;
	std::unique_ptr<HoldGem> m_holdGem;
	std::unique_ptr<BuffUIControl> m_buffUI;
	std::unique_ptr<ClearConditions> m_clearConditionsUI;

	std::unique_ptr<ItemManager> m_itemManager;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();


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

// 取得/設定
public:


// 内部実装
private:
	//ステージのライト状況を保存
	void SaveLight();
	//敵の生成
	void SpawnEnemy();
};
