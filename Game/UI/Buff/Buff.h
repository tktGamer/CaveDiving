/**
 * @file   Buff.h
 *
 * @brief  適用中のバフ表示UIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/30
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "../UserInterface.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 適用中のバフ表示UI
  */
class Buff : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
// 取得/設定
public:
	//バフの残り時間取得
	const float& GetRemainingTime();
	//バフUIの位置設定
	void SetPosition(const DirectX::SimpleMath::Vector2& pos);
// コンストラクタ/デストラクタ
	// コンストラクタ
	Buff(const float& time,const wchar_t* path,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const UserInterface::ANCHOR& anchor);
	// デストラクタ
	~Buff();
// 操作
	//初期化処理
	void Initialize();
	//更新
	void Update() override;
	//描画
	void Render() override;
	//バフUIの追加
	void Add(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, UserInterface::ANCHOR anchor);
	
//内部処理
private:

// データメンバの宣言 -----------------------------------------------
private:
	//バフの画像
	std::unique_ptr<UserInterface> m_upType;
	//ウィンドウサイズ
	int m_windowWidth, m_windowHeight;
	//バフの残り時間
	const float* m_remainingTime;
};
