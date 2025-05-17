#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotUi.generated.h"

/* *This UWidget is bind by the event in the UInventoryBase and the UManageInventorySlots. */
UCLASS()
class TBO02_API USlotUi : public UUserWidget
{
	GENERATED_BODY()
	// Fields
public:
protected:
private:
	UPROPERTY(EditAnywhere, Category = "UI", meta = (UIMin = 0, UIClampMin = 0))
	int id;
	UPROPERTY(EditAnywhere, Category = "UI")
	bool isPlayer = true;

	UPROPERTY()
	class UInventoryBase* inventory;
	UPROPERTY()
	class UManageInventorySlots* inventoryManager;
	UPROPERTY()
	UTexture2D* emptyTexture2D;

	UPROPERTY(Meta = (BindWidgetOptional))
	class UButton* slotButton;
	UPROPERTY(Meta = (BindWidgetOptional))
	class UTextBlock* quickSlotAmount;
	UPROPERTY(Meta = (BindWidgetOptional))
	class UImage* quickSlotImage;
	UPROPERTY(Meta = (BindWidgetOptional))
	class UImage* selection;

	// timer
	UPROPERTY(Meta = (BindWidgetOptional))
	class URadialSlider* timerSlider;
	bool timerSliderReduction = false;
	UPROPERTY(EditAnywhere, Category = "UI",  meta = (UIMin = 0.00001f))
	float timerSliderDuration = 5.0f; // Non credo sia giusto avere qui questa info, ma forse sarebbe meglio fare un getter dalla integrity
	float timerSliderDecayRate = 0;
	float timerSliderElapsed = 0;
	UPROPERTY(EditAnywhere, Category = "UI",  meta = (UIMin = 0.00001f))
	float holdingTime = 1.0f;

	
	bool pressing;
	float currentHoldTime;
	FTimerHandle HoldTimerHandle;

	int slot = -1;
	// Constructors
public:
protected:
private:
	
	// Methods
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowSlot();
	UFUNCTION(BlueprintPure, Category = "UI")
	FText GetDescriptionText();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void PlayTimerSlider(bool isMovingTheItem, bool isSwitching);


	UFUNCTION(BlueprintCallable)
	void OnRightClick();
	UFUNCTION(BlueprintCallable)
	void MouseOver();
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UFUNCTION()
	void SelectSlots();
	UFUNCTION()
	void OnSlotChanged(int slotId,  UInventoryBase* inv, bool isMovingTheItem, bool isSwitching);
	UFUNCTION()
	void OnSortSlots(bool slotSlots) { ShowSlot(); }

	// New
	UFUNCTION()
	void OnLeftClick();

	// Timer
	UFUNCTION()
	void OnTimerEnd();

	
	// Funzioni che verranno chiamate quando il tasto viene premuto o rilasciato
	UFUNCTION()

	void OnButtonPressed();
	UFUNCTION()

	void OnButtonReleased();
	UFUNCTION()

	// Funzione per chiamare quando il tasto viene mantenuto per 5 secondi
	//void OnButtonHoldCompleted();
	//UFUNCTION()

	void CheckHoldDuration();

	UFUNCTION()

	void LoadEmptySlot(int slotToLoad);
};
