/**
 * @file   Hand.cpp
 *
 * @brief  プレイヤーの手に関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Hand.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Hand::Hand()
	:m_graphics{Graphics::GetInstance()}
	, GameObject(ObjectType::Player)
{

}



/**
 * @brief デストラクタ
 */
Hand::~Hand()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Hand::Initialize()
{

}




/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Hand::Update(float elapsedTime)
{
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Hand::Draw()
{
	ID3D11DeviceContext*		 context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = m_graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = m_graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = m_graphics->GetProjectionMatrix();
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Hand::Finalize()
{

}

void Hand::OnMessegeAccepted(Message::MessageID messageID)
{
}

int Hand::GetObjectNumber()
{
	return 0;
}
