#pragma once

#include "CoreMinimal.h"
#include "OldItemTypeEnum.generated.h"

UENUM(BlueprintType)
enum class EOldItemType : uint8
{
	Stim,
	Heal,
	Ammo
};
