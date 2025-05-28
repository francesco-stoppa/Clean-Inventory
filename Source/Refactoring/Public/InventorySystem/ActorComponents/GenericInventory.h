#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystem/Structs/Item.h"
#include "GenericInventory.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REFACTORING_API UGenericInventory : public UActorComponent
{
	GENERATED_BODY()

	// Fields
public:
protected:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<struct FItem> ItemList = TArray<FItem>();
	/*UPROPERTY(Category = "Inventory")
	AActor* Owner;*/
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 MaxItemNumber;
private:
	
	// Constructors
public:
protected:
private:

	// Methods
public:
	// Getter
	UFUNCTION(BlueprintPure, Category = "Inventory") // serve ?
	int32 GetMaxItemNumber() const {return MaxItemNumber; }
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetFirstEmptyId();
	UFUNCTION(BlueprintPure, Category = "Inventory") // why i need it? maybe is bettere only the asset pointer
	FItem GetItem(int32 Id);
	
	// Setter
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItem(int32 Id, FItem Item); // needs to be define
	UFUNCTION(BlueprintCallable, Category = "Inventory") // serve ?
	void SetMaxItemNumber(int32 MaxItemNumber_);
protected:
	UFUNCTION(Category = "Inventory")
	void FillSlots();
	/*UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Sort();*/ // maybe i need sort too
	
private:
	
};

