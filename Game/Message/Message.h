/**
 * @file   Message.h
 *
 * @brief  メッセージの種類に関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef MESSAGE_DEFINED
#define MESSAGE_DEFINED
// ヘッダファイルの読み込み ===================================================

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief メッセージの種類
  */
class Message
{
// クラス定数の宣言 -------------------------------------------------
public:
	// メッセージID
	enum MessageID : int  
	{ 
		// 
		COLLISIONVALID,					// 「衝突有効」状態
		COLLISIONINVALID,				// 「衝突無効」状態
		// 状態
		IDLING,							// 「アイドリング」状態
		MOVING,							// 「移動」状態
		MOVE_FRONT_ON,//前
		MOVE_FRONT_OFF,
		MOVE_BACK_ON,//後ろ
		MOVE_BACK_OFF,
		MOVE_LEFT_ON,//左
		MOVE_LEFT_OFF,
		MOVE_RIGHT_ON,//右
		MOVE_RIGHT_OFF,
		ATTACK,						    // 「攻撃」状態
		AVOIDANCE,						// 「回避」状態
		DAMAGED,						// 「ダメージ」状態
		JUMPING,						// 「ジャンプ」状態

		CHASING,						// 「追跡」状態
		ATTACKPREPARING,			    // 「攻撃準備」状態

	};

	enum AttackMesssage : int 
	{
		NONE =0,
		ATTACKTYPE_ONE,//「攻撃タイプ１」状態
		ATTACKTYPE_TWO

	};
};

#endif		// MESSAGE_DEFINED

