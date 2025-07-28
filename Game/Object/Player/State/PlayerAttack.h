#pragma once
#ifndef PLAYER_ATTACK_DEFINED
#define PLAYER_ATTACK_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
#include"Game/Object/Player/Hand.h"

class Player;
// PlayerAttackクラスを定義する
class PlayerAttack : public IState
{
public:
	// コンストラクタ
	PlayerAttack(Player* player,Hand* hand);
	// デストラクタ
	~PlayerAttack();
	// 初期化する
	void Initialize();
	// 事前更新する
	void PreUpdate();
	// 更新する
	void Update(const float& elapsedTime);
	// 事後更新する
	void PostUpdate();
	// 描画する
	void Render();
	// 後処理を行う
	void Finalize();


	bool Motion();
private:
	// プレイヤー
	Player* m_player;
	// グラフィックス
	Graphics* m_graphics;
	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;

	//モーションさせる手
	Hand* m_pHand;
	//
	float m_motionLerp;
};

#endif		// SOLDIER_IDLING_DEFINED
