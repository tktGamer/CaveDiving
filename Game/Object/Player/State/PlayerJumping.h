#pragma once
#ifndef PLAYER_JUMPING_DEFINED
#define PLAYER_JUMPING_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"

class Player;
// PlayerJumpingクラスを定義する
class PlayerJumping : public IState
{
public:
	// コンストラクタ
	PlayerJumping(Player* soldier);
	// デストラクタ
	~PlayerJumping();
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

private:
	// プレイヤー
	Player* m_player;
	// グラフィックス
	Graphics* m_graphics;
	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;
};
#endif		// SOLDIER_IDLING_DEFINED
