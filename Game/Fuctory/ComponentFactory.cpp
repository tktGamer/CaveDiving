#include "Main/pch.h"
#include "TurretFactory/ComponentFactory.h"
#include "Common/Constant.h"
#include "Interface/IComponent.h"
#include "Node/NodeBase.h"
#include "Turret/Header/Turret.h"
#include "Turret/Header/TurretBottom.h"
#include "Turret/Header/TurretFoot.h"
#include "Turret/Header/TurretFort.h"
#include "Turret/Header/TurretGun.h"
#include "Turret/Header/TurretMiddle.h"
#include "Turret/Header/TurretPlate.h"
#include "Turret/Header/TurretTop.h"

// �u�C���v�𐶐�����
std::unique_ptr<IComponent> Component::CreateTurret(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// �u�C���v��錾����
	std::unique_ptr<IComponent> turret;
	// ���i�ԍ������Z�b�g����
	NodeBase::ResetComponentNumber();
	// Turret �N���X�̃C���X�^���X�𐶐�����
	turret.reset(new Turret(parent, initialPosition, initialAngle, mass));
	// ����������
	turret->Initialize();

	// Turret�N���X�̃C���X�^���X��Ԃ�
	return std::move(turret);
}

// �u�C�������v�𐶐�����
std::unique_ptr<IComponent> Component::CreateTurretBottom(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// �u�C�������v��錾����
	std::unique_ptr<IComponent> turretBottom;
	// TurretBottom �N���X�̃C���X�^���X�𐶐�����
	turretBottom.reset(new TurretBottom(parent, initialPosition, initialAngle, mass));
	// ����������
	turretBottom->Initialize();
	// TurretBottom�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretBottom);
}

// �u�C���r�v�𐶐�����
std::unique_ptr<IComponent> Component::CreateTurretFoot(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// �u�C���r�v��錾����
	std::unique_ptr<IComponent> turretFoot;
	// TurretFoot �N���X�̃C���X�^���X�𐶐�����
	turretFoot.reset(new TurretFoot(parent, initialPosition, initialAngle, mass));
	// ����������
	turretFoot->Initialize();
	// TurretFoot�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretFoot);
}

// �u�C�������v�𐶐�����
std::unique_ptr<IComponent> Component::CreateTurretMiddle(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// �u�C�������v��錾����
	std::unique_ptr<IComponent> turretMiddle;
	// TurretMiddle �N���X�̃C���X�^���X�𐶐�����
	turretMiddle.reset(new TurretMiddle(parent, initialPosition, initialAngle, mass));
	// ����������
	turretMiddle->Initialize();
	// TurretBottom�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretMiddle);
}

// �u�C���㕔�v�𐶐�����
std::unique_ptr<IComponent> Component::CreateTurretTop(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// �u�C���㕔�v��錾����
	std::unique_ptr<IComponent> turretTop;
	// TurretTop �N���X�̃C���X�^���X�𐶐�����
	turretTop.reset(new TurretTop(parent, initialPosition, initialAngle, mass));
	// ����������
	turretTop->Initialize();
	// TurretTop�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretTop);
}

// �u�C���C��v�𐶐�����
std::unique_ptr<IComponent> Component::CreateTurretFort(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// �u�C���C��v��錾����
	std::unique_ptr<IComponent> turretFort;
	// TurretMiddle �N���X�̃C���X�^���X�𐶐�����
	turretFort.reset(new TurretFort(parent, initialPosition, initialAngle, mass));
	// ����������
	turretFort->Initialize();
	// TurretFort�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretFort);
}

// �u�C���C�g�v�𐶐�����
std::unique_ptr<IComponent> Component::CreateTurretGun(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// �u�C���C�g�v��錾����
	std::unique_ptr<IComponent> turretGun;
	// TurretGun �N���X�̃C���X�^���X�𐶐�����
	turretGun.reset(new TurretGun(parent, initialPosition, initialAngle, mass));
	// ����������
	turretGun->Initialize();
	// TurretGun�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretGun);
}

// �u�C���v���[�g�v�𐶐�����
std::unique_ptr<IComponent> Component::CreateTurretPlate(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// �u�C���v���[�g�v��錾����
	std::unique_ptr<IComponent> turretPlate;
	// TurretPlate �N���X�̃C���X�^���X�𐶐�����
	turretPlate.reset(new TurretPlate(parent, initialPosition, initialAngle, mass));
	// ����������
	turretPlate->Initialize();
	// TurretPlate�N���X�̃C���X�^���X��Ԃ�
	return std::move(turretPlate);
}
