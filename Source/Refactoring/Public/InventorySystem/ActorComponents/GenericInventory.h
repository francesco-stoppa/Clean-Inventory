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
	TArray<UItemInfo*> ItemList = TArray<UItemInfo*>();
	/*UPROPERTY(Category = "Inventory")
	AActor* Owner;*/
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 MaxItemNumber;
	UPROPERTY()
	bool bIsPlayer = false;
private:
	UPROPERTY()
	int32 GridRow = 0;
	UPROPERTY()
	int32 GridColumn  = 0;
	
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
	UItemInfo* GetItem(int32 Id);
	
	// Setter
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItem(int32 Id, UItemInfo* Item); // needs to be define
	UFUNCTION(BlueprintCallable, Category = "Inventory") // serve ?
	void SetMaxItemNumber(int32 MaxItemNumber_);
	
	int32 GetColumn() const { return GridColumn; }
	int32 GetRow() const { return GridRow; }
	void SetCoulmn(int32 Column) { GridColumn = Column; }
	
protected:
	UFUNCTION()
	void BeginPlay() override;
	UFUNCTION(Category = "Inventory")
	void FillSlots();
	/*UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Sort();*/ // maybe i need sort too
	
private:
	
};

