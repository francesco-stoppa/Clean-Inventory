#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
/* #include "InventorySystem/Items/ItemTypeEnum.h"
#include "ModifiersSystem/Components/ModifierDispatcher.h"
#include "ModifiersSystem/Data/ModifierBase.h"*/
#include "ItemInfo.generated.h"

/* A data resource that I use to be able to define a game object. */
UCLASS()
class CLEAN_INVENTORY_API UItemInfo : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UTexture2D> AssetThumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<USoundBase> ItemSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item",  meta = (UIMin = 1, UIClampMin = 1))
	int32 MaxAmount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ItemTimeToUseIt = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item",  meta = (UIMin = 0, UIClampMin = 0))
	int32 CurrentAmount = 0;

	// ho bisogno di questo (?)
	UFUNCTION(BlueprintCallable, Category = "Item")
	void UseItem(/*class AGenericCharacter* Target*/);
	virtual void UseItem_Implementation(/*class AGenericCharacter* Target*/);
};
