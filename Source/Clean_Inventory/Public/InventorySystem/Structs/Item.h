#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/Items/ItemInfo.h"
#include "Item.generated.h"
/*
UENUM(BlueprintType)
enum class EItemType : uint8
{
	Empty,
	Default,
	Consumable,
	QuestItem
};*/

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_BODY()

	// Variables
public:
	UPROPERTY()
	FName Name;
	UPROPERTY()
	FName Description;
	//UPROPERTY()
	//EItemType ItemType;
	UPROPERTY(meta = (UIMin = 1, UIClampMin = 1))
	int32 MaxAmount = 1;
	UPROPERTY(meta = (UIMin = 0, UIClampMin = 0))
	int32 CurrentAmount = 0;
	UPROPERTY()
	float ItemTimeToUseIt = 0.0f;
	UPROPERTY()
	TObjectPtr<UTexture2D> AssetThumbnail;

	// Constructor -----------------------------------------------------------------------------------------------------
	// Empty
	FItem() :
	Name(TEXT("Empty")),
	Description(TEXT("None")), 
	//ItemType(EItemType::Empty),
	MaxAmount(0),
	CurrentAmount(0),
	ItemTimeToUseIt(0.f),
	AssetThumbnail(nullptr) {}
	
	// By values
	FItem(FName NewName, FName NewDescription, /*EItemType NewItemType,*/ int32 NewMaxAmount, int32 NewCurrentAmount, float NewItemTimeToUseIt, const TObjectPtr<class UTexture2D>& NewAssetThumbnail) :
	Name(NewName),
    Description(NewDescription),
    //ItemType(NewItemType),
	MaxAmount(NewMaxAmount),
	CurrentAmount(NewCurrentAmount),
	ItemTimeToUseIt(NewItemTimeToUseIt),
	AssetThumbnail(NewAssetThumbnail) {}

	// From a pointer
	static FItem FromPointer(const UItemInfo* Source)
	{
		FItem NewItem;
		
		if (Source)
		{
			NewItem.Name = Source->Name;
			NewItem.Description = Source->Description;
			//NewItem.ItemType = Source->ItemType;
			NewItem.MaxAmount = Source->MaxAmount;
			NewItem.CurrentAmount = Source->CurrentAmount;
			NewItem.ItemTimeToUseIt = Source->ItemTimeToUseIt;
			NewItem.AssetThumbnail = Source->AssetThumbnail;
		}
		return NewItem;
	}
	
	// From a pointer
	static FItem CopyItem(const FItem* Source)
	{
		FItem NewItem;
		
		if (Source)
		{
			NewItem.Name = Source->Name;
			NewItem.Description = Source->Description;
			//NewItem.ItemType = Source->ItemType;
			NewItem.MaxAmount = Source->MaxAmount;
			NewItem.CurrentAmount = Source->CurrentAmount;
			NewItem.ItemTimeToUseIt = Source->ItemTimeToUseIt;
			NewItem.AssetThumbnail = Source->AssetThumbnail;
		}
		return NewItem;
	}
};

