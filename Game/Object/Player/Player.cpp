/**
 * @file   Player.cpp
 *
 * @brief  ＸＸＸＸに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Player.h"

#include "Game/Interface/IState.h"
#include"Game/Shader.h"
#include"Game/Common/Collision/Sphere.h"

const std::vector<D3D11_INPUT_ELEMENT_DESC> Player::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,								D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",	    0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] modelParms モデルパラメータ
 */
Player::Player()
	: GameObject(ObjectType::Player)
	, m_objectNumber{ CountUpNumber() }
	, m_messageID{  }
	, m_hp{100}
	, m_velocity{ 0.0f, 0.0f, 0.0f }
	, m_pGem{}
	, m_initialeDirection{ 0.0f, 0.0f, -1.0f }
	, m_sphere{ GetPosition(), 2.0f }
{
	Messenger::GetInstance()->Register(m_objectNumber, this);
}



/**
 * @brief デストラクタ
 */
Player::~Player()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Player::Initialize()
{
	// 状態の初期化
	m_idlingState = std::make_unique<PlayerIdling>(this);
	m_movingState = std::make_unique<PlayerMoving>(this);

	SetState(m_idlingState.get());

	SetTexture(ResourceManager::GetInstance()->RequestTexture("player.png"));

	SetModel(ResourceManager::GetInstance()->RequestModel(L"player.sdkmesh"));
	SetPosition(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f));
	SetRotation(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	SetScale(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));

	SetShape(&m_sphere);

	m_light = std::make_unique<Light>(GetPosition());

	Shader::GetInstance()->RegisterLight(m_light.get());

	BinaryFile VSData = ResourceManager::GetInstance()->RequestBinaryFile(L"Resources/Shaders/ModelShader/ModelVS.cso");

	//インプットレイアウトの作成
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
		&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(),
		VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_cBuffer);


}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Player::Update(float elapsedTime)
{
	DirectX::Keyboard::KeyboardStateTracker* traker = Graphics::GetInstance()->GetKeyboardTracker();

	GetState()->Update(elapsedTime);
	m_sphere.SetCenter(GetPosition());
	m_light->SetPosition(GetPosition());
	m_light->Update(elapsedTime);
}




/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Player::Draw()
{
	GetState()->Render();
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Player::Finalize()
{
}

void Player::OnMessegeAccepted(Message::MessageID messageID)
{
	switch (messageID)
	{
	case Message::IDLING:
		GameObject::ChangeState(m_idlingState.get());
		break;
	case Message::MOVING:
		GameObject::ChangeState(m_movingState.get());
		break;
	case Message::ATTACK:
		break;
	case Message::AVOIDANCE:
		break;
	case Message::DAMAGED:
		break;
	default:
		break;
	}
}

ID3D11InputLayout* Player::GetInputLayout() const
{
	return m_inputLayout.Get();
}

ID3D11Buffer* Player::GetCBuffer() const
{
	return m_cBuffer.Get();
}

void Player::SetGem(Gem* gem, int index)
{
	m_pGem[index] = gem;
}

int Player::GetObjectNumber()
{
	return m_objectNumber;
}

DirectX::SimpleMath::Vector3 Player::GetVelocity()
{
	return m_velocity;
}

void Player::SetVelocity(DirectX::SimpleMath::Vector3 v)
{
	m_velocity = v;
}
