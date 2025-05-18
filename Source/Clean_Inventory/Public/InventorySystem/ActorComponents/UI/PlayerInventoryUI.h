#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInventoryUI.generated.h"
/* * I use this script to create a UWidget with a button for the function Sort() */
UCLASS()
class CLEAN_INVENTORY_API UPlayerInventoryUI : public UUserWidget
{
	GENERATED_BODY()
	
	// Fields
public:
protected:
private:
	UPROPERTY()
	class UManageInventorySlots* inventoryManager;
	UPROPERTY(Meta = (BindWidgetOptional))
	class UButton* sortButton;
	// Constructors
public:
protected:
private:
	
	// Methods
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SortSlots();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowInventory(bool isOpen);
protected:
	virtual void NativeConstruct() override;

private:
	
};

