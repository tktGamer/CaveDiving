/**
 * @file   GolemHand.cpp
 *
 * @brief  ゴーレムの手に関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/01/19
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GolemHand.h"
#include"../Golem/Golem.h"
#include"Game/Factory/GameObjectFactory.h"
#include"Game/Shader/ShaderManager.h"
#include"Game/Shader/Outline/OutlineRenderer.h"
#include"Game/Object/Weapon.h"
 // メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] root　　		   このクラスを一部とするクラスの最上位の親
 * @param[in] parent　		   親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　   初期角度
 */
GolemHand::GolemHand(Character* root,const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	EnemyPart(root,parent,initialPosition,initialAngle),
	m_motionAngle{},
	m_sphere{initialPosition,GOLEM_HAND_SPHERE_SIZE}
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//テクスチャ設定
	SetTexture(resourceManager->RequestTexture(ResourcePath::TEXTURE::GOLEM_HAND));
	//モデル設定
	SetModel(resourceManager->RequestModel(ResourcePath::MODEL::GOLEM_HAND));
	//メッセンジャーに登録
	Messenger::GetInstance()->Register(GetObjectNumber(), this);
	//当たり判定セット
	SetShape(&m_sphere);
}

/**
 * @brief デストラクタ
 */
GolemHand::~GolemHand()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemHand::Initialize()
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
void GolemHand::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	//位置の更新
	SetCurrentPosition(DirectX::SimpleMath::Vector3::Transform( GetPosition(), m_motionAngle * currentAngle) + currentPosition);
	//角度の更新
	SetCurrentAngle(GetQuaternion() * m_motionAngle * currentAngle);
	
	//当たり判定の更新
	m_sphere.SetCenter(GetCurrentPosition());

	//武器をもっていたら更新
	if(m_weapon)
	m_weapon->Update(GetCurrentPosition(), GetCurrentQuaternion());
}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemHand::Draw()
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
		OutlineRenderer::Draw(*GetModel(), world, GOLEM_HAND_OUTLINE_THICKNESS);
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

	//武器を持っていたら
	if (m_weapon) 
	{
		m_weapon->Draw();

	}

	//m_sphere.AddDisplayCollision(&m_display);
	//m_display.DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates()
	//	, Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());
}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemHand::Finalize()
{
}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void GolemHand::OnMessegeAccepted(Message::MessageID messageID)
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
void GolemHand::CollisionResponce(GameObject* other)
{
	UNREFERENCED_PARAMETER(other);

}


/**
 * @brief 武器を持たせる
 *
 * @param[in] weapon 武器クラス
 *
 * @return true   成功
 * @return false　失敗
 */
bool GolemHand::HaveWeapon(std::unique_ptr<Weapon> weapon)
{
	//実体があるか確認
	if (weapon) 
	{
		//所有権を移動
		m_weapon = std::move(weapon);

		//成功
		return true;
	}

	//失敗
	return false;
}


/**
 * @brief モーションの角度を取得
 *
 * @param[in] なし
 *
 * @return モーションの角度
 */
DirectX::SimpleMath::Quaternion GolemHand::GetMotionAngle()
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
void GolemHand::SetMotionAngle(DirectX::SimpleMath::Quaternion angle)
{
	m_motionAngle = angle;
}
