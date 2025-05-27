#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/Items/Structs/SloSelected.h"
#include "Components/ActorComponent.h"
#include "ManageInventorySlots.generated.h"
/*
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSlotUpdateSignature, int, slotId, UInventoryBase*, slotInventory, bool, isMovingTheItem, bool, isSwitching);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOpenCloseInventorySignature, bool, inventoryIsOpen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMoveSlotSignature, int, slotToLoad);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSlotUsedSignature, UItemInfo*, itemUsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTooltipUpdateSignature, UInventoryBase*, inventory, int, index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSelectSlotSignature, bool, selectOneSlot);
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLEAN_INVENTORY_API UManageInventorySlots : public UActorComponent
{
	GENERATED_BODY()

public:/*
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FSlotUpdateSignature onChangeSlotUiDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOpenCloseInventorySignature onChangeInventoryUiDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FMoveSlotSignature onMoveSlotUiDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FSlotUsedSignature onItemUsed;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FSelectSlotSignature onSelecSlot;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FTooltipUpdateSignature onTooltipUpdateDelegate;*/
protected:
private:
	// Timer variables
	FTimerHandle MyTimerHandle;
	/*
	UPROPERTY(EditAnywhere, Category = "Inventory",  meta = (UIMin = 0.01f))
	float switchItemTimer =0.01f;
	UPROPERTY(EditAnywhere, Category = "Inventory",  meta = (UIMin = 0))
	float sortInventoryTimer;*/

private:
	// UInventoryBase* playerInventory = nullptr;
	UPROPERTY(EditAnywhere, Category = "Inventory")
	UInventoryBase* otherInventory = nullptr;

	// Slot Selected in UI
	FSloSelected slotSelected = FSloSelected(); // i only need the <<id>> 
	FSloSelected secondSlotSelected = FSloSelected();

	// UI
	bool inventoryOpen = false; // show inv
	int BombardiroCrocodilo = -1; // we can also call it AddAllItemCurrentIndex
	//construct
public:
protected:
private:
	// InventoryTimesMultiplier
	//methods
public:
	UFUNCTION(BlueprintCallable, Category = "InventoryManager")
	void SelectSlot(int index, UInventoryBase* inventory);
	UFUNCTION(BlueprintCallable, Category = "InventoryManager")
	void RevertSelection();
	
	UFUNCTION(BlueprintCallable, Category = "InventoryManager")
	void UseSlot(FSlotSelected slot);

	// void PlayTimerSort();
	UFUNCTION(BlueprintCallable, Category = "InventoryManager")
	void PlayTimerUseItem(); // let me see
	UFUNCTION(BlueprintCallable, Category = "InventoryManager")
	void StopAllTimer();

	// per ora
	UFUNCTION(BlueprintCallable, Category = "InventoryManager")
	void UseQuickSlot(int slotToUse);
	UFUNCTION(BlueprintCallable, Category = "InventoryManager")
	void AddItemInSlotSelectedTimer(); // AddItemInSlotSelected()

	
	// Setter
	UFUNCTION(BlueprintCallable, Category = "InventoryManager")
	void SetEnemyInventory(UInventoryBase* inventoryToOpen) { otherInventory = inventoryToOpen; }
	

	// UInventoryBase* GetPlayerInventory() { return playerInventory; }
	// UInventoryBase* GetEnemyInventory() { return otherInventory; }
 
	
	UFUNCTION(BlueprintPure, Category = "InventoryManager")
	bool GetInventoryOpen() { return inventoryOpen; }
	/*
	UFUNCTION(BlueprintCallable, Category = "InventoryManager")
	void OpenCloseInventoryUi(bool isOpen);

	
	// x cri
	UFUNCTION(BlueprintCallable, Category = "InventoryManager")
	void  GiveItem(FItem itemToAdd);
	
	UFUNCTION(BlueprintCallable, Category = "InventoryManager")
	FItem GetItemSelected()
	{
		FItem itemSelected = FItem(slotSelected.inventory->GetItem(slotSelected.index), slotSelected.inventory->GetItemAmount(slotSelected.index));
		return itemSelected;
	}

	FTimerHandle GetMyTimerHandle() { return MyTimerHandle; }*/


		// UI
	UFUNCTION(BlueprintCallable)
	void MouseOver(UInventoryBase* inv, int index);
	UFUNCTION(BlueprintCallable)
	void RemoveItem();
protected:
	virtual void BeginPlay() override;
	
private:
	void EmptySlot(FSlotSelected item);
/*
	// Switch Functions
	void PlayTimerSwitchSlot();
	void  SwitchSlots(FSlotSelected firstSlot, FSlotSelected secondSlot);
	void  ReplaceSlot(FSlotSelected slot, FSlotSelected slotToReplace);
	void  DeleteSlot(FSlotSelected itemToRemove);
	void EndTimerSwitch();
	
	void EndTimerSort();
	void EndTimerUse();
	
	// Getter
	FItem ConvertSlotToItem(FSlotSelected slotToConvert)
	{ return  FItem(slotToConvert.inventory->GetItem(slotToConvert.index), slotToConvert.inventory->GetItemAmount(slotToConvert.index)); }

	// UI
	void LoadUi(FSlotSelected slot)
	{ onChangeSlotUiDelegate.Broadcast(slot.index, slot.inventory, false, false); }*/
};

