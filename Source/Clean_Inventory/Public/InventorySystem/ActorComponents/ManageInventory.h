#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Clean_Inventory/Public/InventorySystem/ActorComponents/GenericInventory.h"
#include "ManageInventory.generated.h"

USTRUCT(BlueprintType)
struct FSlotSelected
{
	GENERATED_BODY()

	UPROPERTY(Category = "Slot")
	int32 Id;
	UPROPERTY(Category = "Slot")
	TWeakObjectPtr<UGenericInventory> Inventory;

	// Empty
	FSlotSelected() :
	Id(-1),
	Inventory(nullptr) {}
	
	// Create
	FSlotSelected(int32 NewId, TWeakObjectPtr<UGenericInventory> NewInventory) :
	Id(NewId),
	Inventory(NewInventory) {}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLEAN_INVENTORY_API UManageInventory: public UGenericInventory
{
	GENERATED_BODY()
	
	// Fields
public:
protected:
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	float HoldTime;
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	FSlotSelected Selection;
	/*UPROPERTY(VisibleAnywhere, Category = "Inventory")
	bool bIsOpen = false;*/
	TWeakObjectPtr<UGenericInventory> ChestInventory = nullptr;
	// FTimerHandle TimerHandle;

	// Constructors
public:
protected:
private:

	// Methods
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SelectSlot(int32 id, TWeakObjectPtr<UGenericInventory> Inventory);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RevertSelection() { Selection = FSlotSelected(); }
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SwitchSlot(FSlotSelected FirstSelection, FSlotSelected SecondCoordinates);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseSlot();
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(FItem ItemToAdd); // if false = inv full
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CloseInventory();
protected:
private:
	
};

/*
 *UFUNCTION(BlueprintCallable, Category = "InventoryManager")
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

	FTimerHandle GetMyTimerHandle() { return MyTimerHandle; }


		// UI
	UFUNCTION(BlueprintCallable)
	void MouseOver(UInventoryBase* inv, int index);
	UFUNCTION(BlueprintCallable)
	void RemoveItem();
protected:
	virtual void BeginPlay() override;
	
private:
	void EmptySlot(FSlotSelected item);

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

