/**
 * @file   Tag.h
 *
 * @brief  オブジェクトの種類に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付 2025/07/16
 */

 // 多重インクルードの防止 =====================================================
#pragma once

class Tag
{
public:
	// オブジェクトの種類
	enum  ObjectType : int
	{
		None,	// なし
		Player,	// プレイヤー
		Pikel,  // つるはし
		Enemy,	// 敵
		Item,	// アイテム
		Light,
		Stage,
	};
};


