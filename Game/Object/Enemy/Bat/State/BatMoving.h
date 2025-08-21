#pragma once
#ifndef BAT_MOVING_DEFINED
#define BAT_MOVING_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"

class Bat;
// BatMovingクラスを定義する
class BatMoving : public IState
{
public:
	// コンストラクタ
	BatMoving(Bat* bat);
	// デストラクタ
	~BatMoving();
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
	Bat* m_bat;
	// グラフィックス
	Graphics* m_graphics;
	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;
};
#endif		// BAT_IDLING_DEFINED
