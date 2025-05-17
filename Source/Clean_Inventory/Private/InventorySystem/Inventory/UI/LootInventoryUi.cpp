#include "InventorySystem/Inventory/UI/LootInventoryUi.h"
#include "CharacterLogic/PlayerCharacter.h"
#include "Components/Button.h"
#include "InventorySystem/Inventory/ManageInventorySlots.h"

/*
WHAT IT DOES:
1. Search the player and its UComponents to bind the events.
	a) Otherwise it gives errors. */
void ULootInventoryUi::NativeConstruct()
{
	Super::NativeConstruct();
		// 1.
	inventoryManager = GetOwningPlayerPawn<APlayerCharacter>() -> GetComponentByClass<UManageInventorySlots>();
	if (inventoryManager)
	{
		inventoryManager->onChangeInventoryUiDelegate.AddDynamic(this, &ULootInventoryUi::ShowInventory);
		if (takeButton)
			takeButton->OnClicked.AddDynamic(this, &ULootInventoryUi::TakeAllSlots);
		else
			UE_LOG(LogTemp, Warning, TEXT("Error: <TakeButton> is missing..."));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Error: <UManageInventorySlots> is missing..."));
}

/*
WHAT IT DOES:
1. On click <takeButton> call the function AddAllItems() from the script UInventoryManage. */
void ULootInventoryUi::TakeAllSlots()
{	// 1.
	if (!GetWorld()->GetTimerManager().IsTimerActive(inventoryManager->GetMyTimerHandle()))
		inventoryManager->AddAllItems();
}

/*
WHAT IT NEEDS:
- A bool.
WHAT IT DOES:
1. Chek if the enemy inventory is open (or exists).
	a) if is open load the UI and set its visibility (to true).
NOTE:
- This function is automatichally call by the event OpenInventory(). */
void ULootInventoryUi::ShowInventory(bool isOpen)
{	// 1.
	if (isOpen && inventoryManager->GetEnemyInventory() != nullptr)
	{
		inventoryManager->GetEnemyInventory()->EventStart();
		this->SetVisibility(ESlateVisibility::Visible);
	}
	else
		this->SetVisibility(ESlateVisibility::Hidden);
}


