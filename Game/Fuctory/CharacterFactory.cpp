#include "pch.h"
#include "CharacterFactory.h"
#include"../Object/Player/Player.h"
#include"../Object/Player/Hand.h"
#include"../Object/Player/Pikel.h"
#include"../Object/Enemy/Bat/Bat.h"
#include"../Object/Enemy/Bat/Wing.h"
// �u�C���v�𐶐�����
//std::unique_ptr<IComponent> Component::CreateTurret(
//	IComponent* parent,
//	const DirectX::SimpleMath::Vector3& initialPosition,
//	const float& initialAngle,
//	const float& mass
//)
//{
//	// �u�C���v��錾����
//	std::unique_ptr<IComponent> turret;
//	// ���i�ԍ������Z�b�g����
//	NodeBase::ResetComponentNumber();
//	// Turret �N���X�̃C���X�^���X�𐶐�����
//	turret.reset(new Turret(parent, initialPosition, initialAngle, mass));
//	// ����������
//	turret->Initialize();
//
//	// Turret�N���X�̃C���X�^���X��Ԃ�
//	return std::move(turret);
//}

/**
 * @brief �u�v���C���[�v�̐���
 *
 * @param[in] parent   �e�̃|�C���^
 * @param[in] initialPosition�@�����ʒu
 * @param[in] initialAngle�@�@�����p�x
 *
 * @return �v���C���[�N���X
 */
std::unique_ptr<Character> CharacterFactory::CreatePlayer(Character* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	//�u�v���C���[�v��錾����
	std::unique_ptr<Character> player;
	//Player�N���X�̃C���X�^���X�𐶐�����
	player = std::make_unique<Player>(parent, initialPosition, initialAngle);
	//����������
	player->Initialize();

	// Player�N���X�̃C���X�^���X��Ԃ�
	return std::move(player);
}

/**
 * @brief �u�v���C���[�̎�v�̐���
 *
 * @param[in] parent   �e�̃|�C���^
 * @param[in] initialPosition�@�����ʒu
 * @param[in] initialAngle�@�@�����p�x
 *
 * @return �v���C���[�̎�N���X
 */

std::unique_ptr<GameObject> CharacterFactory::CreateHand(Character* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	//�u�v���C���[�̎�v��錾����
	std::unique_ptr<GameObject> hand;
	//Player�N���X�̃C���X�^���X�𐶐�����
	hand = std::make_unique<Hand>(parent, initialPosition, initialAngle);
	//����������
	hand->Initialize();

	// Hand�N���X�̃C���X�^���X��Ԃ�
	return std::move(hand);
}

/**
 * @brief �u�s�b�P���v�̐���
 *
 * @param[in] parent   �e�̃|�C���^
 * @param[in] initialPosition�@�����ʒu
 * @param[in] initialAngle�@�@�����p�x
 *
 * @return �s�b�P���N���X
 */
std::unique_ptr<GameObject> CharacterFactory::CreatePikle(Character* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	//�u�s�b�P���v��錾����
	std::unique_ptr<GameObject> pikel;
	//Pikel�N���X�̃C���X�^���X�𐶐�����
	pikel = std::make_unique<Pikel>(parent, initialPosition, initialAngle);
	//����������
	pikel->Initialize();

	// Pikel�N���X�̃C���X�^���X��Ԃ�
	return std::move(pikel);
}

/**
 * @brief �u�R�E�����̓G�v�̐���
 *
 * @param[in] parent   �e�̃|�C���^
 * @param[in] initialPosition�@�����ʒu
 * @param[in] initialAngle�@�@�����p�x
 *
 * @return �R�E�����̓G�N���X
 */
std::unique_ptr<Character> CharacterFactory::CreateBat(Character* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	//�u�R�E�����v��錾����
	std::unique_ptr<Character> bat;
	//Pikel�N���X�̃C���X�^���X�𐶐�����
	bat = std::make_unique<Bat>(parent, initialPosition, initialAngle);
	//����������
	bat->Initialize();

	// Bat�N���X�̃C���X�^���X��Ԃ�
	return std::move(bat);
}

/**
 * @brief �u�R�E�����̉H�v�̐���
 *
 * @param[in] parent   �e�̃|�C���^
 * @param[in] initialPosition�@�����ʒu
 * @param[in] initialAngle�@�@�����p�x
 *
 * @return �R�E�����̉H�N���X
 */
std::unique_ptr<GameObject> CharacterFactory::CreateBatWing(Character* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
{
	//�u�R�E�����̉H�v��錾����
	std::unique_ptr<GameObject> wing;
	//Wing�N���X�̃C���X�^���X�𐶐�����
	wing = std::make_unique<Wing>(parent, initialPosition, initialAngle);
	//����������
	wing->Initialize();

	// Wing�N���X�̃C���X�^���X��Ԃ�
	return std::move(wing);
}
