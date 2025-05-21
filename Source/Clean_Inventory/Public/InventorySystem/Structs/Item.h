#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/Items/ItemInfo.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Default,
	Consumable,
	QuestItem
};

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_BODY()

	// Variables
public:
	UPROPERTY(Category = "Item")
	FName Name;
	UPROPERTY(Category = "Item")
	FText Description;
	UPROPERTY(Category = "Item")
	EItemType ItemType;
	UPROPERTY(Category = "Item",  meta = (UIMin = 1, UIClampMin = 1))
	int32 MaxAmount = 1;
	UPROPERTY(Category = "Item",  meta = (UIMin = 0, UIClampMin = 0))
	int32 CurrentAmount = 0;
	UPROPERTY(Category = "Item")
	float ItemTimeToUseIt = 0.0f;
	UPROPERTY(Category = "Item")
	TObjectPtr<UTexture2D> AssetThumbnail;

	// Constructor -----------------------------------------------------------------------------------------------------
	// Base
	FItem() :
	Name(TEXT("Default")),
	Description(TEXT("...")), 
	ItemType(EItemType::Default),
	MaxAmount(1),
	CurrentAmount(0),
	ItemTimeToUseIt(0.f),
	AssetThumbnail(nullptr) {}
	// By values
	FItem(FName NewName, const FText& NewDescription, EItemType NewItemType, int32 NewMaxAmount, int32 NewCurrentAmount, float NewItemTimeToUseIt, const TObjectPtr<class UTexture2D>& NewAssetThumbnail) :
	Name(NewName),
    Description(NewDescription),
    ItemType(NewItemType),
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
			NewItem.ItemType = Source->ItemType;
			NewItem.MaxAmount = Source->MaxAmount;
			NewItem.CurrentAmount = Source->CurrentAmount;
			NewItem.ItemTimeToUseIt = Source->ItemTimeToUseIt;
			NewItem.AssetThumbnail = Source->AssetThumbnail;
		}
		return NewItem;
	}
};

