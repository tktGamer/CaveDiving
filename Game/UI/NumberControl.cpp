/**
 * @file   NumberControl.cpp
 *
 * @brief  数字UIに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "NumberControl.h"
#include"Game/Common/ResourceManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] data
 * @param[in] pos
 */
NumberControl::NumberControl(const NumberTextureData& data, const DirectX::SimpleMath::Vector2& pos, const DirectX::SimpleMath::Vector4& color)
	:m_graphics{Graphics::GetInstance()}
	,m_drawDigit{1}
	,m_scale{1.0f,1.0f}
	,m_number{}
	,m_position{pos}
	,m_color{color}
{
	//数字テクスチャの画像サイズを取得
	int textureWidth = 0, textureHeight = 0;
	ResourceManager::GetInstance()->GetTextureSize(TKTLib::StringToWchar(data.texturePath), textureWidth, textureHeight);
	//数字ひとつのサイズ
	m_numberSize.x  = textureWidth  / data.col;
	m_numberSize.y  = textureHeight / data.raw;

	m_numberUI=std::make_unique<Number>(data.texturePath,m_numberSize);
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
	//m_position = DirectX::SimpleMath::Vector2{ 1000.0f,200.0f };
	m_number = 490;
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
const DirectX::SimpleMath::Vector2 NumberControl::Draw()
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

	return pos;
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

void NumberControl::SetNumber(const int& num)
{
	m_number = num;
}

void NumberControl::SetScale(const DirectX::SimpleMath::Vector2& scale)
{
	m_scale = scale;
}

void NumberControl::SetDrawMinDigit(const int& digit)
{
	m_drawDigit = digit;
}

int NumberControl::CheckDigit(const int& num)
{
	//０なら一桁
	if (num == 0)
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
