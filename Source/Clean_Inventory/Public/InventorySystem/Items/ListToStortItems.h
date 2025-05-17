#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ListToStortItems.generated.h"

UCLASS()
class TBO02_API UListToStortItems : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Item")
	TArray<class UItemInfo*> sortList; 
};
