/**
 * @file   Wing.cpp
 *
 * @brief  コウモリの羽に関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付 2025/08/27
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Wing.h"
#include"../Bat/Bat.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
 */
Wing::Wing(Character* root, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:EnemyPart(root,parent,initialPosition,initialAngle)
	,m_motionAngle{}
{
	SetTexture(ResourceManager::GetInstance()->RequestTexture(L"wing.png"));
	SetModel(ResourceManager::GetInstance()->RequestModel(L"wing.sdkmesh"));
	Messenger::GetInstance()->Register(GetObjectNumber(), this);

}



/**
 * @brief デストラクタ
 */
Wing::~Wing()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Wing::Initialize()
{



}




/**
 * @brief 更新処理
 *
 * @param[in] currentPosition 親の座標
 * @param[in] currentAngle　親の角度
 *
 * @return なし
 */
void Wing::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{

	m_currentAngle =m_initialAngle * GetQuaternion() * m_motionAngle * currentAngle;
	m_currentPosition =DirectX::SimpleMath::Vector3::Transform(m_initialPosition, m_motionAngle* currentAngle)+ currentPosition + GetPosition();
	
}




/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Wing::Draw()
{
	Shader* shader = Shader::GetInstance();
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = TKTLib::GetWorldMatrix(m_currentPosition,m_currentAngle, GetScale());
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Bat::ConstBuffer cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = Graphics::GetInstance()->GetViewMatrix().Transpose();
	cbuff.matProj = Graphics::GetInstance()->GetProjectionMatrix().Transpose();
	cbuff.color.x = GetRootCharacter()->GetDamageFlash();

	//GetModel()->Draw(context, *states, world, view, proj);

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
void Wing::Finalize()
{

}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void Wing::OnMessegeAccepted(Message::MessageID messageID)
{
}

/**
 * @brief 衝突応答
 *
 * @param[in] other 衝突したオブジェクト
 *
 * @return なし
 */
void Wing::CollisionResponce(GameObject* other)
{
}


DirectX::SimpleMath::Quaternion Wing::GetMotionAngle()
{
	return m_motionAngle;
}

void Wing::SetMotionAngle(DirectX::SimpleMath::Quaternion angle)
{
	m_motionAngle = angle;
}
