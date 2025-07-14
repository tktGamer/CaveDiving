#pragma once
#ifndef COMPONENT_FACTORY_DEFINED
#define COMPONENT_FACTORY_DEFINED
#include "Interface/IComponent.h"
#include "Interface/IComponentFactory.h"

// 部品ファクトリクラスを定義する
class Component : public IComponentFactory
{
public:
	// 「砲塔」を生成する
	static std::unique_ptr<IComponent> CreateTurret(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// 「砲塔下部」を生成する
	static std::unique_ptr<IComponent> CreateTurretBottom(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// 「砲塔中部」を生成する
	static std::unique_ptr<IComponent> CreateTurretMiddle(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// 「砲塔上部」を生成する
	static std::unique_ptr<IComponent> CreateTurretTop(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// 「砲塔砲台」を生成する
	static std::unique_ptr<IComponent> CreateTurretFort(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// 「砲塔砲身」を生成する
	static std::unique_ptr<IComponent> CreateTurretGun(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// 「砲塔プレート」を生成する
	static std::unique_ptr<IComponent> CreateTurretPlate(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);

	// 「砲塔脚」を生成する
	static std::unique_ptr<IComponent> CreateTurretFoot(
		IComponent* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const float& initialAngle,
		const float& mass);
};

#endif		// COMPONENT_FACTORY_DEFINED