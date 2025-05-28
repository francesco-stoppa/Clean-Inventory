#include "InventorySystem/Widgets/WidgetSlot.h"
#include "Components/Button.h"
#include "InventorySystem/ActorComponents/ManageInventory.h"
#include "Components/Image.h"
#include "Refactoring/RefactoringCharacter.h"

void UWidgetSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SlotClicked->SetVisibility(ESlateVisibility::Hidden);
	PlayerInventory = GetOwningPlayerPawn<ARefactoringCharacter>()->GetComponentByClass<UManageInventory>();

	if (PlayerInventory != nullptr)
	{
		SlotButton->OnClicked.AddUniqueDynamic(this, &ThisClass::SelectSlot);

		if (bIsPlayer)
		{
			Inventory = PlayerInventory;
		}
		else
		{
			Inventory = PlayerInventory->GetChestInventory();
		}
	}
}


void UWidgetSlot::SelectSlot()
{
	if (PlayerInventory != nullptr && Inventory != nullptr)
	{
		SlotClicked->SetVisibility(ESlateVisibility::Visible);
		PlayerInventory->SelectSlot(Id, Inventory);
	}
}

void UWidgetSlot::RevertSelectedSlot()
{
	SlotClicked->SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetSlot::ShowSlot()
{
	if (AssetThumbnail != PlayerInventory->GetSlotTexture(Id, Inventory))
	{
		AssetThumbnail = PlayerInventory->GetSlotTexture(Id, Inventory);
	}

	ItemImage->SetBrushFromTexture(AssetThumbnail);
	
	if (AssetThumbnail == nullptr)
	{
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ItemImage->SetVisibility(ESlateVisibility::Visible);
	}
}

