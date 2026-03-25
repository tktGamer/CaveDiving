/**
 * @file   ResourcePath.h
 *
 * @brief  リソースのパスに関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2026/03/05
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#include<string>
class ResourcePath
{
private:
	//空行いれないと表示するときに上のコメントがすべて表示されるので一行あけている
	struct Ex
	{
		//例：A
		static constexpr wchar_t A[] = L"aaa";
		//例：B
		static constexpr wchar_t B[] = L"bbb";
	};

public:
	//テクスチャ
	//"Resources/Textures/" の次に続くパス
	struct TEXTURE
	{
		//モデルにつける用
		
		//白 
		static constexpr wchar_t WHITE[] = L"White.png";

		//コウモリ
		static constexpr wchar_t BAT[] = L"Bat.png";
		
		//コウモリの羽
		static constexpr wchar_t BAT_WING[] = L"Wing.png";
		
		//ゴーレム
		static constexpr wchar_t GOLEM[] = L"Golem.png";
		
		//ゴーレムの手
		static constexpr wchar_t GOLEM_HAND[] = L"GolemHand.png";
		
		//ゴーレムの腕
		static constexpr wchar_t GOLEM_ARM[] = L"GolemArm.png";
		
		//ゴーレムの足
		static constexpr wchar_t GOLEM_FOT[] = L"GolemFot.png";

		//岩
		static constexpr wchar_t ROCK[]  = L"Rock.png";
		
		//アイテム
		static constexpr wchar_t ITEM[]  = L"Item.png";
		
		//プレイヤー
		static constexpr wchar_t PLAYER[]  = L"Player.png";
		
		//プレイヤーの手
		static constexpr wchar_t PLAYER_HAND[]  = L"Hand.png";
		
		//ピッケル
		static constexpr wchar_t PIKEL[]  = L"Pikel.png";
		
		//地面
		static constexpr wchar_t GROUND[]  = L"Block.png";
		
		//壁
		static constexpr wchar_t WALL[]  = L"Block.png";
		
		//影用トゥーンマップ
		static constexpr wchar_t TOON_MAP[]  = L"ToonMap.png";

		//宝石用

		//UI用
		struct UI 
		{
			//ロゴ
			static constexpr wchar_t LOGO[]  = L"Logo.png";

			//タイトル
			static constexpr wchar_t TITLE[]  = L"UI/Title.png";
			
			//ローディングアニメーション画像
			static constexpr wchar_t LOAD[]  = L"UI/Loading.png";
			
			//ロードシーン背景
			static constexpr wchar_t LOAD_BACK[]  = L"Loadback.jpg";
			
			//宝石選択シーン背景
			static constexpr wchar_t GEM_BACK[]  = L"UI/GemSelectBack.png";
			
			//スタート時宝石を読み込むか
			static constexpr wchar_t LOAD_GEM_CHECK[]  = L"UI/LoadGemCheck.png";
			
			//スタート時宝石を読み込むか用のチェック
			static constexpr wchar_t CHECK[]  = L"UI/Check.png";
			
			//攻撃力UPバフ
			static constexpr wchar_t ATTACK_BUFF[]  = L"UI/AttackBuff.png";
			
			//防御力UPバフ
			static constexpr wchar_t DIFFENCE_BUFF[]  = L"UI/DiffenceBuff.png";
			
			//アウトライン表示バフ
			static constexpr wchar_t OUTLINE_BUFF[]  = L"UI/outlineBuff.png";
			
			//敵アイコン
			static constexpr wchar_t ENEMY_ICON[]  = L"UI/enemyIcon.png";
			
			//HPゲージ
			static constexpr wchar_t HPGAUGE[]  = L"UI/hpgauge.png";
			
			//HPゲージの枠
			static constexpr wchar_t HPGAUGE_FRAME[]  = L"UI/HpGaugeFrame.png";
			
			//矢印
			static constexpr wchar_t ARROW[]  = L"UI/Arrow.png";

			//所持宝石のスロット
			static constexpr wchar_t GEM_SLOT[]  = L"slot.png";

			//カーソル
			static constexpr wchar_t RED_CURSOL[]  = L"UI/Cursol.png";
			
			//PRESS SPACE文字
			static constexpr wchar_t PRESS_SPACE[]  = L"UI/PressSpace.png";
			
			//入れ替えUIに遷移するか確認する表示
			static constexpr wchar_t CHANGE_MESSAGE[]  = L"UI/ChangeMessage.png";

			//所持宝石を保存するかの確認表示
			static constexpr wchar_t SAVE_MESSAGE[]  = L"UI/SaveMessage.png";
			
			//取得しない
			static constexpr wchar_t NOT_CHOOSE_MESSAGE[]  = L"UI/notacquiredframe.png";
			
			//選択肢のフレーム
			static constexpr wchar_t MENU_FRAME[]  = L"UI/buttonframe.png";
			
			//はい
			static constexpr wchar_t YES[]  = L"UI/YesFont.png";
			
			//いいえ
			static constexpr wchar_t NO[]  = L"UI/NoFont.png";
			
			//入れ替える
			static constexpr wchar_t CHANGE[]  = L"UI/ChangeFont.png";
			
			//戻る
			static constexpr wchar_t RETURN[]  = L"UI/ReturnFont.png";
			
			//スコア
			static constexpr wchar_t SCORE[]  = L"UI/score.png";
			
			//残りHP
			static constexpr wchar_t CURRENT_HP[]  = L"UI/currenthp.png";
			
			//:
			static constexpr wchar_t COLON[]  = L"UI/colon.png";
			
			//トータルダメージ
			static constexpr wchar_t TOTAL_DAMAGE[]  = L"UI/totaldamage.png";
			
			//経過時間
			static constexpr wchar_t TOTAL_TIME[]  = L"UI/totaltime.png";

			//数字　0～9
			static constexpr wchar_t NUMBER[]  = L"Number.png";

			//ゲームクリア
			static constexpr wchar_t GAME_CLEAR[]  = L"UI/GameClear.png";
			
			//ゲームオーバー
			static constexpr wchar_t GAME_OVER[]  = L"UI/GameOver.png";
			
			//攻撃行動
			static constexpr wchar_t ATTACK_ACTION[]  = L"UI/Action/Attack.png";
			
			//回避行動
			static constexpr wchar_t AVOID_ACTION[]  = L"UI/Action/Avoid.png";
			
			//ジャンプ行動
			static constexpr wchar_t JUMP_ACTION[]  = L"UI/Action/Jump.png";
			
			//回転行動
			static constexpr wchar_t ROTATION_ACTION[]  = L"UI/Action/Rotation.png";

			//移動行動
			static constexpr wchar_t MOVE_ACTION[]  = L"UI/Action/Move.png";

			//キー画像
			struct Key 
			{
				//空白
				static constexpr wchar_t NONE[]  = L"UI/Key/Key.png";

				//Z
				static constexpr wchar_t Z[]  = L"UI/Key/ZKey.png";
				//X
				static constexpr wchar_t X[]  = L"UI/Key/XKey.png";
				//C
				static constexpr wchar_t C[]  = L"UI/Key/CKey.png";
				//shift
				static constexpr wchar_t SHIFT[]  = L"UI/Key/ShiftKey.png";
				//space
				static constexpr wchar_t SPACE[]  = L"UI/Key/SpaceKey.png";
				//左矢印
				static constexpr wchar_t LEFT_ARROW[]  = L"UI/Key/LeftArrowKey.png";
				//上矢印
				static constexpr wchar_t UP_ARROW[]  = L"UI/Key/UpArrowKey.png";
				//右矢印
				static constexpr wchar_t RIGHT_ARROW[]  = L"UI/Key/RightArrowKey.png";
				//下矢印
				static constexpr wchar_t DOWN_ARROW[]  = L"UI/Key/DownArrowKey.png";
			};

		};
		//宝石画像
		struct GEM
		{
			//空
			static constexpr wchar_t BLANK_GEM[]  = L"Gem/blankgem.png";

			//エメラルド
			static constexpr wchar_t EMERALD[]  = L"Gem/emerald.png";

			//ルビー
			static constexpr wchar_t RUBY[]  = L"Gem/ruby.png";

			//サファイア
			static constexpr wchar_t SAPPHIRE[]  = L"Gem/sapphire.png";

			//トパーズ
			static constexpr wchar_t TOPAZ[]  = L"Gem/topaz.png";

			//アメジスト
			static constexpr wchar_t AMETHYST[]  = L"Gem/amethyst.png";

			//アクアマリン
			static constexpr wchar_t AQUAMARINE[]  = L"Gem/Aquamarine.png";

			//モルガナイト
			static constexpr wchar_t MORGANITE[]  = L"Gem/morganite.png";

			//スピネル
			static constexpr wchar_t SPINEL[]  = L"Gem/Spinel.png";
		};
		//パーティクル
		struct PARTICLE 
		{
			//消滅
			static constexpr wchar_t VANISH[]     = L"Particle/Vanish.png";
			
			//HP回復
			static constexpr wchar_t HP_HEAL[]    = L"Particle/HPHeal.png";
			
			//土埃
			static constexpr wchar_t MOVE_DUST[]  = L"Particle/GroundDust.png";
			
			//数字
			static constexpr wchar_t NUMBER[]     = L"Particle/Number.png";
			
			//アイテムゲット
			static constexpr wchar_t ITEM_GET[]   = L"Particle/ItemGet.png";
			
			//パワーアップ
			static constexpr wchar_t POWER_UP[]   = L"Particle/PowerUp.png";
			
			//シールド
			static constexpr wchar_t SHIELD[]     = L"Particle/Shield.png";

		};
		

	};
	//モデル
	//"Resources/Models/" の次に続くパス
	struct MODEL
	{
		//タイトル画面の洞窟
		static constexpr wchar_t TITLE_CAVE[] = L"Cave.sdkmesh";

		//タイトルの天球
		static constexpr wchar_t SKY_DOME[] = L"SkyDome.sdkmesh";

		//コウモリ
		static constexpr wchar_t BAT[] = L"Bat.sdkmesh";

		//コウモリの羽
		static constexpr wchar_t BAT_WING[] = L"Wing.sdkmesh";

		//ゴーレム
		static constexpr wchar_t GOLEM[] = L"Golem.sdkmesh";

		
		//ゴーレムの手
		static constexpr wchar_t GOLEM_HAND[] = L"GolemHand.sdkmesh";

		//ゴーレムの腕
		static constexpr wchar_t GOLEM_ARM[] = L"GolemArm.sdkmesh";
		
		//ゴーレムの足
		static constexpr wchar_t GOLEM_FOT[] = L"GolemFot.sdkmesh";
		
		//アイテム
		static constexpr wchar_t ITEM[] = L"Item.sdkmesh";
		
		//プレイヤー
		static constexpr wchar_t PLAYER[] = L"Player.sdkmesh";
		
		//プレイヤーの手
		static constexpr wchar_t PLAYER_HAND[] = L"Hand.sdkmesh";
		
		//ピッケル
		static constexpr wchar_t PIKEL[] = L"Pikel.sdkmesh";
		
		//光る石
		static constexpr wchar_t RUMI_ROCK[] = L"Rock.sdkmesh";
		
		//地面
		static constexpr wchar_t GROUND[] = L"Block.sdkmesh";
		
		//壁
		static constexpr wchar_t WALL[] = L"Cave_Game.sdkmesh";
	};
	//音
	//"Resources/Sounds/" の次に続くパス
	struct SOUND
	{
		//タイトルBGM
		static constexpr wchar_t TITLE_BGM[] = L"TitleBGM.wav";

		//ゲームBGM
		static constexpr wchar_t GAME_BGM[] = L"GameBGM.wav";
		
		//宝石ロードON・OFF
		static constexpr wchar_t TITLE_GEM_LOAD[] = L"TitleGemLoad.wav";
		
		//ゲームスタート
		static constexpr wchar_t GAME_START[] = L"GameStart.wav";
		//プレイヤー横なぎ攻撃音
		static constexpr wchar_t PLAYER_SWING[] = L"PikelSwing.wav";

		//プレイヤー回転攻撃音
		static constexpr wchar_t PLAYER_SPIN[] = L"TurnAttack.wav";
		
		//ジャンプ音
		static constexpr wchar_t PLAYER_JUMP[] = L"Jump.wav";
		
		//コウモリの攻撃音
		static constexpr wchar_t BAT_ATTACK[] = L"BatAttack.wav";
		
		//コウモリの羽ばたき音
		static constexpr wchar_t BAT_WING[]   = L"Wing.wav";
		
		//ゴーレムのパンチ音
		static constexpr wchar_t GOLEM_PUNCH[]   = L"GolemPunch.wav";
		
		//ゴーレムの叩きつけ音
		static constexpr wchar_t GOLEM_SLAMMED_DOWN[]   = L"GolemSlam.wav";
		
		//敵消滅音
		static constexpr wchar_t ENEMY_VANISH[]   = L"EnemyVanish.wav";
		
		//アイテムゲット音
		static constexpr wchar_t ITEM_GET[]   = L"GetItem.wav";
		
		//攻撃ヒット音
		static constexpr wchar_t ATTACK_HIT[]   = L"AttackHit.wav";
		
		//光る石が光る音
		static constexpr wchar_t LUMI_ROCK_RIGHT_ON[]   = L"LumiRockLightOn.wav";
		
		//メニュー移動音
		static constexpr wchar_t CURSOL_MOVE[]   = L"CursorMove.wav";
		
		//決定音
		static constexpr wchar_t DECIDE[]   = L"decidegem.wav";
		
		//メニュー決定音
		static constexpr wchar_t MENU_DECIDE[]   = L"DecideMenu.wav";
		
		//ゲームクリア音
		static constexpr wchar_t GAME_CLEAR[]   = L"GameClear.wav";
		
		//UI表示音
		static constexpr wchar_t SHOW_CONFIRM[]   = L"ShowConfirmUI.wav";
	};
	//シェーダー
	struct SHADER
	{
		//モデルシェーダー---------------------
		static constexpr wchar_t MODEL_VS[] = L"Resources/Shaders/ModelShader/ModelVS.cso";
		static constexpr wchar_t MODEL_PS[] = L"Resources/Shaders/ModelShader/ModelPS.cso";
		static constexpr wchar_t MODEL_GS[] = L"Resources/Shaders/ModelShader/ModelGS.cso";

		//アイテムモデルシェーダー
		static constexpr wchar_t ITEM_MODEL_PS[] = L"Resources/Shaders/ModelShader/ItemModelPS.cso";
		
		//壁モデルシェーダー
		static constexpr wchar_t WALL_MODEL_PS[] = L"Resources/Shaders/ModelShader/WallPS.cso";
		
		//光る岩モデルシェーダー
		static constexpr wchar_t LUMI_ROCK_PS[] = L"Resources/Shaders/LumiRockShader/LumiRockPS.cso";

		//UIシェーダー--------------------------
		static constexpr wchar_t UI_VS[] = L"Resources/Shaders/UIShader/UIVS.cso";
		static constexpr wchar_t UI_PS[] = L"Resources/Shaders/UIShader/UIPS.cso";
		static constexpr wchar_t UI_GS[] = L"Resources/Shaders/UIShader/UIGS.cso";
		
		//KeyUIシェーダー--------------------------
		static constexpr wchar_t KEY_UI_VS[] = L"Resources/Shaders/KeyUIShader/KeyUIVS.cso";
		static constexpr wchar_t KEY_UI_PS[] = L"Resources/Shaders/KeyUIShader/KeyUIPS.cso";
		static constexpr wchar_t KEY_UI_GS[] = L"Resources/Shaders/KeyUIShader/KeyUIGS.cso";
		
		//パーティクルシェーダー----------------
		static constexpr wchar_t PARTICLE_VS[] = L"Resources/Shaders/ParticleShader/ParticleVS.cso";
		static constexpr wchar_t PARTICLE_PS[] = L"Resources/Shaders/ParticleShader/ParticlePS.cso";
		static constexpr wchar_t PARTICLE_GS[] = L"Resources/Shaders/ParticleShader/ParticleGS.cso";
		
		//フェードシェーダー--------------------
		static constexpr wchar_t FADE_VS[] = L"Resources/Shaders/FadeShader/FadeVS.cso";
		static constexpr wchar_t FADE_PS[] = L"Resources/Shaders/FadeShader/FadePS.cso";
		static constexpr wchar_t FADE_GS[] = L"Resources/Shaders/FadeShader/FadeGS.cso";
		
		//アウトラインシェーダー----------------
		static constexpr wchar_t OUTLINE_VS[] = L"Resources/Shaders/OutlineShader/OutlineVS.cso";
		static constexpr wchar_t OUTLINE_PS[] = L"Resources/Shaders/OutlineShader/OutlinePS.cso";
		static constexpr wchar_t OUTLINE_GS[] = L"Resources/Shaders/OutlineShader/OutlineGS.cso";
		
		//数字2Dシェーダー----------------------
		static constexpr wchar_t NUMBER2D_VS[] = L"Resources/Shaders/NumberShader/NumberVS.cso";
		static constexpr wchar_t NUMBER2D_PS[] = L"Resources/Shaders/NumberShader/NumberPS.cso";
		static constexpr wchar_t NUMBER2D_GS[] = L"Resources/Shaders/NumberShader/NumberGS.cso";
		
		//数字3Dシェーダー----------------------
		static constexpr wchar_t NUMBER3D_VS[] = L"Resources/Shaders/NumberShader/3D/Number3DVS.cso";
		static constexpr wchar_t NUMBER3D_PS[] = L"Resources/Shaders/NumberShader/3D/Number3DPS.cso";
		static constexpr wchar_t NUMBER3D_GS[] = L"Resources/Shaders/NumberShader/3D/Number3DGS.cso";
		//2Dアニメーションシェーダー----------------------
		static constexpr wchar_t ANIMATION2D_VS[] = L"Resources/Shaders/Animation2DShader/Animation2DVS.cso";
		static constexpr wchar_t ANIMATION2D_PS[] = L"Resources/Shaders/Animation2DShader/Animation2DPS.cso";
		static constexpr wchar_t ANIMATION2D_GS[] = L"Resources/Shaders/Animation2DShader/Animation2DGS.cso";
	};
	//データ
	struct DATA
	{
		//ステージごとの敵生成データ
		struct ENEMY_SPAWN 
		{
			static constexpr char FIRST[]  = "Resources/Data/EnemySpawn/FirstStageData.csv";
			static constexpr char SECOND[] = "Resources/Data/EnemySpawn/SecondStageData.csv";
			static constexpr char THIRD[]  = "Resources/Data/EnemySpawn/ThirdStageData.csv";
			static constexpr char FORTH[]  = "Resources/Data/EnemySpawn/ForthStageData.csv";
			static constexpr char BOSS[]  = "Resources/Data/EnemySpawn/BossStageData.csv";
		};
		struct HOLDER_GEM 
		{
			//プレイヤーの所持宝石を保存するファイル
			static constexpr char PLAYER_GEM[]  = "Resources/Data/HolderGem/PlayerHoldGems.txt";

		};
		//アイテムデータ
		static constexpr char ITEM_DATA[] = "Resources/Data/ItemData.csv";
		
		//アイテム配置データ
		static constexpr char ITEM_POSTION[] = "Resources/Data/ItemData.csv";
		
		//ライト情報
		static constexpr char LIGHT[] = "Resources/Data/LightPositionData.csv";

		//宝石
		static constexpr char GEM[] = "Resources/Data/GemData.csv";
	};
};


