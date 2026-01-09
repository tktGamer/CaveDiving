/**
 * @file   Hand.cpp
 *
 * @brief  プレイヤーの手に関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/01/08
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Hand.h"
#include"../CaveDiving/Game/Object/Player/Player.h"
#include"Game/Object/Player/Pikel.h"
#include"Game/Shader/ShaderManager.h"
#include"Game/Factory/GameObjectFactory.h"
 // メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] root　パーツをもつオブジェクトの根
 * @param[in] parent　親オブジェクトのポインタ
 * @param[in] initialPosition　初期座標
 * @param[in] initialAngle　　 初期角度
 */
Hand::Hand(Character* root,const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	: PartObject(root,parent,initialPosition,initialAngle)
	,m_motionAngle{}
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	//テクスチャ設定
	SetTexture(resourceManager->RequestTexture(ResourcePath::TEXTURE::PLAYER_HAND));
	//モデル設定
	SetModel(resourceManager->RequestModel(ResourcePath::MODEL::PLAYER_HAND));
	//メッセンジャークラスに登録
	Messenger::GetInstance()->Register(GetObjectNumber(), this);

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
 * @param[in] currentPosition 親の座標
 * @param[in] currentAngle    親の角度
 *
 * @return なし
 */
void Hand::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	//現在位置の更新
	//プレイヤーの周囲のトランスフォームさせ、親の位置分移動
	SetCurrentPosition(DirectX::SimpleMath::Vector3::Transform(GetInitialPosition() + GetPosition(), m_motionAngle * currentAngle)+ currentPosition );
	//現在角度の更新
	SetCurrentAngle(GetQuaternion() * m_motionAngle * currentAngle * GetInitialQuaternion());
	
	//武器を持っていたら更新
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
void Hand::Draw()
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
		OutlineRenderer::Draw(*GetModel(), world, PLAYER_HAND_OUTLINE_THICKNESS);
		// モデル描画（アウトライン専用）
	}

	//	シェーダーに渡す追加のバッファを作成する。
	ModelShader::ModelCB cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = graphics->GetViewMatrix().Transpose();
	cbuff.matProj = graphics->GetProjectionMatrix().Transpose();
	cbuff.flash.x = GetRootCharacter()->GetDamageFlash();

	//	受け渡し用バッファの内容更新(ModelCBからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::Model), 0, NULL, &cbuff, 0, 0);
	//モデル描画
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

			shader->StartShader(ShaderManager::Model);

			context->IASetInputLayout(shader->GetInputLayout(ShaderManager::Model));

		});
	//シェーダー解放
	shader->EndShader();

	//武器を持っていたら描画
	if (m_weapon)
	m_weapon->Draw();
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

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void Hand::OnMessegeAccepted(Message::MessageID messageID)
{
	UNREFERENCED_PARAMETER(messageID);

}

/**
 * @brief 衝突応答
 *
 * @param[in] other 衝突したオブジェクト
 *
 * @return なし
 */
void Hand::CollisionResponce(GameObject* other)
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
bool Hand::HaveWeapon(std::unique_ptr<Weapon> weapon)
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
DirectX::SimpleMath::Quaternion Hand::GetMotionAngle() const
{
	return m_motionAngle;
}

/**
 * @brief モーションの角度の設定
 *
 * @param[in] angle　モーション角度
 *
 * @return なし
 */
void Hand::SetMotionAngle(DirectX::SimpleMath::Quaternion angle)
{
	m_motionAngle = angle;
}
