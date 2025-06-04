#include "InventorySystem/Widgets/WidgetItemDescription.h"
#include "Components/TextBlock.h"
#include "Refactoring/RefactoringCharacter.h"
#include "InventorySystem/ActorComponents/ManageInventory.h"

void UWidgetItemDescription::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerInventory = GetOwningPlayerPawn<ARefactoringCharacter>()->GetComponentByClass<UManageInventory>();
	if (PlayerInventory)
	{
		PlayerInventory->onItemInfoDelegate.AddDynamic(this, &UWidgetItemDescription::OpenWidget);
	}
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetItemDescription::OpenWidget(FName Name, FText Description)
{
	this->SetVisibility(ESlateVisibility::Visible);
	NameText->SetText(FText::FromName(Name));
	DescriptionText->SetText(Description);
}

void UWidgetItemDescription::CloseWidget()
{
	if (GetVisibility() == ESlateVisibility::Visible)
	{
		this->SetVisibility(ESlateVisibility::Collapsed);
	}
}

