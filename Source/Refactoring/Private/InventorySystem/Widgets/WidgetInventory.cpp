#include "InventorySystem/Widgets/WidgetInventory.h"
#include "InventorySystem/ActorComponents/ManageInventory.h"
#include "Refactoring/RefactoringCharacter.h"


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
		for (int32 x =0; x < GridColumn; x++)
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
		}
		else
		{
			Inventory = PlayerInventory->GetChestInventory();
			if (Inventory != nullptr)
			{
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

