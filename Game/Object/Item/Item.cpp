/**
 * @file   Item.cpp
 *
 * @brief  アイテムの基底に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/19
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Item.h"
#include"Game/Common/Collision/CollisionManager.h"
#include"Game/Shader/ShaderManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] itemInfo  アイテムの情報
 * @param[in] type　オブジェクトの種類
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
 */
Item::Item(const ItemInfo& itemInfo, const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	GameObject{ Tag::ObjectType::Item,parent,initialPosition,initialAngle },
	m_itemInfomation{itemInfo},
	m_box{ initialPosition,BOX_COLLISION_SIZE },
	m_isGet{ false },
	m_color{ DirectX::Colors::White },
	m_display{ Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext() }

{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	//モデル設定
	SetModel(resourceManager->RequestModel(ResourcePath::MODEL::ITEM));
	//テクスチャ設定
	SetTexture(resourceManager->RequestTexture(ResourcePath::TEXTURE::ITEM));
	//当たり判定設定
	SetShape(&m_box);
	//当たり判定管理クラスに登録
	CollisionManager::GetInstance()->Register(this);
	//色を決める
	DecideColor();
}

/**
 * @brief デストラクタ
 */
Item::~Item()
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
void Item::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	//位置の更新
	SetCurrentPosition( currentPosition + GetPosition());
	//角度の更新
	SetCurrentAngle(GetQuaternion() * currentAngle );
	//当たり判定更新
	UpdateCollision(GetCurrentPosition());
}

/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void Item::Draw()
{
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();
	ShaderManager* shader = ShaderManager::GetInstance();

	DirectX::SimpleMath::Matrix world = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale());
	//	シェーダーに渡す追加のバッファを作成する。
	ModelShader::ItemCB cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.color = GetColor();
	//	受け渡し用バッファの内容更新(ItemCBからID3D11Bufferへの変換）
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

			shader->StartShader(ShaderManager::Item_Model);

			context->IASetInputLayout(shader->GetInputLayout(ShaderManager::ShaderType::Item_Model));

		});
	shader->EndShader();

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
void Item::OnMessegeAccepted(Message::MessageID messageID)
{
	messageID;
	//switch (messageID)
	//{
	//default:
	//	break;
	//}
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
	break;
	case Tag::ObjectType::Player:
	{
		
		//取得された
		SetIsGet(true);
		//取得したオブジェクトの座標をセット
		SetItemGetObjectPos(other->GetCurrentPosition());
		//派生クラスの追加処理
		OnItemGetExtra(other);
	}
	break;
	default:
		break;
	}
}

/**
 * @brief 当たり判定の位置更新
 *
 * @param[in] center  中心座標
 *
 * @return　なし
 */
void Item::UpdateCollision(const DirectX::SimpleMath::Vector3& center)
{
	m_box.SetCenter(center);
}


/**
 * @brief アイテム情報の取得
 *
 * @param[in] なし
 *
 * @return　アイテム情報
 */
const Item::ItemInfo& Item::GetItemInfo()
{
	return m_itemInfomation;
}

/**
 * @brief アイテム効果の種類の取得
 *
 * @param[in] なし
 *
 * @return
 */
const Item::EffectType& Item::GetEffectType() const
{
	return m_itemInfomation.type;
}

/**
 * @brief 上昇量の取得
 *
 * @param[in] なし
 *
 * @return
 */
const int& Item::GetIncrease() const
{
	return m_itemInfomation.increase;
}

/**
 * @brief 効果時間の取得
 *
 * @param[in] なし
 *
 * @return
 */
const float& Item::GetTime() const
{
	return m_itemInfomation.time;
}


/**
 * @brief アイテムを取得されたか
 *
 * @param[in] なし
 *
 * @return  true  取得された
 * @return  false 取得されていない
 */
const bool& Item::IsGet() const
{
	return m_isGet;
}


/**
 * @brief 取得されたかの設定
 *
 * @param[in] isGet  取得されたか
 *
 * @return　なし
 */
void Item::SetIsGet(const bool& isGet)
{
	m_isGet = isGet;
}


/**
 * @brief アイテムを取得したオブジェクトの座標を設定
 *
 * @param[in] pos  取得されたか
 *
 * @return　なし
 */
void Item::SetItemGetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	m_gotObjectPos = &pos;
}

/**
 * @brief アイテムを取得したオブジェクトの座標の取得
 *
 * @param[in] なし
 *
 * @return　アイテムを取得したオブジェクトの座標
 */
const DirectX::SimpleMath::Vector3& Item::GetItemGetObjectPos()
{
	return *m_gotObjectPos;
}


/**
 * @brief アイテムの色の取得
 *
 * @param[in] なし
 *
 * @return　アイテムの色
 */
const DirectX::SimpleMath::Vector4& Item::GetColor()
{
	return m_color;
}


/**
 * @brief アイテムを色を決定
 *
 * @param[in] なし
 *
 * @return　なし
 */
void Item::DecideColor()
{
	switch (m_itemInfomation.type)
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
	case Item::Outline:
		m_color = DirectX::Colors::Purple;
	default:
		break;
	}
}