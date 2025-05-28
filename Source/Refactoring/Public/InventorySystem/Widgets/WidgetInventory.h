#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventorySystem/Widgets/WidgetSlot.h"
#include "WidgetInventory.generated.h"

UCLASS()
class REFACTORING_API UWidgetInventory : public UUserWidget
{
	GENERATED_BODY()
	
	// Fields
public:
protected:
private:
	UPROPERTY(EditAnywhere)
	bool bIsPlayer = false;
	
	// Constructors
public:
protected:
private:
	UPROPERTY()
	class UManageInventory* PlayerInventory;
	
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
	int32 i  = -1;
	
	// Methods
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ShowInventory(bool bIsOpen);
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION(Category = "Inventory")
	void CreateInventory();
	
};