/**
 * @file   NumberControl.cpp
 *
 * @brief  数字UIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/02/01
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "NumberControl.h"
#include"Game/Common/ResourceManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] data   数字テクスチャデータ
 * @param[in] pos　　描画座標
 * @param[in] color　色
 */
NumberControl::NumberControl(const NumberTextureData& data, const DirectX::SimpleMath::Vector2& pos, const DirectX::SimpleMath::Vector4& color)
	:
	m_drawDigit{ 1 },
	m_scale{DirectX::SimpleMath::Vector2::One},
	m_number{},
	m_position{pos},
	m_color{color}
{
	//数字テクスチャの画像サイズを取得
	int textureWidth = 0, textureHeight = 0;
	ResourceManager::GetInstance()->GetTextureSize(TKTLib::StringToWchar(data.texturePath), textureWidth, textureHeight);
	//数字ひとつのサイズ
	m_numberSize.x = static_cast<float>(textureWidth / data.col);
	m_numberSize.y = static_cast<float>(textureHeight / data.raw);

	m_numberUI = std::make_unique<Number>(data.texturePath,m_numberSize);
}

/**
 * @brief デストラクタ
 */
NumberControl::~NumberControl()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void NumberControl::Initialize()
{
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void NumberControl::Update()
{

}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return 最上位桁の描画位置から数字一つ分ずらした位置
 */
void NumberControl::Render()
{
	DirectX::SimpleMath::Vector2 pos = m_position;

	//描画する数字の桁数を取得
	int digit = CheckDigit(m_number);

	
	//表示する桁分まわす
	int number = m_number;
	int maxDigit = std::max(digit, m_drawDigit);
	for (int i = 0; i < maxDigit; i++) 
	{
		//下位桁から表示する
		int num = number % 10;
		number /= 10;
		m_numberUI->Draw(num, pos,m_scale,m_color);
		//数字の大きさ分ずらす
		pos.x -= static_cast<float>(m_numberSize.x) * m_scale.x ;

	}

	//return pos;
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void NumberControl::Finalize()
{

}

/**
 * @brief 数字を設定
 *
 * @param[in] num  数字
 *
 * @return なし
 */
void NumberControl::SetNumber(const int& num)
{
	m_number = num;
}

/**
 * @brief 拡大率の設定
 *
 * @param[in] scale　拡大率
 *
 * @return なし
 */
void NumberControl::SetScale(const DirectX::SimpleMath::Vector2& scale)
{
	m_scale = scale;
}


/**
 * @brief 最低表示桁数の設定
 *
 * @param[in] digit　表示する桁数
 *
 * @return なし
 */
void NumberControl::SetDrawMinDigit(const int& digit)
{
	m_drawDigit = digit;
}


/**
 * @brief 桁数の確認
 *
 * @param[in] num　確認する数字
 *
 * @return　桁数
 */
int NumberControl::CheckDigit(const int& num)
{
	//０なら一桁
	if (num == TKTLib::INT_ZERO)
	{
		return 1;
	}
	
	int digit = 0;
	// 符号を考慮して絶対値を取る
	int temp = (num < 0) ? -num : num;
	while (temp > 0)
	{
		temp /= 10;
		digit++;
	}
	
	return digit;
}
