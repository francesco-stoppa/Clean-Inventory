#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LootInventoryUi.generated.h"

/* * I use this script to create a UWidget with a button for the function TakeAll() */
UCLASS()
class CLEAN_INVENTORY_API ULootInventoryUi : public UUserWidget
{
	GENERATED_BODY()
	
	// Fields
public:
protected:
private:
	UPROPERTY()
	class UManageInventorySlots* inventoryManager;

	UPROPERTY(Meta = (BindWidgetOptional))
	class UButton* takeButton;
	
	// Constructors
public:
protected:
private:
	
	// Methods
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void TakeAllSlots();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowInventory(bool isOpen);
protected:
	virtual void NativeConstruct() override;

private:
	
};
