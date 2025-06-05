#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventorySystem/Widgets/WidgetSlot.h"
#include "InventorySystem/Enum/EnumList.h"
#include "WidgetInventory.generated.h"

UCLASS()
class REFACTORING_API UWidgetInventory : public UUserWidget
{
	GENERATED_BODY()
	
	// Fields
public:
protected:
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	bool bIsPlayer = false;

	int InvButtonUse = 0;
	// Constructors
public:
protected:
private:
	UPROPERTY()
	class UManageInventory* PlayerInventory;
	
	UPROPERTY(VisibleAnywhere)
	class UGenericInventory* Inventory = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TSoftObjectPtr<UUniformGridPanel> GridPanel;
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UWidgetSlot> SlotClass;
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<UWidgetSlot*> Slots;
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 GridRow = 2;
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 GridColumn  = 4;
	
	UPROPERTY()
	int32 SlotCreated  = -1;
	UPROPERTY()
	bool bIsMoreInventoryOpen = false;
	
	// Add vv
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 CurrentId;
	
	// Methods
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ShowInventory(bool bIsOpen);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SwitchSlot(int FirstIdToLoad, UGenericInventory* FirstInventory, int SecondIdToLoad, UGenericInventory* SecondInventory);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void LoadSlot(int IdToLoad, UGenericInventory* InventoryToLoad);
	
	// Add vv
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CursorOver(EDirections Direction = EDirections::Default);

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION(Category = "Inventory")
	void CreateInventory();
	UFUNCTION(Category = "Inventory")
	void LoadInventory(bool bIsPlayer_ = false);
	
};