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
		PlayerInventory->onLoadSlotDelegate.AddDynamic(this, &UWidgetInventory::LoadSlot);
	}
	CreateInventory();
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetInventory::CreateInventory()
{
	if (SlotClass != nullptr)
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
}

void UWidgetInventory::ShowInventory(bool bIsOpen)
{
	InvButtonUse++;
	if (bIsOpen)
	{
		Inventory = PlayerInventory->GetChestInventory();
		if (Inventory != nullptr)
		{
			bIsMoreInventoryOpen = true;
			
			if (!bIsPlayer)
			{
				Inventory->SetMaxItemNumber(SlotCreated);
			}
		}
		
		if (!bIsPlayer && Inventory == nullptr)
		{
			GridPanel->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			GridPanel->SetVisibility(ESlateVisibility::Visible);
		}

		LoadInventory(bIsPlayer);
		
		// Add vv
		CurrentId = 0;
		CursorOver(EDirections::Default, true);
	}
	else
	{
		for (int32 n = 0; n < Slots.Num(); n++)
		{
			Slots[n]->RevertSelectedSlot();
		}
		GridPanel->SetVisibility(ESlateVisibility::Hidden);
		Inventory = nullptr;
		bIsMoreInventoryOpen = false;
	}
}

void UWidgetInventory::LoadInventory(bool bIsPlayer_)
{
	this->SetVisibility(ESlateVisibility::Visible);
	for (int32 n = 0; n < Slots.Num(); n++)
	{
		if (!bIsPlayer_)
		{
			if (Inventory != nullptr)
			{
				Slots[n]->SetInventory(Inventory);
			}
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
			if (FirstInventory == PlayerInventory) // || SecondInventory == PlayerInventory)
			{
				Slots[FirstIdToLoad]->ShowSlot();
				// Slots[FirstIdToLoad]->RevertSelectedSlot();
			}
			if (SecondInventory == PlayerInventory)
			{
				Slots[SecondIdToLoad]->ShowSlot();
				Slots[SecondIdToLoad]->OverSlot();
				// Slots[SecondIdToLoad]->RevertSelectedSlot();
			}
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
				Slots[SecondIdToLoad]->OverSlot();
				// Slots[SecondIdToLoad]->RevertSelectedSlot();
			}
		}
	}
}

void UWidgetInventory::LoadSlot(int IdToLoad, UGenericInventory* InventoryToLoad, bool bIsSelection)
{
	if (InventoryToLoad != nullptr && PlayerInventory != nullptr)
	{
		if (bIsPlayer)
		{
			if (InventoryToLoad == PlayerInventory)
			{
				if (bIsSelection)
				{
					Slots[IdToLoad]->OverSlot(); // change from selection (TO TEST)
				}
				else
				{
					Slots[IdToLoad]->ShowSlot();
				}
			}
		}
		else
		{
			if (Inventory != nullptr)
			{
				if (InventoryToLoad == Inventory)
				{
					if (bIsSelection)
					{
						Slots[IdToLoad]->OverSlot(); // change from selection (TO TEST)
					}
					else
					{
						Slots[IdToLoad]->ShowSlot();
					}
				}
			}
		}
	}
}

// this is a case where there is only one inventary open and its is the main
void UWidgetInventory::CursorOver(EDirections Direction, bool test) // Not work with multiple inventory
{																	// Need to test the current id change with another way.
	if (GridPanel->GetVisibility() == ESlateVisibility::Hidden)
	{
		return;
	}
	
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
	
	int32 CheckColumn = MaxSlot - MaxColumn;

		
	switch (Direction)
	{
	case EDirections::Default:
		break;
	case EDirections::Enter:
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
		if (CurrentId > 0)
		{
			CurrentId--;
		}/*
		else
		{
			// effect on ui
		}*/
		break;
	case EDirections::Down:
		if (CurrentId <= CheckColumn)
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
		if (Direction == EDirections::Default)
		{
			if (CurrentId <= TempMaxSlot && !bIsPlayer)
			{
				Slots[CurrentId]->NotOverSlot();
			}
			if (CurrentId > TempMaxSlot && bIsPlayer)
			{
				CurrentId -= TempMaxSlot;
				Slots[CurrentId]->NotOverSlot();
			}
		}
		else if (Direction == EDirections::Enter)
		{
			if (CurrentId <= TempMaxSlot && !bIsPlayer)
			{
				Slots[CurrentId]->SelectSlot();
				Slots[CurrentId]->OverSlot();
			}

			if (CurrentId > TempMaxSlot && bIsPlayer)
			{
				CurrentId -= TempMaxSlot;
				Slots[CurrentId]->SelectSlot();
				Slots[CurrentId]->OverSlot();
			}
		}
		else
		{
			if (CurrentId <= TempMaxSlot && !bIsPlayer)
			{
				Slots[CurrentId]->OverSlot(); // select slot
				UE_LOG(LogTemp, Warning, TEXT("MultyInvChest Slot: %d"), CurrentId);
			}

			if (CurrentId > TempMaxSlot && bIsPlayer)
			{
				CurrentId -= TempMaxSlot;
				Slots[CurrentId]->OverSlot();
				UE_LOG(LogTemp, Warning, TEXT("MultyInvPlay Slot: %d"), CurrentId);
			}
		}

		if (test)
		{
			if (CurrentId <= TempMaxSlot && !bIsPlayer)
			{
				Slots[CurrentId]->OverSlot();
				UE_LOG(LogTemp, Warning, TEXT("MultyInvChest Slot: %d"), CurrentId);
			}

			if (CurrentId > TempMaxSlot && bIsPlayer)
			{
				CurrentId -= TempMaxSlot;
				Slots[CurrentId]->OverSlot();
				UE_LOG(LogTemp, Warning, TEXT("MultyInvPlay Slot: %d"), CurrentId);

			}
		}
	}
	else
	{
		if (Direction == EDirections::Default)
		{
			Slots[CurrentId]->NotOverSlot();
		}
		else if (Direction == EDirections::Enter)
		{
			Slots[CurrentId]->SelectSlot();
			Slots[CurrentId]->OverSlot();
		}
		else
		{
			Slots[CurrentId]->OverSlot();
		}

		if (test)
		{
			Slots[CurrentId]->OverSlot();
		}
	}
}


