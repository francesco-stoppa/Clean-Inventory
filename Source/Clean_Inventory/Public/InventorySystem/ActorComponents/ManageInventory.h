#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystem/ActorComponents/GenericInventory.h"
#include "ManageInventory.generated.h"

USTRUCT(BlueprintType)
struct FSlotSelected
{
	GENERATED_BODY()

	UPROPERTY()
	int32 Id;
	UPROPERTY()
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

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
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
	UFUNCTION(Category = "Inventory")
	void SelectSlot(int32 Id, TWeakObjectPtr<UGenericInventory> Inventory);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RevertSelection() { Selection = FSlotSelected(); }
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SwitchSlot(FSlotSelected FirstSelection, FSlotSelected SecondCoordinates);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseSlot();
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(FItem ItemToAdd); // if false = inv full

	UFUNCTION(Category = "Inventory")
	UTexture2D* GetSlotTexture(int32 Id, TWeakObjectPtr<UGenericInventory> Inventory);
	
	UFUNCTION(Category = "Inventory")
	TWeakObjectPtr<UGenericInventory> GetCloseInventory()
	{
		if (ChestInventory != nullptr)
		{
			return ChestInventory;
		}
		else
		{
			return nullptr;
		}
	}
protected:
private:
	
};

