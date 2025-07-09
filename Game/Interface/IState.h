#pragma once
#ifndef STATE_DEFINED
#define STATE_DEFINED
#include "StepTimer.h"
#include <Keyboard.h>
#include"Game/Interface/IObserver.h"
#include"Game/Common/Graphics.h"
// IStateインターフェイスを定義する 
class IState
{
public:
	// 初期化する 
	virtual void Initialize() = 0;
	// 事前更新する
	virtual void PreUpdate() = 0;
	// 処理を実行する
	virtual void Update(const float& elapsedTime) = 0;
	// 事後更新する
	virtual void PostUpdate() = 0;
	// テクスチャを描画する
	virtual void Render() = 0;
	// 後始末をする
	virtual void Finalize() = 0;
	// 仮想デストラクタ
	virtual ~IState() = default;
};

#endif // STATE_DEFINED
