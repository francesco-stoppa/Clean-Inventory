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
	bool bIsPlayer;
	
	// Constructors
public:
protected:
private:
	
	// Methods
public:/*
	UFUNCTION(Category = "UI")
	void SetId(int32 Id) { this->Id = Id; }*/
	
protected:
private:
	
};

