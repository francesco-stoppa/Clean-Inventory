#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventorySystem/Widgets/WidgetHint.h"
#include "InventorySystem/Enum/EnumList.h"
#include "WidgetCommands.generated.h"

UCLASS()
class REFACTORING_API UWidgetCommands : public UUserWidget
{
	GENERATED_BODY()
	
	// Fields
public:
protected:
private:
	UPROPERTY()
	class UManageInventory* PlayerInventory;
	
	UPROPERTY(Meta = (BindWidget))
	TSoftObjectPtr<UUniformGridPanel> GridPanel;
	UPROPERTY(EditAnywhere, Category = "Commands")
	TSubclassOf<UWidgetHint> HintClass;
	UPROPERTY(EditAnywhere, Category = "Commands")
	TArray<UWidgetHint*> Hints;
	UPROPERTY(EditAnywhere, Category = "Commands")
	int32 GridRow = 2;
	UPROPERTY(EditAnywhere, Category = "Commands")
	int32 GridColumn  = 1;
	
	// Constructors
public:
protected:
private:
	
	// Methods
public:
	void UpdateHints(int32 Id, ECommands Command);
	
protected:
	virtual void NativeConstruct() override;

private:
	void CreateHints();
	
};

