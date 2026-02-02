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
// クラスの定義 ===============================================================
/**
  * @brief オブジェクトの種類
  */
class Tag
{
public:
	// オブジェクトの種類
	enum  ObjectType : int
	{
		None,		// なし
		ObjectPart, //オブジェクトを構成する部品
		Player,		// プレイヤー
		Weapon,		// 武器
		Enemy,		// 敵
		EnemyPart,	// 敵の部品
		Item,		// アイテム
		Light,      // ライト
		Wall,	    // 壁
		Ground,		// 床
	};
};


