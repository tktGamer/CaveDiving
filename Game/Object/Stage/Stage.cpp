/**
 * @file   Stage.cpp
 *
 * @brief  ステージに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/08/27
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Stage.h"
#include"Game/Common/Collision/CollisionManager.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] parent 親オブジェクトのポインタ(なし)
 * @param[in] initialPosition 初期位置
 * @param[in] initialAngle    初期角度
 */
Stage::Stage(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	: m_messageID{  }
	,m_cave{}
	,m_ground{}
	,m_wall{}
{
	//Messenger::GetInstance()->Register(GetObjectNumber(), this);

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
	//SetModel(ResourceManager::GetInstance()->RequestModel(L"block.sdkmesh"));
	//SetPosition(DirectX::SimpleMath::Vector3(0.0f, -1.5f, 0.0f));
	//SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	//SetScale(DirectX::SimpleMath::Vector3(70.0f, 1.0f, 70.0f));
	//SetTexture(ResourceManager::GetInstance()->RequestTexture("block.png"));
	//
	//SetShape(&m_box);

	m_ground = std::make_unique<Ground>(nullptr,DirectX::SimpleMath::Vector3::Zero,0.0f);
	m_ground->Initialize();

	m_cave.SetModelParams(ResourceManager::GetInstance()->RequestModel(L"cave_game.sdkmesh"));
	m_cave.SetModelParamsP(DirectX::SimpleMath::Vector3::Zero);
	m_cave.SetModelParamsR(DirectX::SimpleMath::Vector3::Zero);
	m_cave.SetModelParamsS(DirectX::SimpleMath::Vector3(65.0f, 35.0f, 65.0f));

	m_wall = std::make_unique<Wall>(nullptr, DirectX::SimpleMath::Vector3::Zero, 0.0f);
	m_wall->Initialize();

	CollisionManager* pCM = CollisionManager::GetInstance();
	pCM->Register(m_ground.get());
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
	
	m_ground->Update(elapsedTime,DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Quaternion::Identity);
	m_wall->Update(elapsedTime,DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Quaternion::Identity);
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
	ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = Graphics::GetInstance()->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = Graphics::GetInstance()->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = Graphics::GetInstance()->GetProjectionMatrix();

	//DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	////	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	//Stage::ConstBuffer cbuff;
	//cbuff.matWorld = TKTLib::GetWorldMatrix(GetPosition(), GetQuaternion(), GetScale()).Transpose();
	//cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	//cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();


	////world = TKTLib::GetWorldMatrix(GetPosition(), GetQuaternion(), GetScale());
	////GetModel()->Draw(context, *states, world, view, proj);
	//
	////	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	//context->UpdateSubresource(shader->GetCBuffer(Shader::Model), 0, NULL, &cbuff, 0, 0);

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

	//		Shader::GetInstance()->StartShader(Shader::Model, shader->GetCBuffer(Shader::Model));

	//		context->IASetInputLayout(shader->GetInputLayout(Shader::Model));
	//	});
	//Shader::GetInstance()->EndShader();

	m_ground->Draw();
	m_wall->Draw();

	//m_cave.GetModel()->Draw(context, *states, m_cave.GetWorldMatrix(), view, proj);
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


