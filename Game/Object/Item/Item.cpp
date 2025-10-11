/**
 * @file   Item.cpp
 *
 * @brief  アイテムの基底に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Item.h"
#include"Game/Common/Collision/CollisionManager.h"
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
Item::Item(UpStatus upStatus, int increase,GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:GameObject{Tag::ObjectType::Item,parent,initialPosition,initialAngle}
	,m_upStatus{upStatus}
	,m_increase{increase}
	,m_time{10.0f}
	, m_box{ initialPosition,{1.0f,2.0f,1.0f} }
	,m_isGet{false}
	,m_color{DirectX::Colors::White}
	, m_display{ Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext() }

{
	SetModel(ResourceManager::GetInstance()->RequestModel("item.sdkmesh"));
	SetTexture(ResourceManager::GetInstance()->RequestTexture("item.png"));
	SetShape(&m_box);

	CollisionManager::GetInstance()->Register(this);

	DecideColor();
}



/**
 * @brief デストラクタ
 */
Item::~Item()
{

}


void Item::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	m_currentPosition = currentPosition + GetPosition();
	m_currentAngle = GetQuaternion() * currentAngle;

	m_box.SetCenter(GetCurrentPosition());

}

void Item::Draw()
{
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Item::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale()).Transpose();
	cbuff.matView = graphics->GetViewMatrix().Transpose();
	cbuff.matProj = graphics->GetProjectionMatrix().Transpose();
	cbuff.color = m_color;
	Shader* shader = Shader::GetInstance();
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

			Shader::GetInstance()->StartShader(Shader::Model, shader->GetCBuffer(Shader::Model));

			auto ps = shader->GetItemPS();

			auto constBuffer = shader->GetCBuffer(Shader::ShaderType::Model);
			//	シェーダーにバッファを渡す
			ID3D11Buffer* cb[1] = { constBuffer };

			context->PSSetConstantBuffers(0, 1, cb);
			context->PSSetShader(ps, nullptr, 0);

			context->IASetInputLayout(shader->GetInputLayout(Shader::Model));

		});
	Shader::GetInstance()->EndShader();

	//m_box.AddDisplayCollision(&m_display);
	m_display.DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates()
		, Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());

}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void Item::OnMessegeAccepted(Message::MessageID messageID)
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
void Item::CollisionResponce(GameObject* other)
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
		m_isGet = true;
	}
	default:
		break;
	}
}


/**
 * @brief の取得
 *
 * @param[in] なし
 *
 * @return 
 */
Item::UpStatus Item::GetUpStatus() const
{
	return m_upStatus;
}

/**
 * @brief の取得
 *
 * @param[in] なし
 *
 * @return 
 */
int Item::GetIncrease() const
{
	return m_increase;
}

float Item::GetTime() const
{
	return m_time;
}

bool Item::IsGet() const
{
	return m_isGet;
}

const DirectX::SimpleMath::Vector4& Item::GetColor()
{
	return m_color;
}

void Item::DecideColor()
{
	switch (m_upStatus)
	{
	case Item::Attack:
		m_color = DirectX::Colors::Red;
		break;
	case Item::Diffece:
		m_color = DirectX::Colors::Blue;
		break;
	case Item::Speed:
		m_color = DirectX::Colors::Cyan;
		break;
	default:
		break;
	}
}



