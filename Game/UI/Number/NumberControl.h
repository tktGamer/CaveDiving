/**
 * @file   NumberControl.h
 *
 * @brief  数字に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/31
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"../Number/Number.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 数字
  */
class NumberControl
{
// クラス定数の宣言 -------------------------------------------------
public:
	//数字テクスチャに必要なデータ
	struct NumberTextureData 
	{
		std::string texturePath; //画像パス
		int col = 0;//縦列数
		int raw = 0;//横列数
	};
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//表示する数字を設定
	void SetNumber(const int& num);
	//拡大率を設定
	void SetScale(const DirectX::SimpleMath::Vector2& scale);
	//最低表示桁数の設定
	void SetDrawMinDigit(const int& digit);
// コンストラクタ/デストラクタ
	// コンストラクタ
	NumberControl(const NumberTextureData& data, const DirectX::SimpleMath::Vector2& pos,const DirectX::SimpleMath::Vector4& color);
	// デストラクタ
	~NumberControl();
// 操作
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Render();
	//終了
	void Finalize();
//　内部操作
private:
	//桁数確認
	int CheckDigit(const int& num);
// データメンバの宣言 -----------------------------------------------
private:
	//基準の表示位置(一桁目の中心)
	DirectX::SimpleMath::Vector2 m_position;
	//スケール
	DirectX::SimpleMath::Vector2 m_scale;
	//表示する数字
	int m_number;
	//最低表示桁数
	int m_drawDigit;

	//1つの数字のサイズ
	DirectX::SimpleMath::Vector2 m_numberSize;
	DirectX::SimpleMath::Vector4 m_color;
	//各桁を表示するクラス 一桁目が０番目
	std::unique_ptr<Number> m_numberUI;
};

