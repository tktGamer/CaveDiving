/**
 * @file   Key.h
 *
 * @brief  操作キーUIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/30
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/UI/UserInterface.h"
#include<unordered_map>
#include <Keyboard.h>
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 操作キーUI
  */
class Key : public UserInterface
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
// メンバ関数の宣言 -------------------------------------------------
// 取得/設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	Key(const std::vector<DirectX::Keyboard::Keys>& respoceKey);
	// デストラクタ
	~Key();
// 操作
	//初期化処理
	void Initialize();
	//更新
	void Update() override;
	//描画
	void Render() override;
	
//内部処理
private:

// データメンバの宣言 -----------------------------------------------
private:
	//反応するキー
	std::vector<DirectX::Keyboard::Keys> m_responceKey;
	//押されたか
	bool m_isKeyPressed;
};
