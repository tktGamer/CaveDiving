#pragma once
#ifndef PLAYER_ATTACK_DEFINED
#define PLAYER_ATTACK_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"

class Player;
// PlayerAttackクラスを定義する
class PlayerAttack : public IState
{
public:
	// コンストラクタ
	PlayerAttack(Player* player);
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

private:
	// ソルジャー
	Player* m_player;
	// グラフィックス
	Graphics* m_graphics;
	// デバイスコンテキスト
	ID3D11DeviceContext* m_context;
	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// プレイヤーモデル
	DirectX::Model* m_playerModel;
};

#endif		// SOLDIER_IDLING_DEFINED
