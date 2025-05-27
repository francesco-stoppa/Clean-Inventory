#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInventory.generated.h"

UCLASS()
class CLEAN_INVENTORY_API UWidgetInventory : public UUserWidget
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
	UPROPERTY(Meta = (BindWidgetOptional))
	class UButton* sortButton;
	UPROPERTY()
	TWeakObjectPtr<UManageInventory> PlayerInventory;
	
	// Methods
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowInventory(bool isOpen);
protected:
	virtual void NativeConstruct() override;

private:
	
};

