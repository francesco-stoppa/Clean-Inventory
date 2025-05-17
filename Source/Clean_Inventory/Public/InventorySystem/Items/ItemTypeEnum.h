#pragma once

#include "CoreMinimal.h"
#include "ItemTypeEnum.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Stim,
	Heal,
	Ammo
};
