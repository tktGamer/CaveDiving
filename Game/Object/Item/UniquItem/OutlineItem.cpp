/**
 * @file   OutlineItem.cpp
 *
 * @brief  アウトラインアイテムに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025//11//26
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "OutlineItem.h"
#include"Game/Common/Collision/CollisionManager.h"
#include"Game/Shader/ShaderManager.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] 
 * @param[in] type　オブジェクトの種類
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
 */
OutlineItem::OutlineItem(EffectType effect, int increase,GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:Item{effect,increase,parent,initialPosition,initialAngle}
{
}



/**
 * @brief デストラクタ
 */
OutlineItem::~OutlineItem()
{

}



/**
 * @brief 更新
 *
 * @param[in] currentPosition 
 * @param[in] currentAngle 
 *
 * @return なし
 */
void OutlineItem::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	m_currentPosition = currentPosition + GetPosition();
	m_currentAngle = GetQuaternion() * currentAngle;

	UpdateCollision(GetCurrentPosition());

}


/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void OutlineItem::Draw()
{
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	OutlineItem::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale()).Transpose();
	cbuff.matView = graphics->GetViewMatrix().Transpose();
	cbuff.matProj = graphics->GetProjectionMatrix().Transpose();
	cbuff.color = GetColor();
	ShaderManager* shader = ShaderManager::GetInstance();
	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::Item_Model), 0, NULL, &cbuff, 0, 0);



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

			ShaderManager::GetInstance()->StartShader(ShaderManager::Item_Model);

			//auto ps = shader->GetItemPS();

			//auto constBuffer = shader->GetCBuffer(ShaderManager::ShaderType::Item_Model);
			////	シェーダーにバッファを渡す
			//ID3D11Buffer* cb[1] = { constBuffer };

			//context->PSSetConstantBuffers(0, 1, cb);
			//context->PSSetShader(ps, nullptr, 0);

			context->IASetInputLayout(shader->GetInputLayout(ShaderManager::ShaderType::Item_Model));

		});
	ShaderManager::GetInstance()->EndShader();

	//m_box.AddDisplayCollision(&m_display);
	//m_display.DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates()
	//	, Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());

}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void OutlineItem::OnMessegeAccepted(Message::MessageID messageID)
{
	switch (messageID)
	{
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
void OutlineItem::CollisionResponce(GameObject* other)
{
	switch (other->GetObjectType())
	{
	case Tag::ObjectType::Enemy:
	{
	}
	case Tag::ObjectType::EnemyPart:
	{
	}
	break;
	case Tag::ObjectType::Ground:
	{
	}
	case Tag::ObjectType::Player: 
	{
		Messenger::GetInstance()->SetOutLineActive(true);
		SetIsGet(true);
		SetItemGetObjectPos(other->GetCurrentPosition());
	}
	default:
		break;
	}
}

