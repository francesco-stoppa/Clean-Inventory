#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystem/ActorComponents/GenericInventory.h"
#include "ManageInventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOpenInventorySignature, bool, bIsInventoryOpen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSwitchSlotsSignature, int, FirstIdToLoad, UGenericInventory*, FirstInventory, int, SecondIdToLoad, UGenericInventory*, SecondInventory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLoadSlotSignature, int, IdToLoad, UGenericInventory*, InventoryToLoad);

USTRUCT(BlueprintType)
struct FSlotSelected
{
	GENERATED_BODY()

	int32 Id;
	UGenericInventory* Inventory;

	// Empty
	FSlotSelected() :
	Id(-1),
	Inventory(nullptr) {}
	
	// Create
	FSlotSelected(int32 NewId, UGenericInventory* NewInventory) :
	Id(NewId),
	Inventory(NewInventory) {}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REFACTORING_API UManageInventory: public UGenericInventory
{
	GENERATED_BODY()
	
	// Fields
public:
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOpenInventorySignature onOpenInventoryDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FSwitchSlotsSignature onSwitchSlotsInventoryDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FLoadSlotSignature onSLoadSlotDelegate;
protected:
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	float HoldTime;
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	FSlotSelected Selection;
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	class UGenericInventory* ChestInventory = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	bool bIsInventoryOpen = false;
	// Constructors
public:
protected:
private:

	// Methods
public:
	UFUNCTION(Category = "Inventory")
	void SelectSlot(int32 Id, UGenericInventory* Inventory);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RevertSelection(bool LoadUI = true);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SwitchSlot(FSlotSelected FirstSelection, FSlotSelected SecondCoordinates);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseSlot();
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropSlot();
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UItemInfo* ItemToAdd); // if false = inv full

	UFUNCTION(Category = "Inventory")
	UTexture2D* GetSlotTexture(int32 Id, UGenericInventory* Inventory) const;

	UFUNCTION(Category = "Inventory")
	UGenericInventory* GetChestInventory() const
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
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetChestInventory(UGenericInventory* NewChestInventory);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool ShowInventory();
protected:
private:

};

