/**
 * @file   HoldGem.h
 *
 * @brief  所持している宝石を表示するUIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/03/05
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "../UserInterface.h"
#include"Game/Object/Gem/GemManager.h"
#include"Game/Interface/IUI.h"
#include<unordered_map>
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 所持している宝石を表示するUI
  */
class HoldGem : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:
	//宝石の抽選数
	static constexpr int GEM_NUM = 3;
	//宝石の表示位置
	static constexpr float GEM_POS_X[GEM_NUM] = {-46.0f, 0.0f ,46.0f};
	//宝石のサイズ
	static constexpr DirectX::SimpleMath::Vector2 GEM_SCALE = {0.13f,0.13f};

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//座標設定
	void ChangePositon(const DirectX::SimpleMath::Vector2& pos);
	//スケール設定
	void ChangeScale(const DirectX::SimpleMath::Vector2& scale);
// コンストラクタ/デストラクタ
	//コンストラクタ
	HoldGem(int width, int height, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale);
	//デストラクタ
	~HoldGem();
// 操作
public:
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Render();

	//表示する宝石を変更
	void ChangeDrawGem(const std::vector<int>& gemID);

//　内部操作
private:
	//UI生成
	void Add(const wchar_t* path,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const UserInterface::ANCHOR& anchor);
	//マップ情報設定
	void SetTextureMap();
// データメンバの宣言 -----------------------------------------------
private:
	//対応する宝石を入れるマップ
	std::unordered_map<std::string,const wchar_t*> m_gemTextureMap;

	unsigned int m_menuIndex;

	std::unique_ptr<UserInterface> m_gemUI[GEM_NUM];
	std::unique_ptr<UserInterface> m_base;

	int m_windowWidth, m_windowHeight;



	DirectX::SimpleMath::Vector2 m_position;
	DirectX::SimpleMath::Vector2 m_scale;
};

