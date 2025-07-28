#pragma once
#ifndef PLAYER_IDLING_DEFINED
#define PLAYER_IDLING_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
class Player;

// PlayerIdlingクラスを定義する
class PlayerIdling : public IState
{
public:
	// コンストラクタ
	PlayerIdling(Player* soldier);
	// デストラクタ
	~PlayerIdling();
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
	// デバイスコンテキスト
	ID3D11DeviceContext* m_context;
	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// プレイヤーモデル
	DirectX::Model* m_playerModel;
};

#endif		// SOLDIER_IDLING_DEFINED
