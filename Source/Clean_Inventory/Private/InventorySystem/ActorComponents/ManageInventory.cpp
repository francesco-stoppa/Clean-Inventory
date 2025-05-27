#include "InventorySystem/ActorComponents/ManageInventory.h"
#include "InventorySystem/Structs/Item.h"

void UManageInventory::SelectSlot(int32 Id, TWeakObjectPtr<UGenericInventory> Inventory)
{
	if (Inventory != nullptr)
	{
		return;
	}
	FSlotSelected NewSelection = FSlotSelected(Id, Inventory);
	if (Selection.Inventory == nullptr)
	{
		Selection = NewSelection;
	}
	else
	{
		if (Selection.Inventory == Inventory && Selection.Id == Id)
		{
			RevertSelection();
		}
		else
		{
			SwitchSlot(Selection, NewSelection);
		}
	}
}

void UManageInventory::SwitchSlot(FSlotSelected FirstSelection, FSlotSelected SecondCoordinates)
{
	FItem SecondItem = SecondCoordinates.Inventory->GetItem(SecondCoordinates.Id);
	SecondCoordinates.Inventory->SetItem(SecondCoordinates.Id, FirstSelection.Inventory->GetItem(FirstSelection.Id));
	FirstSelection.Inventory->SetItem(FirstSelection.Id, SecondItem);
}

void UManageInventory::UseSlot()
{
	if (Selection.Inventory == nullptr)
	{
		return;
	}
	
	if (Selection.Inventory == this) // use obj only in your inv
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Used"));
		Selection.Inventory->SetItem(Selection.Id, FItem());
	}
}

bool UManageInventory::AddItem(FItem ItemToAdd)
{
	bool bToReturn = false;
	if (ItemList.Num() != MaxItemNumber)
	{
		int32 Id = GetFirstEmptyId();
		if (Id > 0)
		{
			ItemList[Id] = ItemToAdd;
			bToReturn =  true;
		}
	}
	return bToReturn;
}

UTexture2D* UManageInventory::GetSlotTexture(int32 Id, TWeakObjectPtr<UGenericInventory> Inventory)
{
	UTexture2D* TextureToReturn = nullptr;
	if (Inventory != nullptr)
	{
		FItem Item = Inventory->GetItem(Id);
		//if (Item.ItemType == EItemType::Empty)
		//{
			TextureToReturn = Item.AssetThumbnail;
		//}
	}
	return TextureToReturn;
}


