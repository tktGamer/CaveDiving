/**
 * @file   BuffUIControl.h
 *
 * @brief  バフUIコントロールに関するヘッダファイル
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
  * @brief バフUIコントロール
  */
class BuffUIControl : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:
	//バフUIの最初の位置
	static constexpr DirectX::SimpleMath::Vector2 FIRST_BUFF_UI_POS = { 55.0f,130.0f };
	//通常スケールのときのバフUIの間隔
	static constexpr DirectX::SimpleMath::Vector2 NORMAL_SCALE_BUFF_UI_INTERVAL = { 100.0f,170.0f };
	//バフUIの列数
	int ROW_NUM = 3;

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//バフUI追加
	void AddUI(const Item::EffectType& effectType,const float& buffTime);
	//バフUIのサイズ設定
	void SetBuffUITextureSize(const DirectX::SimpleMath::Vector2& size);
// コンストラクタ/デストラクタ
	// コンストラクタ
	BuffUIControl(int width, int height);
	//デストラクタ
	~BuffUIControl();
// 操作
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Render() override;

//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	//バフUIリスト
	std::list<std::unique_ptr<Buff>> m_buffUIs;
	//ウィンドウサイズ
	int m_windowWidth, m_windowHeight;
	//画像サイズ
	DirectX::SimpleMath::Vector2 m_textureScale;
	//現在のバフ表示数
	int m_nowBuff;
	//効果音
};
