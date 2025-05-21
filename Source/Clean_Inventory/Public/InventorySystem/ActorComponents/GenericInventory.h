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
	UPROPERTY(EditAnywhere, Category = "Inventory")
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
	UFUNCTION(BlueprintPure, Category = "Inventory") // serve ?
	int32 GetMaxItemNumber() const {return MaxItemNumber; }
	UFUNCTION(BlueprintPure, Category = "Inventory") // why i need it? maybe is bettere only the asset pointer
	FItem* GetItem(int32 id) { return &ItemList[id]; }
	
	// Setter
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItem(int32 id, FItem Item); // needs to be define
	/*UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Sort(); // maybe i need sort too
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DeleteEmptyItemFromTheList();*/ // maybe
private:
	
};

