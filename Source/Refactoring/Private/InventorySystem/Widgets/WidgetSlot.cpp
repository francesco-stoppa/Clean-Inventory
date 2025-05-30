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

	MissingAssetThumbnail = Cast<UTexture2D>(ItemImage->GetBrush().GetResourceObject()); 
}


void UWidgetSlot::OverSlot()
{
	if (PlayerInventory != nullptr && Inventory != nullptr)
	{
		SlotClicked->SetVisibility(ESlateVisibility::Visible);
		SlotClicked->SetRenderOpacity(0.45f);
	}
}

void UWidgetSlot::SelectSlot()
{
	if (PlayerInventory != nullptr && Inventory != nullptr)
	{
		SlotClicked->SetVisibility(ESlateVisibility::Visible);
		SlotClicked->SetRenderOpacity(0.6f);
		PlayerInventory->SelectSlot(Id, Inventory);
	}
}

void UWidgetSlot::RevertSelectedSlot()
{
	SlotClicked->SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetSlot::ShowSlot()
{
	AssetThumbnail = PlayerInventory->GetSlotTexture(Id, Inventory);
	
	if (AssetThumbnail == nullptr)
	{
		ItemImage->SetBrushFromTexture(MissingAssetThumbnail);
	}
	else
	{
		ItemImage->SetBrushFromTexture(AssetThumbnail);
	}
	
	SlotClicked->SetVisibility(ESlateVisibility::Hidden);
}

