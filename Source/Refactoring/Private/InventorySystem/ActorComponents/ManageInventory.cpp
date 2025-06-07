#include "InventorySystem/ActorComponents/ManageInventory.h"

#include "InventorySystem/Enum/EnumList.h"
#include "InventorySystem/Items/ItemInfo.h"

// Bug = de switch Selection TO TEST (is on WIdgetInventory->SwitchSlot())
// Pick up system = prendere tutti gli oggetti che entrano nel trigger salvarseli in una lista e poi al momento dell'interazione calcolare tutti gli oggetti e calcolare il più vicino (sarebbe meglio l'oggeto nella giusta distanza e angolazione) poi interagisci con quello.

void UManageInventory::BeginPlay()
{
	Super::BeginPlay();

	bIsPlayer = true;
}

void UManageInventory::SelectSlot(int32 Id, UGenericInventory* Inventory)
{
	if (Inventory == nullptr)
	{
		return;
	}
	
	FSlotSelected NewSelection = FSlotSelected(Id, Inventory);
	if (Selection.Inventory == nullptr)
	{
		Selection = NewSelection;
		onLoadSlotDelegate.Broadcast(Id, Inventory, true);
		onCommandDelegate.Broadcast(ECommandStats::Switch);  
	}
	else
	{
		if (Selection.Inventory == Inventory && Selection.Id == Id)
		{
			// ReadItemInfo();// presss Y
			// selection 
			// RevertSelection();
			//ReadItemInfo(); //info press Y
			//TempSelection(Id, Inventory);
		}
		else
		{
			SwitchSlot(Selection, NewSelection);
			RevertSelection(false);
			// SelectSlot(Id, Inventory); // Sarebbe meglio dire: "OnMouseOver();"
		}
	}
}

void UManageInventory::RevertSelection(bool LoadUI)
{
	if (LoadUI)
	{
		onLoadSlotDelegate.Broadcast(Selection.Id, Selection.Inventory, false);
	}
	onCommandDelegate.Broadcast(ECommandStats::Inventory);
	Selection = FSlotSelected();
}

void UManageInventory::SwitchSlot(FSlotSelected FirstSelection, FSlotSelected SecondCoordinates)
{
	UItemInfo* SecondItem = SecondCoordinates.Inventory->GetItem(SecondCoordinates.Id);
	SecondCoordinates.Inventory->SetItem(SecondCoordinates.Id, FirstSelection.Inventory->GetItem(FirstSelection.Id));
	FirstSelection.Inventory->SetItem(FirstSelection.Id, SecondItem);
	
	onSwitchSlotsInventoryDelegate.Broadcast(FirstSelection.Id, FirstSelection.Inventory,SecondCoordinates.Id, SecondCoordinates.Inventory);
	onCommandDelegate.Broadcast(ECommandStats::Inventory);
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
		DropSlot(); // for now
	}
}

void UManageInventory::DropSlot()
{
	if (Selection.Inventory == nullptr)
	{
		RevertSelection();
		return;
	}

	if (Selection.Inventory == this) // puoi droppare solo oggetti dal tuo inventario
	{
		SetItem(Selection.Id, nullptr);
	}
	RevertSelection();
}

bool UManageInventory::AddItem(UItemInfo* ItemToAdd)
{
	bool bToReturn = false;
	if (ItemList.Num() != MaxItemNumber)
	{
		int32 Id = GetFirstEmptyId();
		if (Id > 0)
		{
			ItemList[Id] = ItemToAdd;
			bToReturn = true;
		}
	}
	return bToReturn;
}

UTexture2D* UManageInventory::GetSlotTexture(int32 Id, UGenericInventory* Inventory) const
{
	UTexture2D* TextureToReturn = nullptr;
	if (Inventory != nullptr)
	{
		UItemInfo* Item = Inventory->GetItem(Id);
		if (Item)
		{
			TextureToReturn = Item->AssetThumbnail;
		}
	}
	return TextureToReturn;
}

void UManageInventory::SetChestInventory(UGenericInventory* NewChestInventory)
{
	ChestInventory = NewChestInventory;
	if (NewChestInventory != nullptr)
	{
		onCommandDelegate.Broadcast(ECommandStats::Chest);
	}
	else
	{
		onCommandDelegate.Broadcast(ECommandStats::Game);
	}
}

bool UManageInventory::ShowInventory()
{
	if (bIsInventoryOpen)
	{
		bIsInventoryOpen = false;
		if (ChestInventory != nullptr)
		{
			ChestInventory = nullptr;
		}
		RevertSelection();
		onCommandDelegate.Broadcast(ECommandStats::Game);
	}
	else
	{
		bIsInventoryOpen = true;
		onCommandDelegate.Broadcast(ECommandStats::Inventory);
	}
	onOpenInventoryDelegate.Broadcast(bIsInventoryOpen);
	/*
	if (bIsInventoryOpen)
	{
		if (ChestInventory != nullptr)
		{
			SelectSlot(0, ChestInventory);
		}
		else
		{
			SelectSlot(0, this);
		}
	}*/
	return bIsInventoryOpen;
}

void UManageInventory::ReadItemInfo()
{
	if (Selection.Inventory == nullptr)
		return;
	
	UItemInfo* Item = GetItem(Selection.Id);
	if (Item != nullptr)
	{
		FName ItemName = Item->Name;
		FText ItemDescription = Item->Description;
		onItemInfoDelegate.Broadcast(ItemName, ItemDescription);
	}
	onCommandDelegate.Broadcast(ECommandStats::Info);
}
