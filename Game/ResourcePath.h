/**
 * @file   ResourcePath.h
 *
 * @brief  リソースのパスに関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2025/12/23
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#include<string>
class ResourcePath
{
public:
	//テクスチャ
	//"Resources/Textures/" の次に続くパス
	struct TEXTURE
	{
		//モデルにつける用
		static constexpr wchar_t BAT[] = L"Bat.png";
		static constexpr wchar_t GOLEM[] = L"Golem.png";
		static constexpr wchar_t GOLEM_HAND[] = L"GolemHand.png";
		static constexpr wchar_t BLOCK[] = L"Resources/Texture/block.png";
		static constexpr wchar_t ROCK[]  = L"Rock.png";
		static constexpr wchar_t ITEM[]  = L"Item.png";
		static constexpr wchar_t PLAYER[]  = L"Player.png";
		static constexpr wchar_t PLAYER_HAND[]  = L"Hand.png";
		static constexpr wchar_t PIKEL[]  = L"Pikel.png";

		//宝石用

		//UI用
		struct UI 
		{
			static constexpr wchar_t LOGO[]  = L"Logo.png";
			static constexpr wchar_t TITLE[]  = L"UI/Title.png";
			static constexpr wchar_t PRESS_SPACE[]  = L"UI/PressSpace.png";
			static constexpr wchar_t NUMBER[]  = L"Number.png";

		};
		//パーティクル
		struct PARTICLE 
		{
			static constexpr wchar_t VANISH[]     = L"Particle/Vanish.png";
			static constexpr wchar_t HP_HEAL[]    = L"Particle/HPHeal.png";
			static constexpr wchar_t MOVE_DUST[]  = L"Particle/GroundDust.png";
			static constexpr wchar_t NUMBER[]     = L"Particle/Number.png";
			static constexpr wchar_t ITEM_GET[]   = L"Particle/ItemGet.png";
			static constexpr wchar_t POWER_UP[]   = L"Particle/PowerUp.png";
			static constexpr wchar_t SHIELD[]     = L"Particle/Shield.png";

		};
		

	};
	//モデル
	//"Resources/Models/" の次に続くパス
	struct MODEL
	{
		static constexpr wchar_t BAT[] = L"Bat.sdkmesh";
		static constexpr wchar_t GOLEM[] = L"Golem.sdkmesh";
		static constexpr wchar_t GOLEM_HAND[] = L"GolemHand.sdkmesh";
		static constexpr wchar_t ITEM[] = L"Item.sdkmesh";
		static constexpr wchar_t PLAYER[] = L"Player.sdkmesh";
		static constexpr wchar_t PLAYER_HAND[] = L"Hand.sdkmesh";
		static constexpr wchar_t PIKEL[] = L"Pikel.sdkmesh";
		static constexpr wchar_t RUMI_ROCK[] = L"Rock.sdkmesh";
	};
	//音
	//"Resources/Sounds/" の次に続くパス
	struct SOUND
	{
		//プレイヤー攻撃音
		static constexpr wchar_t PLAYER_SWING[] = L"PikelSwing.wav";
		static constexpr wchar_t PLAYER_SPIN[] = L"TurnAttack.wav";
		//コウモリの攻撃音
		static constexpr wchar_t BAT_ATTACK[] = L"BatAttack.wav";
		//コウモリの羽ばたき音
		static constexpr wchar_t BAT_WING[]   = L"Wing.wav";
		//ゴーレムのパンチ音
		static constexpr wchar_t GOLEM_PUNCH[]   = L"GolemPunch.wav";
		//ゴーレムの叩きつけ音
		static constexpr wchar_t GOLEM_SLAMMED_DOWN[]   = L"GolemSlam.wav";
		//アイテムゲット音
		static constexpr wchar_t ITEM_GET[]   = L"GetItem.wav";

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
		//アイテム
		static constexpr char ITEM[] = "Resources/Data/ItemData.csv";
	};
};


