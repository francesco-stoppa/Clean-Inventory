#pragma once

#include "CoreMinimal.h"
#include "EnumList.generated.h"

UENUM(BlueprintType)
enum class EDirections : uint8
{
	Default,
	Right,
	Left,
	Up,
	Down,
	Enter
};

UENUM(BlueprintType)
enum class ECommands : uint8
{
	Default,
	Inventory,
	Open,
	Take,
	Switch,
	Revert,
	Select,
	Use,
	Info,
	Drop,
	Close
};

UENUM(BlueprintType)
enum class EInput : uint8
{
	A,
	B,
	X,
	Y,
	Tab,
	E,
	BackSpace,
	Enter
};

UENUM(BlueprintType)
enum class ECommandStats : uint8
{
	Default,
	Game,
	Inventory,
	Switch,
	Info,
	Chest
};

