#pragma once
#ifndef MESSAGE_DEFINED
#define MESSAGE_DEFINED

// Messageクラス
// ・IDLINGをOFFENSIVE_IDLINGに変更する
class Message
{
public:
	// メッセージID
	enum MessageID : int  
	{ 
		// 
		COLLISIONVALID,					// 「衝突有効」状態
		COLLISIONINVALID,					// 「衝突無効」状態
		// 状態
		IDLING,							// 「アイドリング」状態
		MOVING,							// 「移動」状態
		ATTACK,							// 「攻撃」状態
		AVOIDANCE,						// 「回避」状態
		DAMAGED,						// 「ダメージ」状態
		JUMPING,
	};
};

#endif		// MESSAGE_DEFINED

