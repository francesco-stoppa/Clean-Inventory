#include "InventorySystem/_Widgets/WidgetInventory.h"
#include "InventorySystem/ActorComponents/ManageInventory.h"

void UWidgetInventory::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerInventory = GetOwningPlayerPawn<APawn>()->GetComponentByClass<UManageInventory>();

	// creazione della griglia
}

void UWidgetInventory::ShowInventory(bool isOpen)
{
	if (isOpen)
		this->SetVisibility(ESlateVisibility::Visible);
	else
		this->SetVisibility(ESlateVisibility::Hidden);
}
