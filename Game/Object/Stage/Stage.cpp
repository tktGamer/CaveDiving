/**
 * @file   Stage.cpp
 *
 * @brief  ステージに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/08/27
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Stage.h"
#include"Game/Common/Collision/CollisionManager.h"
#include<fstream>
#include<sstream>

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] parent 親オブジェクトのポインタ(なし)
 * @param[in] initialPosition 初期位置
 * @param[in] initialAngle    初期角度
 */
Stage::Stage(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	: m_messageID{  }
	,m_ground{}
	,m_wall{}
{
	//Messenger::GetInstance()->Register(GetObjectNumber(), this);

}



/**
 * @brief デストラクタ
 */
Stage::~Stage()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Stage::Initialize(bool* isOnLight, int size)
{
	//SetModel(ResourceManager::GetInstance()->RequestModel(L"block.sdkmesh"));
	//SetPosition(DirectX::SimpleMath::Vector3(0.0f, -1.5f, 0.0f));
	//SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	//SetScale(DirectX::SimpleMath::Vector3(70.0f, 1.0f, 70.0f));
	//SetTexture(ResourceManager::GetInstance()->RequestTexture("block.png"));
	//
	//SetShape(&m_box);

	m_ground = std::make_unique<Ground>(nullptr,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
	m_ground->Initialize();


	m_wall = std::make_unique<Wall>(nullptr, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
	m_wall->Initialize();


	GenerateIlumiRock(isOnLight, size);

	CollisionManager* pCM = CollisionManager::GetInstance();
	pCM->Register(m_ground.get());


	//m_rocks.emplace_back(std::make_unique<CandleStick>(nullptr, DirectX::SimpleMath::Vector3{ 0.0f,1.0f,0.0f }, DirectX::SimpleMath::Quaternion::Identity));
	//m_rocks.back()->Initialize(isOnLight[0]);
	//m_rocks.back()->SetPosition({ 5.0f, 0.0f, -25.0f });

	//pCM->Register(m_rocks.back().get());

	//m_rocks.emplace_back(std::make_unique<CandleStick>(nullptr, DirectX::SimpleMath::Vector3{ 0.0f,1.0f,0.0f }, DirectX::SimpleMath::Quaternion::Identity));
	//m_rocks.back()->Initialize(isOnLight[1]);
	//m_rocks.back()->SetPosition({ -5.0f, 0.0f, 35.0f });

	//pCM->Register(m_rocks.back().get());

}




/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Stage::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	
	m_ground->Update(elapsedTime,DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Quaternion::Identity);
	m_wall->Update(elapsedTime,DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Quaternion::Identity);

	for (std::unique_ptr<CandleStick>& rock : m_rocks) 
	{
		rock->Update(elapsedTime, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
	}
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Stage::Draw()
{
	//Shader* shader = Shader::GetInstance();	
	//ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//DirectX::DX11::CommonStates* states  = Graphics::GetInstance()->GetCommonStates();
	//DirectX::SimpleMath::Matrix  view    = Graphics::GetInstance()->GetViewMatrix();
	//DirectX::SimpleMath::Matrix  proj    = Graphics::GetInstance()->GetProjectionMatrix();


	m_ground->Draw();
	m_wall->Draw();

	for (std::unique_ptr<CandleStick>& rock : m_rocks)
	{
		rock->Draw();
	}
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Stage::Finalize()
{

}

void Stage::OnMessegeAccepted(Message::MessageID messageID)
{

}

std::list<std::unique_ptr<CandleStick>>& Stage::GetRocks()
{
	return m_rocks;
}

void Stage::GenerateIlumiRock(bool* isOnLight, int size)
{

	//パスの生成
	std::string path = "Resources/Data/LightPositionData.csv";
	//ファイルのオープン
	std::ifstream ifs{ path };
	if (!ifs.is_open())
	{
		//読み込み失敗
		return;
	}

	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	while (ifs)
	{
		int id = 0;
		//敵の種類を読み込む
		ifs >> id;
		ifs.ignore(); //カンマを読み飛ばす

		if (id <= 0) 
		{
			break;
		}

		//スポーン位置
		DirectX::SimpleMath::Vector3 spawnPos = DirectX::SimpleMath::Vector3::Zero;
		DirectX::SimpleMath::Vector3 color    = DirectX::SimpleMath::Vector3::One;
		float intensity = 1.0f;

		//座標を読み込む
		ifs >> spawnPos.x;
		ifs.ignore(); //カンマを読み飛ばす
		ifs >> spawnPos.y;
		ifs.ignore(); //カンマを読み飛ばす
		ifs >> spawnPos.z;
		ifs.ignore(); //カンマを読み飛ばす

		//ライトの色を読み込む
		ifs >> color.x;
		ifs.ignore(); //カンマを読み飛ばす
		ifs >> color.y;
		ifs.ignore(); //カンマを読み飛ばす
		ifs >> color.z;
		ifs.ignore(); //カンマを読み飛ばす
		//ライト強度を読み込む
		ifs >> intensity;
		ifs.ignore(); //カンマを読み飛ばす
		

		Shader::PointLight lightdata;
		lightdata.LightColor = color;
		lightdata.LightIntensity = intensity;

		m_rocks.emplace_back(std::make_unique<CandleStick>(lightdata,nullptr, DirectX::SimpleMath::Vector3{ 0.0f,1.0f,0.0f }, DirectX::SimpleMath::Quaternion::Identity));
		m_rocks.back()->Initialize(isOnLight[id-1]);
		m_rocks.back()->SetPosition(spawnPos);

		CollisionManager::GetInstance()->Register(m_rocks.back().get());


		//ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	}
	ifs.close();

}

