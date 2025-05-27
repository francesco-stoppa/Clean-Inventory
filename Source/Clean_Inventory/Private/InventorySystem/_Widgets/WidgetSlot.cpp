#include "InventorySystem/_Widgets/WidgetSlot.h"
#include "InventorySystem/ActorComponents/ManageInventory.h"
// #include "InventorySystem/ActorComponents/GenericInventory.h"
#include "Components/Image.h"

void UWidgetSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SlotClicked->SetVisibility(ESlateVisibility::Hidden);
	PlayerInventory = GetOwningPlayerPawn<APawn>() -> GetComponentByClass<UManageInventory>();

	if (bIsPlayer)
	{
		Inventory = PlayerInventory;
	}
	else
	{
		Inventory = PlayerInventory->GetCloseInventory();
	}
}


void UWidgetSlot::SelectSlots()
{
	if (PlayerInventory != nullptr && Inventory != nullptr)
	{
		SlotClicked->SetVisibility(ESlateVisibility::Visible);
		PlayerInventory->SelectSlot(Id, Inventory);
	}
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

