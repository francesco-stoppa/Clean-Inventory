#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetItemDescription.generated.h"

UCLASS()
class REFACTORING_API UWidgetItemDescription : public UUserWidget
{
	GENERATED_BODY()
	
	// Fields
public:
protected:
private:
	UPROPERTY(Meta = (BindWidget))
	TSoftObjectPtr<class UTextBlock> NameText;
	UPROPERTY(Meta = (BindWidget))
	TSoftObjectPtr<class UTextBlock> DescriptionText;
	
	UPROPERTY()
	class UManageInventory* PlayerInventory;	// Constructors
public:
protected:
private:
	
	// Methods
public:
	UFUNCTION(BlueprintCallable, Category = "Item Description")
	void OpenWidget(FName Name, FText Description);
	UFUNCTION(BlueprintCallable, Category = "Item Description")
	void CloseWidget();
	
protected:
	virtual void NativeConstruct() override;

private:
	
};

