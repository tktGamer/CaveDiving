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
#include"../Common/Collision/DisplayCollision.h"
#include"../Common/Collision/CollisionManager.h"
#include"../Object/Camera.h"
#include"../UI/Gauge/Gauge.h"
#include"../UI/ClearConditions/ClearConditions.h"
#include"../UI/Number/CountUpNumber.h"
#include"../UI/HoldGem/HoldGem.h"
#include"../UI/Buff/BuffUIControl.h"
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

// メンバ関数の宣言 -------------------------------------------------
// 取得/設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	GameScene();
	// デストラクタ
	~GameScene();
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
	void CreateUI();

	//ステージ終了判定
	const bool IsFinish();
	//プレイヤーの状態を保存
	void SavePlayer();
	//ステージのライト状況を保存
	void SaveLight();
	//敵の生成
	void SpawnEnemy();

// データメンバの宣言 -----------------------------------------------
private:
	ResourceManager* m_pResourceManager;    ///< リソースマネージャ
	//衝突表示オブジェクト
	std::unique_ptr<Ito::DisplayCollision> m_displayCollision;
	CollisionManager* m_collsionManager;

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


	//敵管理オブジェクト
	std::unique_ptr<EnemyManager> m_enemyManager; 
	// カメラオブジェクト
	std::unique_ptr<Camera> m_camera;    
	// プレイヤーオブジェクト
	std::unique_ptr<Player> m_player;    
	// ステージオブジェクト
	std::unique_ptr<Stage> m_stage;    

	std::unique_ptr<Gauge> m_hpGauge;
	std::unique_ptr<HoldGem> m_holdGem;
	std::unique_ptr<BuffUIControl> m_buffUI;
	std::unique_ptr<ClearConditions> m_clearConditionsUI;
	//std::unique_ptr<NumberControl> m_clearConditionsUI;

	std::unique_ptr<ItemManager> m_itemManager;




};
