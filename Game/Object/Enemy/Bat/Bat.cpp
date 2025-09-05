/**
 * @file   Bat.cpp
 *
 * @brief  コウモリの敵に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/08/27
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Bat.h"
#include "Game/Common/Collision/CollisionManager.h"
#include"../CaveDiving/Game/Fuctory/CharacterFactory.h"
#include"Game/Common/DamageSystem.h"
#include"Game/Object/Weapon.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
 */
Bat::Bat(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:m_graphics{Graphics::GetInstance()}
	, Character(50,8,5,Tag::ObjectType::Enemy, parent, initialPosition, initialAngle)
	, m_sphere{ GetPosition(), 2.0f } // 初期位置とサイズを設定
	,m_frameCount{}
{
	SetTexture(ResourceManager::GetInstance()->RequestTexture("bat.png"));

	SetModel(ResourceManager::GetInstance()->RequestModel(L"bat.sdkmesh"));

	SetShape(&m_sphere);

	m_leftWing = std::make_unique<Wing>(this, DirectX::SimpleMath::Vector3{-0.5f,0.0f,0.0f}, DirectX::XMConvertToRadians(0.0f));
	m_rightWing = std::make_unique<Wing>(this, DirectX::SimpleMath::Vector3{0.5f,0.0f,0.0f}, DirectX::XMConvertToRadians(180.0f));



}



/**
 * @brief デストラクタ
 */
Bat::~Bat()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Bat::Initialize()
{
	// 状態の初期化
	m_idlingState  = std::make_unique<BatIdling>(this);
	m_movingState  = std::make_unique<BatMoving>(this);
	m_attackState  = std::make_unique<BatAttack>(this);
	m_chasingState = std::make_unique<BatChasing>(this);
	m_attackPreaparing = std::make_unique<BatAttackPreparing>(this,m_rightWing.get(), m_leftWing.get());

	SetState(m_idlingState.get());


	SetPosition(DirectX::SimpleMath::Vector3(0.0f, 1.0f, -5.0f));
	SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	SetScale(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));

	m_currentPosition = m_initialPosition  + GetPosition();
	m_currentAngle = m_initialAngle * GetQuaternion() ;

}



/**
 * @brief 更新処理
 *
 * @param[in] currentPosition 親の座標
 * @param[in] currentAngle　親の角度
 *
 * @return なし
 */
void Bat::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	//生きていない場合更新しない
	if (!IsAlive())
	{
		return;
	}


	//現在の状態を更新
	GetState()->Update(elapsedTime);


	m_currentPosition = m_initialPosition + currentPosition + GetPosition();
	m_currentAngle =m_initialAngle * GetQuaternion() * currentAngle;
	
	//当たり判定更新
	m_sphere.SetCenter(m_currentPosition);

	//子クラス更新
	m_leftWing->Update(elapsedTime, GetCurrentPosition(), GetCurrentQuaternion());
	m_rightWing->Update(elapsedTime, GetCurrentPosition(), GetCurrentQuaternion());

	//時間経過
	m_frameCount += elapsedTime;
}




/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Bat::Draw()
{
	//生きていない場合描画しない
	if (!IsAlive()) 
	{
		return;
	}


	//現在の状態を描画
	//GetState()->Render();

	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext* context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Bat::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale()).Transpose();
	cbuff.matView = graphics->GetViewMatrix().Transpose();
	cbuff.matProj = graphics->GetProjectionMatrix().Transpose();

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

			context->IASetInputLayout(shader->GetInputLayout(Shader::Model));

		});
	Shader::GetInstance()->EndShader();

	m_leftWing->Draw();
	m_rightWing->Draw();
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Bat::Finalize()
{

}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void Bat::OnMessegeAccepted(Message::MessageID messageID)
{
	switch (messageID)
	{
	case Message::IDLING:
		GameObject::ChangeState(m_idlingState.get());
		break;
	case Message::MOVING:
		GameObject::ChangeState(m_movingState.get());
		break;
	case Message::GROUNDATTACK:
		GameObject::ChangeState(m_attackState.get());
		break;
	case Message::DAMAGED:
		break;
	case Message::CHASING:
		GameObject::ChangeState(m_chasingState.get());
		break;
	case Message::ATTACKPREPARING:
		GameObject::ChangeState(m_attackPreaparing.get());
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
void Bat::CollisionResponce(GameObject* other)
{
	switch (other->GetObjectType())
	{
		case Tag::ObjectType::Player:
		{
			// プレイヤーとの衝突処理
			// ここでは何もしないが、必要に応じて実装
			break;
		}
		case Tag::ObjectType::Stage:
		{
			//ステージとの衝突応答　押し出し
			SetPosition(CollisionManager::GetInstance()->PushOut(dynamic_cast<Box*>(other->GetShape()), &m_sphere));
			//速度をリセット
			m_velocity.y = 0.0f;

			break;
		}
		case Tag::ObjectType::Weapon:
		{
			Weapon* weapon = other->Cast<Weapon>();
			//ピッケルとの衝突応答
			DamageSystem::GetInstance()->DamageToCharacter(weapon->GetOwner(),this);
			//管理クラスに削除依頼を出す
			//Damage(10);

			break;
		}
	default:
		break;
	}
}



const float Bat::GetFrameCount() const
{
	return m_frameCount;
}

void Bat::ResetFrameCount()
{
	m_frameCount = 0.0f;
}

DirectX::SimpleMath::Vector3 Bat::GetVelocity()
{
	return m_velocity;
}

void Bat::SetVelocity(DirectX::SimpleMath::Vector3 v)
{
	m_velocity = v;
}

