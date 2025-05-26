#pragma once

#include "CoreMinimal.h"
//#include "InventorySystem/Items/Structs/Item.h"
#include "RandomicItem.generated.h"

/* A struct that I use to define an object and its spawn rate. */
USTRUCT(BlueprintType)
struct FRandomicItem
{
	GENERATED_BODY()
	/*
	UPROPERTY(EditAnywhere, Category = "Item")
	FOldItem item;*/
	UPROPERTY(EditAnywhere, Category = "Item", meta = (UIMin = 1, UIMax = 100, ClampMin = 1, ClampMax = 100, Units = "Percent"))
	int spawnRate = 100;
};
