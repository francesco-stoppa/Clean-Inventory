#include "Clean_Inventory/Public/InventorySystem/ActorComponents/UI/PlayerInventoryUI.h"
#include "CharacterLogic/PlayerCharacter.h"
#include "Components/Button.h"
#include "Clean_Inventory/Public/InventorySystem/ActorComponents/ManageInventorySlots.h"

/*
WHAT IT DOES:
1. Search the player and its UComponents to bind the events.
	a) Otherwise it gives errors. */
void UPlayerInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();
	// 1.
	inventoryManager = GetOwningPlayerPawn<APlayerCharacter>()->GetComponentByClass<UManageInventorySlots>();
	if (inventoryManager)
	{
		inventoryManager->onChangeInventoryUiDelegate.AddDynamic(this, &UPlayerInventoryUI::ShowInventory);
		if (sortButton)
			sortButton->OnClicked.AddDynamic(this, &UPlayerInventoryUI::SortSlots);
		else
			UE_LOG(LogTemp, Warning, TEXT("Error: <SortButton> is missing..."));
	}
	else
			UE_LOG(LogTemp, Warning, TEXT("Error: <UManageInventorySlots> is missing..."));
}

/*
WHAT IT DOES:
1. On click <sortButton> call the function Sort() from the script UInventoryManage. */
void UPlayerInventoryUI::SortSlots()
{	// 1.
	if (!GetWorld()->GetTimerManager().IsTimerActive(inventoryManager->GetMyTimerHandle()))
		inventoryManager->PlayTimerSort();
}

/*
WHAT IT NEEDS:
- A bool.
WHAT IT DOES:
1. Chek if the enemy inventory is open.
	a) if is open load the UI and set its visibility (to true).
NOTE:
- This function is automatichally call by the event OpenInventory(). */
void UPlayerInventoryUI::ShowInventory(bool isOpen)
{
	if (isOpen)
		this->SetVisibility(ESlateVisibility::Visible);
	else
		this->SetVisibility(ESlateVisibility::Hidden);
}

