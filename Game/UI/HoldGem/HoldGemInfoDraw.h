/**
 * @file   HoldGemInfoDraw.h
 *
 * @brief  所持している宝石の内1つの情報を表示するUIに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2026/01/30
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "../UserInterface.h"
#include"Game/Object/Gem/GemManager.h"
#include"Game/Interface/IUI.h"
#include"Game/UI/HoldGem/HoldGem.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 所持している宝石の内1つの情報を表示するUI
  */
class HoldGemInfoDraw : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:
	//宝石の表示位置
	static constexpr float GEM_POS_X[3] = {-46.0f, 0.0f ,46.0f};
	static constexpr DirectX::SimpleMath::Vector2 GEM_SCALE = {0.13f,0.13f};

	//入れ替え候補UI位置
	static constexpr DirectX::SimpleMath::Vector2 CACDIDATE_GEM_UI_POS = { 350.0f,200.0f };
	//カーソルUIの位置
	static constexpr DirectX::SimpleMath::Vector2 CURSOL_UI_POS = { 650.0f,450.0f };

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//位置設定
	void SetPositon(const DirectX::SimpleMath::Vector2& pos);
	//大きさ設定
	void SetScale(const DirectX::SimpleMath::Vector2& scale);

	int GetMunuIndex() const;
// コンストラクタ/デストラクタ
	//コンストラクタ
	HoldGemInfoDraw(int width, int height, const std::vector<int>& gemID);
	//デストラクタ
	~HoldGemInfoDraw();
// 操作
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Render();

//　内部操作
private:
// データメンバの宣言 -----------------------------------------------
private:

	unsigned int m_menuIndex;

	std::unique_ptr<UserInterface> m_gemUI[3];


	std::unique_ptr<UserInterface> m_cursol;

	int m_windowWidth, m_windowHeight;

	DirectX::SimpleMath::Vector2 m_position;
	DirectX::SimpleMath::Vector2 m_scale;

	std::unique_ptr<HoldGem> m_holdGem;
	//入れ替え候補の宝石UI
	std::unique_ptr<UserInterface> m_candidateGemUI;

	const std::vector<int> m_gemID;
};

