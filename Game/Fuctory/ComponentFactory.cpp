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

// 「砲塔」を生成する
std::unique_ptr<IComponent> Component::CreateTurret(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// 「砲塔」を宣言する
	std::unique_ptr<IComponent> turret;
	// 部品番号をリセットする
	NodeBase::ResetComponentNumber();
	// Turret クラスのインスタンスを生成する
	turret.reset(new Turret(parent, initialPosition, initialAngle, mass));
	// 初期化する
	turret->Initialize();

	// Turretクラスのインスタンスを返す
	return std::move(turret);
}

// 「砲塔下部」を生成する
std::unique_ptr<IComponent> Component::CreateTurretBottom(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// 「砲塔下部」を宣言する
	std::unique_ptr<IComponent> turretBottom;
	// TurretBottom クラスのインスタンスを生成する
	turretBottom.reset(new TurretBottom(parent, initialPosition, initialAngle, mass));
	// 初期化する
	turretBottom->Initialize();
	// TurretBottomクラスのインスタンスを返す
	return std::move(turretBottom);
}

// 「砲塔脚」を生成する
std::unique_ptr<IComponent> Component::CreateTurretFoot(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// 「砲塔脚」を宣言する
	std::unique_ptr<IComponent> turretFoot;
	// TurretFoot クラスのインスタンスを生成する
	turretFoot.reset(new TurretFoot(parent, initialPosition, initialAngle, mass));
	// 初期化する
	turretFoot->Initialize();
	// TurretFootクラスのインスタンスを返す
	return std::move(turretFoot);
}

// 「砲塔中部」を生成する
std::unique_ptr<IComponent> Component::CreateTurretMiddle(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// 「砲塔中部」を宣言する
	std::unique_ptr<IComponent> turretMiddle;
	// TurretMiddle クラスのインスタンスを生成する
	turretMiddle.reset(new TurretMiddle(parent, initialPosition, initialAngle, mass));
	// 初期化する
	turretMiddle->Initialize();
	// TurretBottomクラスのインスタンスを返す
	return std::move(turretMiddle);
}

// 「砲塔上部」を生成する
std::unique_ptr<IComponent> Component::CreateTurretTop(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// 「砲塔上部」を宣言する
	std::unique_ptr<IComponent> turretTop;
	// TurretTop クラスのインスタンスを生成する
	turretTop.reset(new TurretTop(parent, initialPosition, initialAngle, mass));
	// 初期化する
	turretTop->Initialize();
	// TurretTopクラスのインスタンスを返す
	return std::move(turretTop);
}

// 「砲塔砲台」を生成する
std::unique_ptr<IComponent> Component::CreateTurretFort(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// 「砲塔砲台」を宣言する
	std::unique_ptr<IComponent> turretFort;
	// TurretMiddle クラスのインスタンスを生成する
	turretFort.reset(new TurretFort(parent, initialPosition, initialAngle, mass));
	// 初期化する
	turretFort->Initialize();
	// TurretFortクラスのインスタンスを返す
	return std::move(turretFort);
}

// 「砲塔砲身」を生成する
std::unique_ptr<IComponent> Component::CreateTurretGun(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// 「砲塔砲身」を宣言する
	std::unique_ptr<IComponent> turretGun;
	// TurretGun クラスのインスタンスを生成する
	turretGun.reset(new TurretGun(parent, initialPosition, initialAngle, mass));
	// 初期化する
	turretGun->Initialize();
	// TurretGunクラスのインスタンスを返す
	return std::move(turretGun);
}

// 「砲塔プレート」を生成する
std::unique_ptr<IComponent> Component::CreateTurretPlate(
	IComponent* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const float& initialAngle,
	const float& mass
)
{
	// 「砲塔プレート」を宣言する
	std::unique_ptr<IComponent> turretPlate;
	// TurretPlate クラスのインスタンスを生成する
	turretPlate.reset(new TurretPlate(parent, initialPosition, initialAngle, mass));
	// 初期化する
	turretPlate->Initialize();
	// TurretPlateクラスのインスタンスを返す
	return std::move(turretPlate);
}
