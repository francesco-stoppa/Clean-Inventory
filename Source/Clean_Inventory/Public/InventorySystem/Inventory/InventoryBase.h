#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystem/Items/Structs/Item.h"
#include "InventoryBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSortSlotSignature, bool, slotSlots);

/*
This is a list of objects with a capacity limit and the ability to reorder themselves.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TBO02_API UInventoryBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<FItem> inventory = TArray<FItem>();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FSortSlotSignature onSortUiDelegate;
	
protected:
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int maxSlots;
	UPROPERTY(EditAnywhere, Category = "Inventory",  meta = (UIMin = 0))
	int quickSlots = 3;
	UPROPERTY(EditAnywhere, Category = "Inventory")
	class UListToStortItems* itemsOrder;
	
	//construct
public:
protected:
private:

	//methods
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void FillSlots();
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DeleteEmptyItemFromTheList();
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Sort();
	
	// Getter
	UFUNCTION(BlueprintPure, Category = "Inventory")
	int GetMaxSlots() {return maxSlots; }
	UFUNCTION(BlueprintPure, Category = "Inventory")
	int GetQuickSlots() {return quickSlots-1; }
	UFUNCTION(BlueprintPure, Category = "Inventory")
	UItemInfo* GetItem(int index) { return inventory[index].item; }
	UFUNCTION(BlueprintPure, Category = "Inventory")
	int GetItemAmount(int index) { return inventory[index].amount; }
	UFUNCTION(BlueprintPure, Category = "Inventory")
	int GetEmptySlots();
	UFUNCTION(BlueprintPure, Category = "Inventory")
	int GetSlotsOccupite();
	
	
	// Setter
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItem(int index, UItemInfo* item);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemAmount(int index, int amount);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemAndAmount(int index, UItemInfo* item, int amount);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void EventStart() { onSortUiDelegate.Broadcast(true); }

protected:
private:
	
};

