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
#include"Game/Command/InputHandler.h"
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
#include"Game/RenderPipeLine.h"
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
	//プレイヤー初期位置
	static constexpr DirectX::SimpleMath::Vector3 PLAYER_INIT_POSITION = { 0.0f, 0.8f, 0.0f };
	//ステージ中心位置
	static constexpr DirectX::SimpleMath::Vector3 STAGE_CENTER_POS = { 0.0f, 0.8f, 0.0f };
	//地面の初期位置
	static constexpr DirectX::SimpleMath::Vector3 INITIAL_GROUND_POS = { 0.0f, -1.5f, 0.0f };
	//地面の初期サイズ
	static constexpr DirectX::SimpleMath::Vector3 INITIAL_GROUND_SCALE = { 70.0f, 1.0f, 70.0f };
	//壁の初期位置
	static constexpr DirectX::SimpleMath::Vector3 INITIAL_WALL_POS = { 0.0f, 0.0f, 0.0f };
	//壁の初期サイズ
	static constexpr DirectX::SimpleMath::Vector3 INITIAL_WALL_SCALE = { 60.0f, 50.0f, 60.0f };
	//石の数
	static constexpr int ROCK_NUM = 10;
	//クリア条件UIの位置
	static constexpr DirectX::SimpleMath::Vector2 CLEAR_CONDITION_UI_POS = { 1240.0f,150.0f };
	//HPゲージUIの位置
	static constexpr DirectX::SimpleMath::Vector2 HP_GAUGE_UI_POS = { 45.0f,50.0f };
	//所持宝石表示位置
	static constexpr DirectX::SimpleMath::Vector2 HOLD_GEM_UI_POS = { 80.0f,680.0f };

	//操作方法表示UI
	//攻撃方法キーUI位置
	static constexpr DirectX::SimpleMath::Vector2 ATTACK_KEY_UI_POS = { 650.0f,680.0f };
	//攻撃方法キーUIサイズ
	static constexpr DirectX::SimpleMath::Vector2 ATTACK_KEY_UI_SCALE = { 0.3f,0.3f };
	//攻撃動作UI位置
	static constexpr DirectX::SimpleMath::Vector2 ATTACK_ACTION_UI_POS = { 650.0f,615.0f };
	//攻撃動作UIサイズ
	static constexpr DirectX::SimpleMath::Vector2 ATTACK_ACTION_UI_SCALE = { 0.2f,0.2f };
	//回避方法キーUI位置
	static constexpr DirectX::SimpleMath::Vector2 AVOID_KEY_UI_POS = { 760.0f,680.0f };
	//回避方法キーUIサイズ
	static constexpr DirectX::SimpleMath::Vector2 AVOID_KEY_UI_SCALE = { 0.3f,0.3f };
	//回避動作UI位置
	static constexpr DirectX::SimpleMath::Vector2 AVOID_ACTION_UI_POS = { 760.0f,615.0f };
	//回避動作UIサイズ
	static constexpr DirectX::SimpleMath::Vector2 AVOID_ACTION_UI_SCALE = { 0.2f,0.18f };
	//ジャンプ方法キーUI位置
	static constexpr DirectX::SimpleMath::Vector2 JUMP_KEY_UI_POS = { 860.0f,680.0f };
	//ジャンプ方法キーUIサイズ
	static constexpr DirectX::SimpleMath::Vector2 JUMP_KEY_UI_SCALE = { 0.3f,0.3f };
	//ジャンプ動作UI位置
	static constexpr DirectX::SimpleMath::Vector2 JUMP_ACTION_UI_POS = { 870.0f,620.0f };
	//ジャンプ動作UIサイズ
	static constexpr DirectX::SimpleMath::Vector2 JUMP_ACTION_UI_SCALE = { 0.2f,0.18f };
	//視点左回転方法キーUI位置
	static constexpr DirectX::SimpleMath::Vector2 LEFT_ROTATION_KEY_UI_POS = { 990.0f,680.0f };
	//視点左回転方法キーUIサイズ
	static constexpr DirectX::SimpleMath::Vector2 LEFT_ROTATION_KEY_UI_SCALE = { 0.3f,0.3f };
	//視点右回転方法キーUI位置
	static constexpr DirectX::SimpleMath::Vector2 RIGHT_ROTATION_KEY_UI_POS = { 1060.0f,680.0f };
	//視点右回転方法キーUIサイズ
	static constexpr DirectX::SimpleMath::Vector2 RIGHT_ROTATION_KEY_UI_SCALE = { 0.3f,0.3f };
	//視点回転動作UI位置
	static constexpr DirectX::SimpleMath::Vector2 ROTATION_ACTION_UI_POS = { 1040.0f,620.0f };
	//視点回転動作UIサイズ
	static constexpr DirectX::SimpleMath::Vector2 ROTATION_ACTION_UI_SCALE = { 0.25f,0.25f };
	//左移動方法キーUI位置
	static constexpr DirectX::SimpleMath::Vector2 LEFT_MOVE_KEY_UI_POS = { 1138.0f,700.0f };
	//左移動方法キーUIサイズ
	static constexpr DirectX::SimpleMath::Vector2 LEFT_MOVE_KEY_UI_SCALE = { 0.2f,0.2f };
	//前移動方法キーUI位置
	static constexpr DirectX::SimpleMath::Vector2 FRONT_MOVE_KEY_UI_POS = { 1170.0f,668.0f };
	//前移動方法キーUIサイズ
	static constexpr DirectX::SimpleMath::Vector2 FRONT_MOVE_KEY_UI_SCALE = { 0.2f,0.2f };
	//右移動方法キーUI位置
	static constexpr DirectX::SimpleMath::Vector2 RIGHT_MOVE_KEY_UI_POS = { 1202.0f,700.0f };
	//右移動方法キーUIサイズ
	static constexpr DirectX::SimpleMath::Vector2 RIGHT_MOVE_KEY_UI_SCALE = { 0.2f,0.2f };
	//後ろ移動方法キーUI位置
	static constexpr DirectX::SimpleMath::Vector2 BACK_MOVE_KEY_UI_POS = { 1170.0f,700.0f };
	//後ろ移動方法キーUIサイズ
	static constexpr DirectX::SimpleMath::Vector2 BACK_MOVE_KEY_UI_SCALE = { 0.2f,0.2f };
	//移動動作UI位置
	static constexpr DirectX::SimpleMath::Vector2 MOVE_ACTION_UI_POS = { 1175.0f,620.0f };
	//移動動作UIサイズ
	static constexpr DirectX::SimpleMath::Vector2 MOVE_ACTION_UI_SCALE = { 0.2f,0.2f };


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
	//入力処理生成
	void CreateInputCommand();
	//オブジェクト生成
	void CreateObjects();
	//UI生成
	void CreateUI();
	//敵の生成
	void SpawnEnemy();
	//石生成
	void GenerateIlumiRock(bool* isOnLight, int size);

	//ステージ終了判定
	const bool IsFinish();
	//プレイヤーの状態を保存
	void SavePlayer();
	//ステージのライト状況を保存
	void SaveLight();

// データメンバの宣言 -----------------------------------------------
private:
	//キー入力管理
	std::unique_ptr<InputHandler> m_inputHandler;
	//衝突表示オブジェクト
	std::unique_ptr<Ito::DisplayCollision> m_displayCollision;
	//当たり判定管理
	CollisionManager* m_collsionManager;
	//ゲーム音楽
	std::unique_ptr<Sound> m_gameBGM;

	std::unique_ptr<RenderPipeLine> m_renderPipeLine;

	//オブジェクトリスト
	std::list<IComponent*> m_objects;
	//敵管理オブジェクト
	std::unique_ptr<EnemyManager> m_enemyManager; 
	// カメラオブジェクト
	std::unique_ptr<Camera> m_camera;    
	// プレイヤーオブジェクト
	std::unique_ptr<Player> m_player;    
	//外壁
	std::unique_ptr<Wall> m_wall;
	//地面
	std::unique_ptr<Ground> m_ground;
	//発光する岩
	std::list<std::unique_ptr<RumiRock>> m_rocks;

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