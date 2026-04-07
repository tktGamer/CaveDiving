/**
 * @file   RumiRock.cpp
 *
 * @brief  光る石に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/08
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "RumiRock.h"
#include"Game/Shader/ShaderManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] lightData　ライトの情報
 * @param[in] id　　　　石の番号
 * @param[in] parent　親のオブジェクトポインタ
 * @param[in] initialPosition
 * @param[in] initialAngle
 */
RumiRock::RumiRock(const ModelShader::PointLightCB& lightData, const int& id, const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	GameObject{ Tag::ObjectType::Rock,parent,initialPosition,initialAngle },
	m_id{id},
	m_box{ GetPosition(),BOX_COLLISION_SIZE },
	m_color{},
	m_messageID{},
	m_isOn{},
	m_light{},
	m_LightOnSound{},
	m_display{ Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext() }

{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	//テクスチャ設定
	SetTexture(resourceManager->RequestTexture(ResourcePath::TEXTURE::ROCK));
	//モデル設定
	SetModel(resourceManager->RequestModel(ResourcePath::MODEL::RUMI_ROCK));
	m_LightOnSound = std::make_unique<Sound>(resourceManager->RequestSound(ResourcePath::SOUND::LUMI_ROCK_RIGHT_ON));
	//メッセンジャークラスに登録
	Messenger::GetInstance()->Register(GetObjectNumber(), this);
	//当たり判定セット
	SetShape(&m_box);
	//ライト生成
	m_light = std::make_unique<Light>(nullptr,DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Quaternion::Identity);
	m_light->Initialize();

	m_light->SetLightData(lightData);
	//ライトを登録
	Messenger::GetInstance()->RegisterLight(m_light.get());

}

/**
 * @brief デストラクタ
 */
RumiRock::~RumiRock()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] 
 *
 * @return なし
 */
void RumiRock::Initialize()
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
void RumiRock::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	//位置の更新
	SetCurrentPosition( GetPosition() + currentPosition);
	//角度の更新
	SetCurrentAngle( GetQuaternion() * currentAngle);

	//ライトの更新
	m_light->Update(GetCurrentPosition(), GetCurrentQuaternion());
	//当たり判定の更新
	m_box.SetCenter(GetCurrentPosition());
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void RumiRock::Draw()
{
	Graphics* graphics = Graphics::GetInstance();
	ShaderManager* shader = ShaderManager::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();


	//ワールド行列を計算
	DirectX::SimpleMath::Matrix world = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale());
	//	シェーダーに渡す追加のバッファを作成する。
	ModelShader::ModelCB cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.flash = m_color;
	//	受け渡し用バッファの内容更新(ModelCBからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::Rock_Model), 0, NULL, &cbuff, 0, 0);

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

			//シェーダーの設定
			shader->StartShader(ShaderManager::Rock_Model);

			//頂点情報を設定
			context->IASetInputLayout(shader->GetInputLayout(ShaderManager::ShaderType::Rock_Model));

		});
	shader->EndShader();

	//m_box.AddDisplayCollision(&m_display);
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
void RumiRock::Finalize()
{
}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void RumiRock::OnMessegeAccepted(Message::MessageID messageID)
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
void RumiRock::CollisionResponce(GameObject* other)
{
	switch (other->GetObjectType())
	{
		case Tag::ObjectType::Weapon:
		{
			//点いていなかったら
			if (!IsOnLight()) 
			{
				OnLight();
			}
			break;
		}

	}
}

/**
 * @brief ライトをオンにする
 *
 * @param[in] なし
 *
 * @return なし
 */
void RumiRock::OnLight()
{
	//音再生
	m_LightOnSound->Play(false);
	//明かりを点ける
	m_light->LightOn();
	m_color = DEFAULT_COLOR;
}

/**
 * @brief IDを取得する
 *
 * @param[in] なし
 *
 * @return ID
 */
const int& RumiRock::GetID() const
{
	return m_id;
}

/**
 * @brief ライトがオンか
 *
 * @param[in] なし
 *
 * @return true   オン
 * @return flase　オフ
 */
bool RumiRock::IsOnLight()
{
	return m_light->IsOn();
}

bool RumiRock::IsBloom()
{
	return IsOnLight();
}
