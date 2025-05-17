#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GarbageSlotUi.generated.h"

UCLASS()
class CLEAN_INVENTORY_API UGarbageSlotUi : public UUserWidget
{
	GENERATED_BODY()
	// Fields
public:
protected:
private:
	UPROPERTY()
	class UManageInventorySlots* inventoryManager;

	UPROPERTY(Meta = (BindWidgetOptional))
	class UButton* slotButton;
	UPROPERTY(Meta = (BindWidgetOptional))
	class UImage* quickSlotImage;
	
	// Constructors
public:
protected:
private:
	
	// Methods
public:
	UFUNCTION(BlueprintCallable)
	void DeleteSlot();
protected:
	virtual void NativeConstruct() override;
private:
	void OnTooltipChanged();
};
