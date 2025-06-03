#include "InventorySystem/Widgets/WidgetInventory.h"
#include "InventorySystem/ActorComponents/ManageInventory.h"
#include "Refactoring/RefactoringCharacter.h"
#include "InventorySystem/Enum/EnumList.h"


void UWidgetInventory::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerInventory = GetOwningPlayerPawn<ARefactoringCharacter>()->GetComponentByClass<UManageInventory>();
	if (PlayerInventory)
	{
		PlayerInventory->onOpenInventoryDelegate.AddDynamic(this, &UWidgetInventory::ShowInventory);
		PlayerInventory->onSwitchSlotsInventoryDelegate.AddDynamic(this, &UWidgetInventory::SwitchSlot);
		PlayerInventory->onSLoadSlotDelegate.AddDynamic(this, &UWidgetInventory::LoadSlot);
		CreateInventory();
	}
	
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetInventory::CreateInventory()
{
	UWidgetSlot* WidgetSlot = nullptr;
	for (int32 y = 0; y < GridRow; y++)
	{
		for (int32 x = 0; x < GridColumn; x++)
		{
			WidgetSlot = CreateWidget<UWidgetSlot>(this, SlotClass);
			if (WidgetSlot)
			{
				SlotCreated++;
				WidgetSlot->SetId(SlotCreated);
				WidgetSlot->SetPlayerSlot(bIsPlayer);
				GridPanel->AddChildToUniformGrid(WidgetSlot, y, x);
				Slots.Add(WidgetSlot);
			}
		}
	}
	
	if (bIsPlayer)
	{
		PlayerInventory->SetMaxItemNumber(SlotCreated);
	}
}

void UWidgetInventory::ShowInventory(bool bIsOpen)
{
	if (bIsOpen)
	{
		if (bIsPlayer)
		{
			LoadInventory();
			Inventory = PlayerInventory->GetChestInventory();
			if (Inventory != nullptr)
			{
				bIsMoreInventoryOpen = true;
			}
		}
		else
		{
			Inventory = PlayerInventory->GetChestInventory();
			if (Inventory != nullptr)
			{
				if (Inventory->GetColumn() == 0)
				{
					Inventory->SetCoulmn(GridColumn);
				}
				LoadInventory(true);
			}
		}
	}
	else
	{
		for (int32 n = 0; n < Slots.Num(); n++)
		{
			Slots[n]->RevertSelectedSlot();
		}
		this->SetVisibility(ESlateVisibility::Hidden);
		Inventory = nullptr;
	}
}

void UWidgetInventory::LoadInventory(bool bIsChest)
{
	this->SetVisibility(ESlateVisibility::Visible);
	for (int32 n = 0; n < Slots.Num(); n++)
	{
		if (bIsChest)
		{
			Slots[n]->SetInventory(Inventory);
		}
		Slots[n]->ShowSlot();
	}
}

void UWidgetInventory::SwitchSlot(int FirstIdToLoad, UGenericInventory* FirstInventory, int SecondIdToLoad, UGenericInventory* SecondInventory)
{
	if (FirstInventory != nullptr && SecondInventory != nullptr && PlayerInventory != nullptr)
	{
		if (bIsPlayer)
		{
			if (FirstInventory == PlayerInventory || SecondInventory == PlayerInventory)
			{
				Slots[FirstIdToLoad]->ShowSlot();
				// Slots[FirstIdToLoad]->RevertSelectedSlot();
			}/*
			if (SecondInventory == PlayerInventory)
			{
				Slots[SecondIdToLoad]->ShowSlot();
				// Slots[SecondIdToLoad]->RevertSelectedSlot();
			}*/
		}
		else
		{
			if (FirstInventory == Inventory)
			{
				Slots[FirstIdToLoad]->ShowSlot();
				// Slots[FirstIdToLoad]->RevertSelectedSlot();
			}
			if (SecondInventory == Inventory)
			{
				Slots[SecondIdToLoad]->ShowSlot();
				// Slots[SecondIdToLoad]->RevertSelectedSlot();
			}
		}
	}
}

void UWidgetInventory::LoadSlot(int IdToLoad, UGenericInventory* InventoryToLoad)
{
	if (InventoryToLoad != nullptr && PlayerInventory != nullptr)
	{
		if (bIsPlayer)
		{
			if (InventoryToLoad == PlayerInventory)
			{
				Slots[IdToLoad]->ShowSlot();
				CurrentId = 0;
				CursorOver(EDirections::Default);
			}
		}
		else
		{
			if (InventoryToLoad == Inventory)
			{
				Slots[IdToLoad]->ShowSlot();
			}
		}
	}
}

// this is a case where there is only one inventary open and its is the main
void UWidgetInventory::CursorOver(EDirections Direction) // TO TEST vv 
{
	/* // Old
		switch (direction)
		{
		case EEnumList::Default:
			break;
		case EEnumList::Right:
			if (CurrentId < SlotCreated) // mi pare (<< questo o SlotCreated - 1)
			{
				CurrentId++;
			}
		break;
		case EEnumList::Left:
			if (CurrentId < 0)
			{
				CurrentId--;
			}
		break;
		case EEnumList::Down:
		if (CurrentId <= SlotCreated)
		{
			CurrentId += GridColumn;
		}
		break;
		case EEnumList::Up:
			if (CurrentId >= GridColumn)
			{
				CurrentId -= GridColumn;
			}
		break;
		}
		*/
	int32 MaxSlot = SlotCreated;
	int32 MaxColumn = GridColumn;
	int32 TempMaxSlot = 0;
		
	if (bIsMoreInventoryOpen && Inventory != nullptr)
	{
		TempMaxSlot = Inventory->GetMaxItemNumber();
		if (CurrentId <= TempMaxSlot)
		{
			MaxColumn = Inventory->GetColumn();
		}
		MaxSlot += TempMaxSlot + 1;
	}
		
	switch (Direction)
	{
	case EDirections::Default:
		break;
	case EDirections::Right:
		if (CurrentId < MaxSlot) 
		{
			CurrentId++;
		}/*
		else
		{
			// effect on ui
		}*/
		break;
	case EDirections::Left:
		if (CurrentId < 0)
		{
			CurrentId--;
		}/*
		else
		{
			// effect on ui
		}*/
		break;
	case EDirections::Down:
		if (CurrentId <= MaxSlot)
		{
			CurrentId += MaxColumn;
		}/*
		else
		{
			// effect on ui
		}*/
		break;
	case EDirections::Up:
		if (CurrentId >= MaxColumn)
		{
			CurrentId -= MaxColumn;
		}/*
		else
		{
			// effect on ui
		}*/
		break;
	}

	if (bIsMoreInventoryOpen)
	{
		if (CurrentId <= TempMaxSlot && !bIsPlayer)
		{
			Slots[CurrentId]->OverSlot();
		}

		if (CurrentId > TempMaxSlot && bIsPlayer)
		{
			CurrentId -= TempMaxSlot;
			Slots[CurrentId]->OverSlot();
		}
	}
	else
	{
		Slots[CurrentId]->OverSlot();
	}
}


