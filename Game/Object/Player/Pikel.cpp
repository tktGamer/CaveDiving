/**
 * @file   Pikel.cpp
 *
 * @brief  つるはし（プレイヤーの武器）に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/03
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Pikel.h"
#include"../CaveDiving/Game/Object/Player/Player.h"
#include"Game/Common/Collision/CollisionManager.h"
#include"Game/Shader/ShaderManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] owner    武器の所有者
 * @param[in] parent　親オブジェクトのポインタ
 * @param[in] initialPosition　初期座標
 * @param[in] initialAngle　　　初期角度
 */
Pikel::Pikel(Character* owner, const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:m_graphics{Graphics::GetInstance()}
	, Weapon(owner,Tag::ObjectType::Weapon,parent,initialPosition,initialAngle)
	, m_messageID{}
	, m_sphere{ GetPosition(), 1.5f}
	,m_display{ Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()}
{
	SetTexture(ResourceManager::GetInstance()->RequestTexture(L"pikel.png"));
	SetModel(ResourceManager::GetInstance()->RequestModel(L"pikel.sdkmesh"));

	m_sphere.SetEnabled(false);
	SetShape(&m_sphere);

	Messenger::GetInstance()->Register(GetObjectNumber(), this);

	CollisionManager::GetInstance()->Register(this);

}




/**
 * @brief デストラクタ
 */
Pikel::~Pikel()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Pikel::Initialize()
{

}




/**
 * @brief 更新処理
 *
 * @param[in] currentPosition 親の座標
 * @param[in] currentAngle    親の角度
 *
 * @return なし
 */
void Pikel::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	//位置の更新
	SetCurrentPosition(GetInitialPosition() + currentPosition + GetPosition());
	//角度の更新
	SetCurrentAngle(GetQuaternion() * currentAngle * GetInitialQuaternion());
	//当たり判定の更新
	//位置を調整する
	m_sphere.SetCenter(GetCurrentPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f), GetCurrentQuaternion()));
}




/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Pikel::Draw()
{
	ShaderManager* shader = ShaderManager::GetInstance();
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale());
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ModelShader::ModelCB cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();

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
void Pikel::Finalize()
{

}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void Pikel::OnMessegeAccepted(Message::MessageID messageID)
{
	switch (messageID)
	{
	case Message::COLLISIONVALID:
		m_sphere.SetEnabled(true);
		break;
	case Message::COLLISIONINVALID:
		m_sphere.SetEnabled(false);
		break;
	default:
		break;

	}
}

/**
 * @brief 衝突応答
 *
 * @param[in] other 衝突したオブジェクト
 *
 * @return なし
 */
void Pikel::CollisionResponce(GameObject* other)
{
	switch (other->GetObjectType()) 
	{
	case Tag::Enemy:
		
		break;
	default:
		break;

	}
}

