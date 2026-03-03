/**
 * @file   GameScene.h
 *
 * @brief  ゲームシーンに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/28
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
class ResourceManager;
// クラスの定義 ===============================================================
/**
 * @brief ゲームシーン
 */
class PlayScene : public Scene<GameData>
{
// クラス定数の宣言 -------------------------------------------------
public:
	//１秒あたりの回転量
	static constexpr  float ROTATION_SPEED_Y_ANGLE = DirectX::XMConvertToRadians(180.0f);
	//カメラ初期位置
	static constexpr DirectX::SimpleMath::Vector3 CAMERA_INIT_POSITION = { 0.0f, 7.0f, 25.0f };
	//カメラ初期距離
	static constexpr DirectX::SimpleMath::Vector3 CAMERA_INIT_DISTANCE = { 0.0f, 7.0f, 25.0f };

// メンバ関数の宣言 -------------------------------------------------
// 取得/設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	PlayScene();
	// デストラクタ
	virtual ~PlayScene();
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
	//キーボード入力
	void PressKeyBoard();
	//移動メッセージ
	void MovingMessage(const int& operateObjectID);
	//視点回転
	void RotateDirection(const int& operateObjectID, const bool& isRotateRight);
	//UI生成
	void CreateUI();
	//敵の生成
	void SpawnEnemy();

	//ステージ終了判定
	const bool IsFinish();
	//プレイヤーの状態を保存
	void SavePlayer();
	//ステージのライト状況を保存
	void SaveLight();

// データメンバの宣言 -----------------------------------------------
private:
	//衝突表示オブジェクト
	std::unique_ptr<Ito::DisplayCollision> m_displayCollision;
	//当たり判定管理
	CollisionManager* m_collsionManager;
	//ゲーム音楽
	std::unique_ptr<Sound> m_gameBGM;

	//
	std::unique_ptr<Bloom> m_bloomEffect;
	//レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;
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
	//アイテム管理
	std::unique_ptr<ItemManager> m_itemManager;
	//プレイヤーのHPゲージUI
	std::unique_ptr<Gauge> m_hpGauge;
	//所持宝石UI
	std::unique_ptr<HoldGem> m_holdGem;
	//バフ表示UI
	std::unique_ptr<BuffUIControl> m_buffUI;
	//残りの敵数UI
	std::unique_ptr<ClearConditions> m_clearConditionsUI;
	//std::unique_ptr<NumberControl> m_clearConditionsUI;
};