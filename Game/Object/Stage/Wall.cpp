/**
 * @file   Wall.cpp
 *
 * @brief  壁に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/08
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Wall.h"
#include"Game/Common/Collision/CollisionManager.h"
#include"Game/Shader/ShaderManager.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] parent 親オブジェクトのポインタ(なし)
 * @param[in] initialPosition 初期位置
 * @param[in] initialAngle    初期角度
 */
Wall::Wall(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	: GameObject(Tag::ObjectType::Wall,parent,initialPosition,initialAngle)
	, m_messageID{  }
	, m_graphics{ Graphics::GetInstance() }
	, m_sphere{ GetPosition(),60.0f} // 初期位置とサイズを設定
	, m_display{ Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext() }

{
	Messenger::GetInstance()->Register(GetObjectNumber(), this);

}



/**
 * @brief デストラクタ
 */
Wall::~Wall()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Wall::Initialize()
{
	SetModel(ResourceManager::GetInstance()->RequestModel(L"cave_game.sdkmesh"));
	SetPosition(DirectX::SimpleMath::Vector3::Zero);
	SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	SetScale(DirectX::SimpleMath::Vector3(60.0f, 50.0f, 60.0f));
	SetTexture(ResourceManager::GetInstance()->RequestTexture("block.png"));
	
	SetShape(&m_sphere);

	CollisionManager::GetInstance()->Register(this);
}




/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Wall::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	m_sphere.SetCenter(currentPosition + GetPosition());
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Wall::Draw()
{
	ShaderManager* shader = ShaderManager::GetInstance();
	ID3D11DeviceContext* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = m_graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = m_graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = m_graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Wall::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(GetPosition(), GetQuaternion(), GetScale()).Transpose();
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();
	cbuff.color.x = 0.0f;

	//world = TKTLib::GetWorldMatrix(GetPosition(), GetQuaternion(), GetScale());
	//GetModel()->Draw(context, *states, world, view, proj);
	
	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::Model), 0, NULL, &cbuff, 0, 0);

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

			ShaderManager::GetInstance()->StartShader(ShaderManager::Model);

			context->IASetInputLayout(shader->GetInputLayout(ShaderManager::Model));
		});
	ShaderManager::GetInstance()->EndShader();

	//m_sphere.AddDisplayCollision(&m_display);
	m_display.DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates()
		, Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Wall::Finalize()
{

}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void Wall::OnMessegeAccepted(Message::MessageID messageID)
{

}

/**
 * @brief 衝突応答
 *
 * @param[in] other 衝突したオブジェクト
 *
 * @return なし
 */
void Wall::CollisionResponce(GameObject* other)
{
}

