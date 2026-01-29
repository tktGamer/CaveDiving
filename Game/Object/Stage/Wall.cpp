/**
 * @file   Wall.cpp
 *
 * @brief  壁に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/08
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
Wall::Wall(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	: 
	GameObject(Tag::ObjectType::Wall,parent,initialPosition,initialAngle),
	m_messageID{},
	m_sphere{ GetPosition(),60.0f}, // 初期位置とサイズを設定
	m_display{ Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext() }
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	//モデル設定
	SetModel(resourceManager->RequestModel(ResourcePath::MODEL::WALL));
	//テクスチャ設定
	SetTexture(resourceManager->RequestTexture(ResourcePath::TEXTURE::WALL));
	//メッセンジャーに登録
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
	
	SetShape(&m_sphere);
	CollisionManager::GetInstance()->Register(this);
}

/**
 * @brief 更新処理
 *
 * @param[in] currentPosition　親の現在位置
 * @param[in] currentAngle 　  親の現在角度
 *
 * @return なし
 */
void Wall::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	//当たり判定更新
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
	Graphics* graphics = Graphics::GetInstance();

	ShaderManager* shader = ShaderManager::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = graphics->GetProjectionMatrix();
	//ワールド行列を計算
	DirectX::SimpleMath::Matrix world = TKTLib::GetWorldMatrix(GetPosition(), GetQuaternion(), GetScale());
	//	シェーダーに渡す追加のバッファを作成する。
	ModelShader::ModelCB cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.flash.x = 0.0f;
	
	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::Wall_Model), 0, NULL, &cbuff, 0, 0);

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
			context->OMSetDepthStencilState(states->DepthNone(), 0);

			//	カリングはなし
			context->RSSetState(states->CullNone());
			//シェーダー設定
			shader->StartShader(ShaderManager::Wall_Model);

			context->IASetInputLayout(shader->GetInputLayout(ShaderManager::Wall_Model));
		});
	//シェーダー解放
	shader->EndShader();

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
	messageID;
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
	other;
}