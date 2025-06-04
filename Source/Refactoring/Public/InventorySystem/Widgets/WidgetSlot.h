#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetSlot.generated.h"


UCLASS()
class REFACTORING_API UWidgetSlot : public UUserWidget
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
	/*
	UPROPERTY()
	class UTexture2D* AssetThumbnail;*/
	
	UPROPERTY()
	class UTexture2D* MissingAssetThumbnail;

	UPROPERTY()
	class UGenericInventory* Inventory;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* SlotButton;
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;
	UPROPERTY(meta = (BindWidget))
	class UImage* SlotClicked;

	UPROPERTY()
	class UManageInventory* PlayerInventory;
	
	// Methods
public:
	UFUNCTION(Category = "UI") // 4 Creation
	void SetId(int32 Id_) { Id = Id_; }
	UFUNCTION(Category = "UI") // 4 Creation
	void SetPlayerSlot(bool bIsPlayer_) { bIsPlayer = bIsPlayer_; }

	UFUNCTION(Category = "UI")
	void OverSlot();
	UFUNCTION(Category = "UI")
	void NotOverSlot();
	UFUNCTION(Category = "UI")
	void SelectSlot();
	UFUNCTION(Category = "UI")
	void RevertSelectedSlot();
	
	UFUNCTION(Category = "UI")
	void ShowSlot();
	UFUNCTION(Category = "UI")
	void SetInventory(UGenericInventory* NewInventory) { Inventory = NewInventory; }
	
protected:
	virtual void NativeConstruct() override;
	
private:
};
