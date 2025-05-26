#include "Clean_Inventory/Public/InventorySystem/ActorComponents/ManageInventory.h"
#include "Clean_Inventory/Public/InventorySystem/Structs/Item.h"

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
	if (ItemList.Num() == MaxItemNumber)
	{
		return false;
	}
	else
	{
		int32 Id = GetFirstEmptyId();
		if (Id > 0)
		{
			ItemList[Id] = ItemToAdd;
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}


