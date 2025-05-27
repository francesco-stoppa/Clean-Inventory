#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetSlot.generated.h"

UCLASS()
class CLEAN_INVENTORY_API UWidgetSlot : public UUserWidget
{
	GENERATED_BODY()
	
	// Fields
public:
protected:
private:
	UPROPERTY(VisibleAnywhere, Category = "UI", meta = (UIMin = 0, UIClampMin = 0))
	int32 Id;
	UPROPERTY(VisibleAnywhere, Category = "UI")
	bool bIsPlayer = false;

	
	UPROPERTY()
	class UTexture2D* AssetThumbnail;

	UPROPERTY()
	TWeakObjectPtr<UGenericInventory> Inventory;
	
	// Constructors
public:
protected:
private:
	UPROPERTY(Meta = (BindWidgetOptional))
	class UButton* SlotButton;
	UPROPERTY(Meta = (BindWidgetOptional))
	class UImage* ItemImage;
	UPROPERTY(Meta = (BindWidgetOptional))
	class UImage* SlotClicked;
	
	UPROPERTY()
	TWeakObjectPtr<UManageInventory> PlayerInventory;
	
	// Methods
public:
	UFUNCTION(Category = "UI") // 4 Creation
	void SetId(int32 Id_) { Id = Id_; }
	UFUNCTION(Category = "UI") // 4 Creation
	void SetPlayerSlot(bool bIsPlayer_) { bIsPlayer = bIsPlayer_; }

	UFUNCTION(Category = "UI")
	void SelectSlots();
	
	UFUNCTION(Category = "UI")
	void ShowSlot();

protected:
	virtual void NativeConstruct() override;
	
private:
	
};

