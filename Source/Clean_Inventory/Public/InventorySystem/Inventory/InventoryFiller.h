#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/Items/Structs/RandomicItem.h"
#include "Components/ActorComponent.h"
#include "InventoryFiller.generated.h"

/* This is a component that randomly generates items in the inventory. */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TBO02_API UInventoryFiller: public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<FRandomicItem> itemsToSpawn = TArray<FRandomicItem>();
	
protected:
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	class UInventoryBase* inventory;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	bool generateAtStart;
	
	//construct
public:
protected:
private:

	//methods
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void GeneradeInventory();

	// TEST
	UFUNCTION(CallInEditor, Category = "TestButtons")
	void FillInventory() { GeneradeInventory(); }
	
protected:
	virtual void BeginPlay() override;
private:
	
};
