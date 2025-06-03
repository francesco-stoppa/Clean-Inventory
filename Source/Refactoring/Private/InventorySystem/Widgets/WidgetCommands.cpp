#include "InventorySystem/Widgets/WidgetCommands.h"
#include "InventorySystem/Widgets/WidgetHint.h"
#include "Refactoring/RefactoringCharacter.h"
#include "InventorySystem/Enum/EnumList.h"


void UWidgetCommands::NativeConstruct()
{
	Super::NativeConstruct();
	
	PlayerInventory = GetOwningPlayerPawn<ARefactoringCharacter>()->GetComponentByClass<UManageInventory>();
	if (PlayerInventory)
	{
		// PlayerInventory->onXxxDelegate.AddDynamic(this, &UWidgetCommands::UpdateHints);
		CreateHints();
	}
}

void UWidgetCommands::CreateHints()
{
	UWidgetHint* WidgetHint = nullptr;
	for (int32 y = 0; y < GridRow; y++)
	{
		for (int32 x = 0; x < GridColumn; x++)
		{
			WidgetHint = CreateWidget<UWidgetHint>(this, HintClass);
			if (WidgetHint)
			{
				WidgetHint->SetCommand(this->GetFName(), nullptr);
			}
		}
	}
}

void UWidgetCommands::UpdateHints(int32 Id, ECommands Command) // TO TEST
{
	FName CommandText = FName(*UEnum::GetDisplayValueAsText(Command).ToString());
	Hints[Id]->SetCommand(CommandText, nullptr);
}

