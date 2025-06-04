#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetHint.generated.h"

UCLASS()
class REFACTORING_API UWidgetHint : public UUserWidget
{
	GENERATED_BODY()
	
	// Fields
public:
protected:
private:
	UPROPERTY(Meta = (BindWidget))
	TSoftObjectPtr<class UImage> Image;
	UPROPERTY(Meta = (BindWidget))
	TSoftObjectPtr<class UTextBlock> TextBlock;
	
	// Constructors
public:
protected:
private:
	
	// Methods
public:
	UFUNCTION(BlueprintCallable, Category = "Command")
	void SetCommand(FName CommandText, UTexture2D* TextureImage);
	UFUNCTION(BlueprintCallable, Category = "Command")
	void BlockCommand();
	UFUNCTION(BlueprintCallable, Category = "Command")
	void ShowCommand(bool bHide = false);
	
protected:
	// virtual void NativeConstruct() override;

private:
	
};
