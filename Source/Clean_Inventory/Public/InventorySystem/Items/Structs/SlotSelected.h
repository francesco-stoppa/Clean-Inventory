#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/Inventory/InventoryBase.h"
#include "SlotSelected.generated.h"

/* struct that I use to define a slot in my inventory */
USTRUCT(BlueprintType)
struct FSlotSelected
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Slot")
	class UInventoryBase* inventory = nullptr;
	UPROPERTY(EditAnywhere, Category = "Slot",  meta = (UIMin = 0))
	int index = 0;
};