#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/Items/ItemInfo.h"
#include "ModifierItemInfo.generated.h"

UCLASS()
class TBO02_API UModifierItemInfo : public UItemInfo
{
	GENERATED_BODY()
public:
	void UseItem_Implementation(class AGenericCharacter* Target) override;
};
