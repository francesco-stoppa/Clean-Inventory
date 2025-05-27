#include "InventorySystem/ActorComponents/UI/LootInventoryUi.h"
//#include "CharacterLogic/PlayerCharacter.h"
#include "Components/Button.h"
#include "InventorySystem/ActorComponents/ManageInventorySlots.h"

/*
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

void ULootInventoryUi::TakeAllSlots()
{	// 1.
	if (!GetWorld()->GetTimerManager().IsTimerActive(inventoryManager->GetMyTimerHandle()))
		inventoryManager->AddAllItems();
}


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
*/

