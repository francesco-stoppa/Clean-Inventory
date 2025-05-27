#include "InventorySystem/ActorComponents/UI/GarbageSlotUi.h"
//#include "CharacterLogic/PlayerCharacter.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "InventorySystem/ActorComponents/ManageInventorySlots.h"
/*
void UGarbageSlotUi::NativeConstruct()
{
	Super::NativeConstruct();
	
	inventoryManager = GetOwningPlayerPawn<APlayerCharacter>()->GetComponentByClass<UManageInventorySlots>();
	if (inventoryManager)
	{
		inventoryManager->onTooltipUpdateDelegate.AddDynamic(this, &UGarbageSlotUi::OnSelectSlot);
		if (slotButton)
			slotButton->OnClicked.AddDynamic(this, &UGarbageSlotUi::DeleteSlot);
		else
			UE_LOG(LogTemp, Warning, TEXT("Error: <X> is missing..."));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Error: <UManageInventorySlots> is missing..."));

	// selection->SetVisibility(ESlateVisibility::Hidden);
}

void UGarbageSlotUi::DeleteSlot()
{
	if (inventoryManager)
		invetoryManager->RemoveItem();
}

void UGarbageSlotUi::OnSelectionChanged(bool selectOneSlot)
{/*
	if (!selectOneSlot)
		selection->SetVisibility(ESlateVisibility::Hidden);
	else
		selection->SetVisibility(ESlateVisibility::visible);*/ // occhio che "visible"

//}

