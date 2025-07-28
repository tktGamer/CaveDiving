/**
 * @file   Stage.cpp
 *
 * @brief  ステージに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Stage.h"

//頂点情報
const std::vector<D3D11_INPUT_ELEMENT_DESC> Stage::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,								D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",	    0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] parent 親オブジェクトのポインタ(なし)
 * @param[in] initialPosition 初期位置
 * @param[in] initialAngle    初期角度
 */
Stage::Stage(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	: GameObject(Tag::ObjectType::Stage,parent,initialPosition,initialAngle)
	, m_objectNumber{ CountUpNumber() }
	, m_messageID{  }
	, m_graphics{ Graphics::GetInstance() }
	, m_box{ GetPosition(),DirectX::SimpleMath::Vector3(50.01f,1.01f,50.01f)} // 初期位置とサイズを設定
{

}



/**
 * @brief デストラクタ
 */
Stage::~Stage()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Stage::Initialize()
{
	SetModel(ResourceManager::GetInstance()->RequestModel(L"block.sdkmesh"));
	SetPosition(DirectX::SimpleMath::Vector3(0.0f, -2.0f, 0.0f));
	SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	SetScale(DirectX::SimpleMath::Vector3(50.0f, 1.0f, 50.0f));
	SetTexture(ResourceManager::GetInstance()->RequestTexture("block.png"));
	
	SetShape(&m_box);


}




/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Stage::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	m_box.SetCenter(currentPosition + GetPosition());
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Stage::Draw()
{
	Shader* shader = Shader::GetInstance();	
	ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = m_graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = m_graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = m_graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Stage::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(GetPosition(), GetQuaternion(), GetScale()).Transpose();
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(Shader::Model), 0, NULL, &cbuff, 0, 0);

	GetModel()->Draw(context, *states, world, view, proj, false, [&]()
		{
			//	モデル表示をするための自作シェーダに関連する設定を行う


			//	画像用サンプラーの登録
			ID3D11SamplerState* sampler[1] = { states->PointWrap() };
			context->PSSetSamplers(0, 1, sampler);

			if (GetTexture() != nullptr)
			{
				//	読み込んだ画像をピクセルシェーダに伝える
				//	自作VSはt0を使っているため、
				//	t0がメインで使われていると勝手に想定。
				context->PSSetShaderResources(0, 1, GetTexture());
			}

			//	半透明描画指定
			ID3D11BlendState* blendstate = states->NonPremultiplied();

			//	透明判定処理
			context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

			//	深度バッファに書き込み参照する
			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			//	カリングはなし
			context->RSSetState(states->CullClockwise());

			Shader::GetInstance()->StartShader(Shader::Model, shader->GetCBuffer(Shader::Model));

			context->IASetInputLayout(shader->GetInputLayout(Shader::Model));
		});
	Shader::GetInstance()->EndShader();

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Stage::Finalize()
{

}

void Stage::OnMessegeAccepted(Message::MessageID messageID)
{

}


int Stage::GetObjectNumber()
{
	return m_objectNumber;
}
