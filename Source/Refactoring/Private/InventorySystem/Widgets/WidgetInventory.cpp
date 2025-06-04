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
	if (bIsOpen)
	{
		Inventory = PlayerInventory->GetChestInventory();
		if (Inventory != nullptr)
		{
			bIsMoreInventoryOpen = true;
			
			if (!bIsPlayer)
				Inventory->SetMaxItemNumber(SlotCreated);
		}
		LoadInventory(bIsPlayer);

		
		// Add vv
		CurrentId = 0;
		// CursorOver(EDirections::Default);
	}
	else
	{
		for (int32 n = 0; n < Slots.Num(); n++)
		{
			Slots[n]->RevertSelectedSlot();
		}
		this->SetVisibility(ESlateVisibility::Hidden);
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

	if (this->GetVisibility() == ESlateVisibility::Hidden)
		return;
	
	if (CurrentId >= 0) // check for missing referance
		Slots[CurrentId]->NotOverSlot();
	
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
		/* // the fuck vv
		if (BeforeId <= TempMaxSlot && !bIsPlayer)
		{// chek if BeforeId exist
			Slots[BeforeId]->NotOverSlot();
		}

		if (BeforeId > TempMaxSlot && bIsPlayer)
		{// chek if BeforeId exist
			BeforeId -= TempMaxSlot;
			Slots[BeforeId]->NotOverSlot();
		}*/ // the fuck ^^

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


