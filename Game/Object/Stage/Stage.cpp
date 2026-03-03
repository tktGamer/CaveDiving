/**
 * @file   Stage.cpp
 *
 * @brief  ステージに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/22
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Stage.h"
#include"Game/Common/Collision/CollisionManager.h"
#include"Game/Shader/ShaderManager.h"
#include<fstream>
#include<sstream>
#include"Game/Factory/GameObjectFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] parent 親オブジェクトのポインタ(なし)
 * @param[in] initialPosition 初期位置
 * @param[in] initialAngle    初期角度
 */
Stage::Stage(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	: 
	m_messageID{},
	m_ground{},
	m_wall{},
	m_rocks{}
{
	UNREFERENCED_PARAMETER(parent);
	UNREFERENCED_PARAMETER(initialPosition);
	UNREFERENCED_PARAMETER(initialAngle);

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
	//地面の生成
	m_ground = GameObjectFactory::CreateGround(nullptr, INITIAL_GROUND_POS, DirectX::SimpleMath::Quaternion::Identity,INITIAL_GROUND_SCALE);
	//壁の生成
	m_wall = GameObjectFactory::CreateWall(nullptr, INITIAL_WALL_POS, DirectX::SimpleMath::Quaternion::Identity, INITIAL_WALL_SCALE);
	//石の生成
	GenerateIlumiRock(isOnLight, size);

	CollisionManager* pCM = CollisionManager::GetInstance();
	pCM->Register(m_ground.get());
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Stage::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	UNREFERENCED_PARAMETER(currentPosition);
	UNREFERENCED_PARAMETER(currentAngle);
	//地面更新
	m_ground->Update(DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Quaternion::Identity);
	//壁更新
	m_wall->Update(DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Quaternion::Identity);
	//石更新
	for (std::unique_ptr<RumiRock>& rock : m_rocks)
	{
		rock->Update( DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
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

	for (std::unique_ptr<RumiRock>& rock : m_rocks)
	{
		if (!rock->IsOnLight()) 
		{
			rock->Draw();
		}
	}
}

void Stage::BloomDraw()
{
	m_ground->Draw();
	m_wall->Draw();
	for (std::unique_ptr<RumiRock>& rock : m_rocks)
	{
		if(rock->IsOnLight())
		{
			rock->Draw();

		}
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
	messageID;
}

/**
 * @brief 石の取得
 *
 * @param[in] なし
 *
 * @return 石のリスト
 */
std::list<std::unique_ptr<RumiRock>>& Stage::GetRocks()
{
	return m_rocks;
}

/**
 * @brief 石の生成
 *
 * @param[in] isOnLight　ライトがオンかの配列
 * @param[in] size　配列の要素数
 *
 * @return なし
 */
void Stage::GenerateIlumiRock(bool* isOnLight, int size)
{

	//パスの生成
	std::string path = ResourcePath::DATA::LIGHT;
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
		

		ModelShader::PointLightCB lightdata;
		lightdata.LightColor = color;
		lightdata.LightIntensity = intensity;

		m_rocks.emplace_back(std::make_unique<RumiRock>(lightdata,nullptr, spawnPos, DirectX::SimpleMath::Quaternion::Identity));
		m_rocks.back()->Initialize(isOnLight[id-1]);

		CollisionManager::GetInstance()->Register(m_rocks.back().get());


		//ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	}
	ifs.close();
}