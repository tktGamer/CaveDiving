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
#include"../CaveDiving/Game/Object/Player/Player.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Hand::Hand(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:m_graphics{Graphics::GetInstance()}
	, GameObject(Tag::ObjectType::Player,parent,initialPosition,initialAngle)
{
	SetTexture(ResourceManager::GetInstance()->RequestTexture(L"hand.png"));
	SetModel(ResourceManager::GetInstance()->RequestModel(L"hand.sdkmesh"));

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
	m_pikel = std::make_unique<Pikel>(this, DirectX::SimpleMath::Vector3(0.0f,0.0f,0.0f), DirectX::XMConvertToRadians(0.0f));

}




/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Hand::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	SetQuaternion(GetQuaternion() * DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(1.0f)));
	m_currentAngle = GetQuaternion() * currentAngle;
	m_currentPosition =DirectX::SimpleMath::Vector3::Transform(m_initialPosition, m_currentAngle)+ currentPosition + GetPosition();
	
	if(m_pikel)
	m_pikel->Update(elapsedTime, m_currentPosition, m_currentAngle);
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
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = TKTLib::GetWorldMatrix(m_currentPosition,m_currentAngle, GetScale());
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Player::ConstBuffer cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	//context->UpdateSubresource(GetCBuffer(), 0, NULL, &cbuff, 0, 0);


	Shader* shader = Shader::GetInstance();

	GetModel()->Draw(context, *states, world, view, proj);
	//GetModel()->Draw(context, *states, world, view, proj, false, [&]()
	//	{
	//		//	モデル表示をするための自作シェーダに関連する設定を行う


	//		//	画像用サンプラーの登録
	//		ID3D11SamplerState* sampler[1] = { states->PointWrap() };
	//		context->PSSetSamplers(0, 1, sampler);

	//		if (GetTexture() != nullptr)
	//		{
	//			//	読み込んだ画像をピクセルシェーダに伝える
	//			//	自作VSはt0を使っているため、
	//			//	t0がメインで使われていると勝手に想定。
	//			context->PSSetShaderResources(0, 1, GetTexture());
	//		}

	//		//	半透明描画指定
	//		ID3D11BlendState* blendstate = states->NonPremultiplied();

	//		//	透明判定処理
	//		context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//		//	深度バッファに書き込み参照する
	//		context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//		//	カリングはなし
	//		context->RSSetState(states->CullClockwise());

	//		Shader::GetInstance()->StartShader(Shader::Model, GetCBuffer());

	//		context->IASetInputLayout();

	//	});
	//Shader::GetInstance()->EndShader();
	if (m_pikel)
	m_pikel->Draw();
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
