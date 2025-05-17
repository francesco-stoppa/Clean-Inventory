#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InventorySystem/Items/ItemTypeEnum.h" /*
#include "ModifiersSystem/Components/ModifierDispatcher.h"
#include "ModifiersSystem/Data/ModifierBase.h"*/
#include "ItemInfo.generated.h"

/* A data resource that I use to be able to define a game object. */
UCLASS()
class CLEAN_INVENTORY_API UItemInfo : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* assetThumbnail = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundBase> itemSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UNiagaraSystem> itemVFX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType type;
	
	UPROPERTY(EditAnywhere,  meta = (UIMin = 1), BlueprintReadWrite)
	int maxAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float useItemTime = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveItemTime = 0.0f;
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UModifierBase*> Modifiers;*/
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UseItem(/*class AGenericCharacter* Target*/);
	virtual void UseItem_Implementation(/*class AGenericCharacter* Target*/);
};
