#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/Items/ItemInfo.h"
#include "Item.generated.h"

USTRUCT(BlueprintType)
struct FOldItem 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Item")
	class UItemInfo* item = nullptr;
	UPROPERTY(EditAnywhere, Category = "Item",  meta = (UIMin = 0, UIClampMin = 0))
	int amount = 0;
};
/*
UCLASS()
class UItem : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Item")
	class UItemInfo* item = nullptr;
	UPROPERTY(EditAnywhere, Category = "Item",  meta = (UIMin = 1))
	int amount = 0;
protected:
private:
	//construct
public:
protected:
private:
	//methods
public:
	UFUNCTION(BlueprintCallable)
	void UseItem(TScriptInterface<IModifierTarget>& Target); // TODO Change with ModifiersDispatcherComponent when available
protected:
private:
};

/*

UFUNCTION()
	virtual void UseItem(TScriptInterface<IModifierTarget>& Target); // TODO Change with ModifiersDispatcherComponent when available


 *
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystem/Items/Structs/Item.h"
#include "InventoryBase.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TBO02_API UInventoryBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<FItem> inventory = TArray<FItem>();
	
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
	UFUNCTION(BlueprintCallable)
	void FillSlots();
	UFUNCTION(BlueprintCallable)
	void DeleteEmptyItemFromTheList();
	UFUNCTION(BlueprintCallable)
	void Sort();
	
	// Getter
	UFUNCTION(BlueprintPure)
	int GetMaxSlots() {return maxSlots; }
	UFUNCTION(BlueprintPure)
	UItemInfo* GetItem(int index) { return inventory[index].item; }
	UFUNCTION(BlueprintPure)
	int GetItemAmount(int index) { return inventory[index].amount; }
	UFUNCTION(BlueprintCallable)
	int GetEmptySlots();
	
	// Setter
	UFUNCTION(BlueprintCallable)
	void SetItem(int index, UItemInfo* item);
	UFUNCTION(BlueprintCallable)
	void SetItemAmount(int index, int amount);
	UFUNCTION(BlueprintCallable)
	void SetItemAndAmount(int index, UItemInfo* item, int amount);

protected:
private:
	
};*/