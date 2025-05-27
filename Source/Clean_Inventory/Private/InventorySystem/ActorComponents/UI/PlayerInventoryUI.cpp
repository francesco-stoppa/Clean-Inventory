#include "InventorySystem/ActorComponents/UI/PlayerInventoryUI.h"
//#include "CharacterLogic/PlayerCharacter.h"
#include "Components/Button.h"
#include "InventorySystem/ActorComponents/ManageInventorySlots.h"

/*
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

void UPlayerInventoryUI::SortSlots()
{	// 1.
	if (!GetWorld()->GetTimerManager().IsTimerActive(inventoryManager->GetMyTimerHandle()))
		inventoryManager->PlayTimerSort();
}

void UPlayerInventoryUI::ShowInventory(bool isOpen)
{
	if (isOpen)
		this->SetVisibility(ESlateVisibility::Visible);
	else
		this->SetVisibility(ESlateVisibility::Hidden);
}*/

