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
				i++;
				WidgetSlot->SetId(i);
				WidgetSlot->SetPlayerSlot(bIsPlayer);
				GridPanel->AddChildToUniformGrid(WidgetSlot, y, x);
				Slots.Add(WidgetSlot);
			}
		}
	}
	PlayerInventory->SetMaxItemNumber(i);
}

void UWidgetInventory::ShowInventory(bool bIsOpen)
{
	if (bIsOpen)
	{
		this->SetVisibility(ESlateVisibility::Visible);
		
		for (int32 n = 0; n < Slots.Num(); n++)
		{
			Slots[n]->RevertSelectedSlot();
		}
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Hidden);
	}
}

