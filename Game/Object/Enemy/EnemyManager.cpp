/**
 * @file   EnemyManager.cpp
 *
 * @brief  �G�Ǘ��Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "EnemyManager.h"

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
EnemyManager::EnemyManager()
	:m_graphics{Graphics::GetInstance()}
{

}



/**
 * @brief �f�X�g���N�^
 */
EnemyManager::~EnemyManager()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void EnemyManager::Initialize()
{
	
}



/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void EnemyManager::Update()
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();
	for (std::unique_ptr<GameObject>& enemy : m_enemies)
	{
		enemy->Update(elapsedTime, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity);
	}
}



/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void EnemyManager::Draw()
{
	ID3D11DeviceContext*		 context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = m_graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = m_graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = m_graphics->GetProjectionMatrix();

	for (std::unique_ptr<GameObject>& enemy : m_enemies)
	{
		enemy->Draw();
	}

}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void EnemyManager::Finalize()
{

}

void EnemyManager::Spawn()
{
	m_enemies.emplace_back(std::make_unique<Bat>( nullptr, DirectX::SimpleMath::Vector3::Zero, DirectX::XMConvertToRadians(0.0f)));
}
