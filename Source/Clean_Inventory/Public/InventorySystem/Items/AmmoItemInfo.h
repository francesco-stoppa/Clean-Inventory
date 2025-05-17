#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InventorySystem/Items/ItemInfo.h"
#include "AmmoItemInfo.generated.h"

UCLASS()
class TBO02_API UAmmoItemInfo : public UItemInfo 
{
	GENERATED_BODY()
public:
	void UseItem_Implementation(class AGenericCharacter* Target) override;
};
