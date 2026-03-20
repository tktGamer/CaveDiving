/**
 * @file   GemSelect.h
 *
 * @brief  宝石選択UIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/02/24
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "../UserInterface.h"
#include"Game/Object/Gem/GemManager.h"
#include"Game/Interface/IUI.h"
// クラスの宣言 ===============================================================
class GemSelectUIManager;
class Sound;
// クラスの定義 ===============================================================
/**
  * @brief ユーザーインターフェイス
  */
class GemSelect : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:
	static constexpr float PANNEL_X_POS = 310.0f;
	static constexpr float PANNEL_Y_POS = 310.0f;
	//選出数宇
	static constexpr int GEM_ELECTION_NUM = 3;
	//宝石抽選の最大回数
	static constexpr int MAX_TRY = 100;
	//宝石情報UIのサイズ
	static constexpr DirectX::SimpleMath::Vector2 GEM_SIZE = { 1.0f, 1.0f };
	//「取得しない」のメッセージの位置
	static constexpr DirectX::SimpleMath::Vector2 NOT_GET_MESSAGE_POSITION = { 650.0f,625.0f };
	//「取得しない」のメッセージの大きさ
	static constexpr DirectX::SimpleMath::Vector2 NOT_GET_MESSAGE_SCALE = { 1.0f,1.0f };

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//選択されている項目番号種痘
	int GetGemSelectIndex() const { return m_menuIndex; }
// コンストラクタ/デストラクタ
public:
	//コンストラクタ
	GemSelect(int width, int height,const std::vector<int>& gemID, GemSelectUIManager* pUIManager);
	//デストラクタ
	~GemSelect();
// 操作
	//初期化
	void Initialize();
	//更新
	void Update() override;
	//描画
	void Render() override;


	//宝石をランダムに選択
	void Randomize();
//　内部操作
private:
	//UI追加
	void Add(const Gem::GemImagePath& gemImagePath, const DirectX::SimpleMath::Vector2& position,
			 const DirectX::SimpleMath::Vector2& scale, const UserInterface::ANCHOR& anchor);

// データメンバの宣言 -----------------------------------------------
private:
	int m_windowWidth, m_windowHeight;
	//管理クラスのポインタ
	GemSelectUIManager* m_pUIManager;

	unsigned int m_menuIndex;

	std::vector<std::unique_ptr<UserInterface>> m_userInterface;
	std::vector<std::unique_ptr<UserInterface>> m_base;



	const Gem* m_pGems[GEM_ELECTION_NUM];
	const std::vector<int> m_gemID;

	//効果音
	std::unique_ptr<Sound> m_cursorSound;
	std::unique_ptr<Sound> m_decideSound;

};
