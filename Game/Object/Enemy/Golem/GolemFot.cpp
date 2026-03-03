/**
 * @file   GolemFot.cpp
 *
 * @brief  ゴーレムの足に関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/01/19
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GolemFot.h"
#include"../Golem/Golem.h"
#include"Game/Factory/GameObjectFactory.h"
#include"Game/Shader/ShaderManager.h"
#include"Game/Common/Collision/CollisionManager.h"
 // メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] root　　		   このクラスを一部とするクラスの最上位の親
 * @param[in] parent　		   親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　   初期角度
 */
GolemFot::GolemFot(Character* root,const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	EnemyPart(root,parent,initialPosition,initialAngle),
	m_motionAngle{},
	m_box{initialPosition,GOLEM_FOT_COLLISION_SIZE},
	m_display{ Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext() }

{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//テクスチャ設定
	SetTexture(resourceManager->RequestTexture(ResourcePath::TEXTURE::GOLEM_FOT));
	//モデル設定
	SetModel(resourceManager->RequestModel(ResourcePath::MODEL::GOLEM_FOT));
	//メッセンジャーに登録
	Messenger::GetInstance()->Register(GetObjectNumber(), this);
	//当たり判定セット
	SetShape(&m_box);
}

/**
 * @brief デストラクタ
 */
GolemFot::~GolemFot()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemFot::Initialize()
{
}

/**
 * @brief 更新処理
 *
 * @param[in] currentPosition　親の位置
 * @param[in] currentAngle　　 親の角度
 *
 * @return なし
 */
void GolemFot::Update( const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	//位置の更新
	SetCurrentPosition(DirectX::SimpleMath::Vector3::Transform(GetPosition(), m_motionAngle * currentAngle) + currentPosition);
	//角度の更新
	SetCurrentAngle(GetQuaternion() * m_motionAngle * currentAngle);
	
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
void GolemFot::Draw()
{
	ShaderManager* shader = ShaderManager::GetInstance();
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	//ワールド行列を計算
	DirectX::SimpleMath::Matrix world = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale());

	//アウトライン描画
	if (Messenger::GetInstance()->IsOutLineActive()) 
	{
		OutlineRenderer::Draw(*GetModel(), world, GOLEM_FOT_OUTLINE_THICKNESS);
	}

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ModelShader::ModelCB cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.flash.x = GetRootCharacter()->GetDamageFlash();
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
			//シェーダーセット
			shader->StartShader(ShaderManager::Model);
			//頂点情報設定
			context->IASetInputLayout(shader->GetInputLayout(ShaderManager::Model));

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
void GolemFot::Finalize()
{
}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void GolemFot::OnMessegeAccepted(Message::MessageID messageID)
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
void GolemFot::CollisionResponce(GameObject* other)
{
	switch (other->GetObjectType())
	{
	case Tag::ObjectType::Player:
	{
		// プレイヤーとの衝突処理
		break;
	}
	case Tag::ObjectType::Enemy:
	{
		break;
	}
	case Tag::ObjectType::Ground:
	{
		//親オブジェクト取得
		Character* rootObject = GetRootCharacter();
		//ステージとの衝突応答　押し出し
		DirectX::SimpleMath::Vector3 newPosition = CollisionManager::GetInstance()->PushOut(dynamic_cast<Box*>(other->GetShape()), &m_box);
		rootObject->SetPosition(rootObject->GetCurrentPosition()+newPosition-GetCurrentPosition());

		//Yの速度をリセット
		DirectX::SimpleMath::Vector3 velocity = rootObject->GetVelocity();
		velocity.y = 0.0f;
		rootObject->SetVelocity(velocity);


		break;
	}
	case Tag::ObjectType::Weapon:
	{
		//当たった
		Weapon* weapon = other->Cast<Weapon>();
		//攻撃力をもっている所有者を渡す
		GetRootCharacter()->OnDamage(weapon->GetOwner());
		break;
	}
	default:
		break;
	}

}

/**
 * @brief モーションの角度を取得
 *
 * @param[in] なし
 *
 * @return モーションの角度
 */
const DirectX::SimpleMath::Quaternion& GolemFot::GetMotionAngle() const
{
	return m_motionAngle;
}

/**
 * @brief モーションの角度の設定
 *
 * @param[in] なし
 *
 * @return モーションの角度
 */
void GolemFot::SetMotionAngle(const DirectX::SimpleMath::Quaternion& angle)
{
	m_motionAngle = angle;
}
