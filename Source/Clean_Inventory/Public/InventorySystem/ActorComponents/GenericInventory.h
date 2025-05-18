#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
// #include "InventorySystem/Items/Structs/Item.h"
#include "GenericInventory.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLEAN_INVENTORY_API UGenericInventory : public UActorComponent
{
	GENERATED_BODY()

	// Fields
public:
protected:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<FItem> ItemList = TArray<FItem>();
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 MaxItemNumber;
private:
	
	// Constructors
public:
protected:
private:

	// Methods
public:
protected:
	UFUNCTION(Category = "Inventory")
	void FillSlots();
	
	// Getter
	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetMaxItemNumber() const {return MaxItemNumber; }
	UFUNCTION(BlueprintPure, Category = "Inventory")
	FItem* GetItem(int index) { return &ItemList[index]; }
	
	// Setter
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItem(int index, FItem* item); // needs to be define
private:
	
};

