#pragma once
#ifndef COMPONENT_FACTORY_DEFINED
#define COMPONENT_FACTORY_DEFINED
#include "Interface/IComponent.h"
#include "Interface/IComponentFactory.h"

// ���i�t�@�N�g���N���X���`����
class Component : public IComponentFactory
{
public:
	// �u�C���v�𐶐�����
	static std::unique_ptr<IComponent> CreateTurret(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// �u�C�������v�𐶐�����
	static std::unique_ptr<IComponent> CreateTurretBottom(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// �u�C�������v�𐶐�����
	static std::unique_ptr<IComponent> CreateTurretMiddle(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// �u�C���㕔�v�𐶐�����
	static std::unique_ptr<IComponent> CreateTurretTop(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// �u�C���C��v�𐶐�����
	static std::unique_ptr<IComponent> CreateTurretFort(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// �u�C���C�g�v�𐶐�����
	static std::unique_ptr<IComponent> CreateTurretGun(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// �u�C���v���[�g�v�𐶐�����
	static std::unique_ptr<IComponent> CreateTurretPlate(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// �u�C���r�v�𐶐�����
	static std::unique_ptr<IComponent> CreateTurretFoot(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);
};

#endif		// COMPONENT_FACTORY_DEFINED