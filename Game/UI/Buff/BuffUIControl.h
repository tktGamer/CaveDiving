/**
 * @file   BuffUIControl.h
 *
 * @brief  入れ替え確認UIに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include<list>
#include "../UserInterface.h"

#include"Game/Interface/IUI.h"
#include"../Buff/Buff.h"
#include"Game/Object/Item/Item.h"
// クラスの宣言 ===============================================================
class GemSelectUIManager;
class Sound;
// クラスの定義 ===============================================================
/**
  * @brief 入れ替え確認UI
  */
class BuffUIControl : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:
	static constexpr DirectX::SimpleMath::Vector2 FIRST_BUFF_UI_POS = { 5.0f,100.0f };

	int ROW_NUM = 3;
// データメンバの宣言 -----------------------------------------------
private:
	std::list<std::unique_ptr<Buff>> m_buffUIs;

	int m_windowWidth, m_windowHeight;

	//画像サイズ
	DirectX::SimpleMath::Vector2 m_textureSize;
	//現在のバフ表示数
	int m_nowBuff;
	//効果音

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	BuffUIControl(int width, int height);
	~BuffUIControl();
	// 操作
public:
	void Initialize() ;
	void Update() override;
	void Render() override;

//　取得・設定
public:
	void AddUI(const Item::EffectType& effectType,const float& buffTime);

//　内部操作
private:

};
