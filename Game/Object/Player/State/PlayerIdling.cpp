#include "pch.h"
#include "Game/Object/Player/State/PlayerIdling.h"
#include "Game/Object/Player/Player.h"

// コンストラクタ
PlayerIdling::PlayerIdling(Player* player)
	:
	m_player(player),
	m_graphics{},
	m_context{}
{
	// グラフィックスを取得する
	m_graphics = Graphics::GetInstance();
	// コンテキストを取得する
	m_context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
}
// デストラクタ
PlayerIdling::~PlayerIdling()
{
}

// 初期化する
void PlayerIdling::Initialize()
{
	PreUpdate();
}

// 事前更新する
void PlayerIdling::PreUpdate()
{
}

// 更新する
void PlayerIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	// キーボードステートを取得する
	DirectX::Keyboard::KeyboardStateTracker* key = m_graphics->GetKeyboardTracker();
	if (key->pressed.Left || key->pressed.Right || key->pressed.Up || key->pressed.Down) 
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::MOVING);
	}
	if (key->pressed.Space) 
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::JUMPING);
	}
	if (key->pressed.Z) 
	{
		Messenger::GetInstance()->Notify(m_player->GetObjectNumber(), Message::ATTACK);
	}

	DirectX::SimpleMath::Vector3 v = m_player->GetVelocity();
	
	v.y += -0.8f * elapsedTime;

	m_player->SetVelocity(v);

	m_player->SetPosition(m_player->GetPosition() + m_player->GetVelocity());

}

// 事後更新する
void PlayerIdling::PostUpdate()
{
}

// 描画する
void PlayerIdling::Render()
{
	Graphics* graphics = Graphics::GetInstance();
	ID3D11DeviceContext*		 context = graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = graphics->GetProjectionMatrix();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Player::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(m_player->GetCurrentPosition(),m_player->GetCurrentQuaternion(),m_player->GetScale()).Transpose();
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_player->GetCBuffer(), 0, NULL, &cbuff, 0, 0);


	Shader* shader = Shader::GetInstance();

	m_player->GetModel()->Draw(context, *states, world, view, proj, false, [&]()
		{
			//	モデル表示をするための自作シェーダに関連する設定を行う
			

			//	画像用サンプラーの登録
			ID3D11SamplerState* sampler[1] = { states->PointWrap() };
			context->PSSetSamplers(0, 1, sampler);

			if (m_player->GetTexture() != nullptr)
			{
				//	読み込んだ画像をピクセルシェーダに伝える
				//	自作VSはt0を使っているため、
				//	t0がメインで使われていると勝手に想定。
				context->PSSetShaderResources(0, 1, m_player->GetTexture());
			}

			//	半透明描画指定
			ID3D11BlendState* blendstate = states->NonPremultiplied();

			//	透明判定処理
			context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

			//	深度バッファに書き込み参照する
			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			//	カリングはなし
			context->RSSetState(states->CullClockwise());
			
			Shader::GetInstance()->StartShader(Shader::Model,m_player->GetCBuffer());
			
			context->IASetInputLayout(m_player->GetInputLayout());

		});
	Shader::GetInstance()->EndShader();
#ifdef _DEBUG
#endif // DEBUG

}

// 後処理を行う
void PlayerIdling::Finalize()
{
}
