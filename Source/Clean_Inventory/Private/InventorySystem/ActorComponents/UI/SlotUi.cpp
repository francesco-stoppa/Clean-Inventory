#include "InventorySystem/ActorComponents/UI/SlotUi.h"
//#include "CharacterLogic/PlayerCharacter.h"
/*#include "Components/Button.h"
#include "Components/Image.h"
#include "Runtime/AdvancedWidgets/Public/Components/RadialSlider.h"
#include "Components/TextBlock.h"
#include "Clean_Inventory/Public/InventorySystem/ActorComponents/ManageInventorySlots.h"*/

/*

void USlotUi::NativeConstruct()
{
	Super::NativeConstruct();

	// Per ora setto l'empty texture basato da quello che vede il giocatore allo start.
	emptyTexture2D = Cast<UTexture2D>(quickSlotImage->GetBrush().GetResourceObject());
	// 1.
	if (isPlayer)
	{
		inventory = GetOwningPlayerPawn<APlayerCharacter>() -> GetComponentByClass<UInventoryBase>();
		if (inventory)
			inventory->onSortUiDelegate.AddDynamic(this, &USlotUi::OnSortSlots);
		else
			UE_LOG(LogTemp, Warning, TEXT("Error: <UInventoryBase> is missing..."));
	}
	// 2.
	inventoryManager = GetOwningPlayerPawn<APlayerCharacter>() -> GetComponentByClass<UManageInventorySlots>();
	if (inventoryManager)
	{
		inventoryManager->onChangeSlotUiDelegate.AddDynamic(this, &USlotUi::OnSlotChanged);
		inventoryManager->onChangeInventoryUiDelegate.AddDynamic(this, &USlotUi::OnSortSlots);
		inventoryManager->onMoveSlotUiDelegate.AddDynamic(this, &USlotUi::LoadEmptySlot);
		if (slotButton)
		{
			slotButton->OnClicked.AddDynamic(this, &USlotUi::SelectSlots);
			slotButton->OnPressed.AddDynamic(this, &USlotUi::OnButtonPressed);
			slotButton->OnReleased.AddDynamic(this, &USlotUi::OnButtonReleased);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Error: <SlotButton> is missing..."));
	}
else
	UE_LOG(LogTemp, Warning, TEXT("Error: <UManageInventorySlots> is missing..."));
// 3.
selection->SetVisibility(ESlateVisibility::Hidden);

// timer
timerSlider->SetVisibility(ESlateVisibility::Hidden);
}

void USlotUi::SelectSlots()
{	// 1.
	if (inventoryManager->GetInventoryOpen())
		// 2.
			if (!timerSliderReduction && !GetWorld()->GetTimerManager().IsTimerActive(inventoryManager->GetMyTimerHandle()))
			{
				selection->SetVisibility(ESlateVisibility::Visible);
				inventoryManager->SelectSlot(id, inventory);	
			}
}

void USlotUi::ShowSlot()
{
	if (isPlayer)
	{			// 1.
		if (inventory->inventory.Num() >= id)
		{
			if (inventory->inventory[id].amount <= 0)
			{
				quickSlotImage->SetBrushFromTexture(emptyTexture2D);
				quickSlotAmount->SetText(FText::FromString("x0"));
			}
			else 
			{	// 2.
				if (inventory->GetItem(id) != nullptr)
					if (inventory->GetItem(id)->assetThumbnail != nullptr)
						quickSlotImage->SetBrushFromTexture(inventory->GetItem(id)->assetThumbnail);
				
				quickSlotAmount->SetText(FText::Format(FText::FromString("{0}{1}"),
					FText::FromString("x"), FText::AsNumber(inventory->inventory[id].amount)));
			}
				// 3.
			selection->SetVisibility(ESlateVisibility::Hidden);
			timerSlider->SetVisibility(ESlateVisibility::Hidden);
			timerSliderReduction = false;
		}
	}
	else
	{
		inventory = inventoryManager->GetEnemyInventory();
		if (inventory != nullptr)
			if (inventory->inventory.Num() >= id)
			{
				if (inventory->inventory[id].amount <= 0)
				{
					quickSlotImage->SetBrushFromTexture(emptyTexture2D);
					quickSlotAmount->SetText(FText::FromString("x0"));
				}
				else 
				{	// 2.
					quickSlotImage->SetBrushFromTexture(inventory->GetItem(id)->assetThumbnail);
					quickSlotAmount->SetText(FText::Format(FText::FromString("{0}{1}"),
						FText::FromString("x"), FText::AsNumber(inventory->inventory[id].amount)));
				}
				// 3.
				selection->SetVisibility(ESlateVisibility::Hidden);
				
				selection->SetVisibility(ESlateVisibility::Hidden);
				timerSlider->SetVisibility(ESlateVisibility::Hidden);
				timerSliderReduction = false;
			}
		else
			UE_LOG(LogTemp, Warning, TEXT("Error: <UInventoryBase>(enemy) is missing..."));
	}
}

// the check i need to update the right slot
void USlotUi::OnSlotChanged(int slotId, UInventoryBase* inv, bool isMovingTheItem, bool isSwitching)
{
	if (id == slotId && inventory == inv)
	{
		if (!isMovingTheItem)
			ShowSlot();
		else
			PlayTimerSlider(isMovingTheItem, isSwitching);
	}
}

void USlotUi::OnLeftClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Left Mouse Button Clicked!"));
}

void USlotUi::OnRightClick()
{
	if (!timerSliderReduction && inventoryManager->GetInventoryOpen())
	{
		UE_LOG(LogTemp, Warning, TEXT("Right Mouse Button Clicked!"));
		// PlayTimerSlider(true);
	}
}

FReply USlotUi::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// ToolTipWidget
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		OnLeftClick(); 
		return FReply::Handled();
	}
	else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		OnRightClick();  
		return FReply::Handled(); 
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}


FText USlotUi::GetDescriptionText() 
{
	FText errorText;
	UInventoryBase* inv = inventory;
	if (!isPlayer)
		inv = inventoryManager->GetEnemyInventory();
	
	if (inv->GetItem(id) != nullptr)
	{
		UItemInfo* item = inv->GetItem(id);
		return inventory->GetItem(id)->description;
	}
	else
	{
		errorText = FText::FromString("Tooltip missing..");
	}
	return errorText;
}

void USlotUi::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	
	if (timerSliderReduction && timerSlider->GetValue() > 0.000001f)
	{
		timerSliderElapsed += DeltaTime;
        
		float currentShieldBarPercent = FMath::Lerp(1, 0.000001f, timerSliderElapsed / timerSliderDuration);

		if (currentShieldBarPercent <= 0.000001f)
			OnTimerEnd();
		else
			timerSlider->SetValue(currentShieldBarPercent);
	}
}

void USlotUi::PlayTimerSlider(bool isMovingTheItem, bool isSwitching)
{
	float timerMod = 1.0f;
	if (inventoryManager)
	{
		if (!isMovingTheItem)
		{
			inventoryManager->RevertSelection();
			SelectSlots();
			inventoryManager->PlayTimerUseItem();
		}
		timerMod = inventoryManager->GetInventoryTimesMultiplier();
	}
	
	timerSlider->SetVisibility(ESlateVisibility::Visible);
	timerSlider->SetValue(1.0f);
	timerSliderElapsed = 0;
	timerSliderDuration = 0.0f;

	if (!isMovingTheItem)
	{
		if (inventory->GetItem(id) != nullptr)
			timerSliderDuration = inventory->GetItem(id)->useItemTime * timerMod;
		else
			UE_LOG(LogTemp, Warning, TEXT("<timerSliderDuration> missing"));
	}
	else
	{
		if (inventory->GetItem(id) != nullptr)
			timerSliderDuration = inventory->GetItem(id)->moveItemTime * timerMod;
		else
			UE_LOG(LogTemp, Warning, TEXT("<timerSliderDuration> missing"));
	}

	if (isSwitching && inventoryManager)
		timerSliderDuration = inventoryManager->GetSwitchItemTimer();
	
	if (timerSliderDuration > 0)					
		timerSliderDecayRate = (1 - 0.000001f) / timerSliderDuration;
	else
		timerSliderDecayRate = 0;
	timerSliderReduction = true;
}

void USlotUi::OnTimerEnd()
{
	timerSlider->SetVisibility(ESlateVisibility::Hidden);
	timerSliderReduction = false;
}




void USlotUi::OnButtonPressed()
{
	if (inventoryManager->GetInventoryOpen())
	{
		pressing = true;

		GetWorld()->GetTimerManager().SetTimer(HoldTimerHandle, this, &USlotUi::CheckHoldDuration, 0.1f, true);
	}	
}

void USlotUi::OnButtonReleased()
{
	if (inventoryManager->GetInventoryOpen())
	{
		pressing = false;
		GetWorld()->GetTimerManager().ClearTimer(HoldTimerHandle);
		timerSlider->SetVisibility(ESlateVisibility::Hidden);
		timerSliderReduction = false;
		inventoryManager->StopAllTimer();
		selection->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USlotUi::CheckHoldDuration()
{
	if (pressing)
	{
		if (!inventoryManager->GetInventoryOpen())
			OnButtonReleased();
		
		currentHoldTime += 0.1f;

		if (currentHoldTime >= holdingTime)
		{
			PlayTimerSlider(false,false);
			currentHoldTime = 0.0f;
			pressing = false; 
		}
	}
}

void USlotUi::LoadEmptySlot(int slotToLoad)
{
	if (slotToLoad == -1)
		slot = slotToLoad;
	else
		slot++;

	if (slot == id && !isPlayer)
	{
		inventory = inventoryManager->GetEnemyInventory();
		if (inventory != nullptr)
		{
			if (inventory->inventory.Num() >= id)
			{
				quickSlotImage->SetBrushFromTexture(emptyTexture2D);
				quickSlotAmount->SetText(FText::FromString("x0"));
					
				selection->SetVisibility(ESlateVisibility::Hidden);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("Error: <UInventoryBase>(enemy) is missing..."));
		}		
	}
}

void USlotUi::MouseOver()
{
	if (!inventoryManager)
		return;
	if (!inventoryManager->GetInventoryOpen())
		return;
	if (!isPlayer)
		inventory = inventoryManager->GetEnemyInventory();

	inventoryManager->MouseOver(inventory, id);
}*/

