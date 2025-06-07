#include "InventorySystem/Widgets/WidgetCommands.h"
#include "Refactoring/RefactoringCharacter.h"
#include "InventorySystem/ActorComponents/ManageInventory.h"

// visto che sono 4 i tasti del controller forse è meglio settare la creazione degli hint a quel numero
// non so ancora con chi parentare questo UWidgetCommands per ora UManagerInventory

void UWidgetCommands::NativeConstruct()
{
	Super::NativeConstruct();
	
	PlayerInventory = GetOwningPlayerPawn<ARefactoringCharacter>()->GetComponentByClass<UManageInventory>();
	if (PlayerInventory)
	{
		PlayerInventory->onCommandDelegate.AddDynamic(this, &UWidgetCommands::UpdateHints);
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

void UWidgetCommands::UpdateHints(ECommandStats CommandStat) // TO TEST
{
	FName CommandText;
	switch (CommandStat)
	{
	case ECommandStats::Default:
		break;
	case ECommandStats::Game:
		CommandText = FName(*UEnum::GetDisplayValueAsText(ECommands::Inventory).ToString());
		Hints[0]->SetCommand(CommandText, nullptr);
		for (int32 i = 1; i <Hints.Num(); i++)
		{
			Hints[i]->BlockCommand();
			Hints[i]->SetCommand("...", nullptr);
		}
		break;
	case ECommandStats::Chest:
		CommandText = FName(*UEnum::GetDisplayValueAsText(ECommands::Open).ToString());
		Hints[0]->SetCommand(CommandText, nullptr);
		for (int32 i = 1; i <Hints.Num(); i++)
		{
			Hints[i]->BlockCommand();
			Hints[i]->SetCommand("...", nullptr);
		}
		break;
	case ECommandStats::Inventory:
		CommandText = FName(*UEnum::GetDisplayValueAsText(ECommands::Select).ToString());
		Hints[0]->SetCommand(CommandText, nullptr);
		
		CommandText = FName(*UEnum::GetDisplayValueAsText(ECommands::Close).ToString());
		Hints[1]->SetCommand(CommandText, nullptr);

		
		CommandText = FName(*UEnum::GetDisplayValueAsText(ECommands::Info).ToString());
		Hints[2]->SetCommand(CommandText, nullptr);
		break;
	case ECommandStats::Info:
		CommandText = FName(*UEnum::GetDisplayValueAsText(ECommands::Use).ToString());
		Hints[0]->SetCommand(CommandText, nullptr);
		Hints[0]->BlockCommand();
		
		CommandText = FName(*UEnum::GetDisplayValueAsText(ECommands::Close).ToString());
		Hints[1]->SetCommand(CommandText, nullptr);
		
		CommandText = FName(*UEnum::GetDisplayValueAsText(ECommands::Drop).ToString());
		Hints[2]->SetCommand(CommandText, nullptr);
		break;
	case ECommandStats::Switch:
		CommandText = FName(*UEnum::GetDisplayValueAsText(ECommands::Switch).ToString());
		Hints[0]->SetCommand(CommandText, nullptr);
		
		Hints[1]->BlockCommand();

		CommandText = FName(*UEnum::GetDisplayValueAsText(ECommands::Revert).ToString());
		Hints[2]->SetCommand(CommandText, nullptr);
		break;
	}
	// FName CommandText = FName(*UEnum::GetDisplayValueAsText(Command).ToString());
	// Hints[Id]->SetCommand(CommandText, nullptr);
	
	// un e num per definire gli stati

	// per assegnare il comando controllo gli hint e vedo quali di quelli sono legati a quel comando
	// per ogni hint leggo i loro comandi
	// se uno di loro ha il comando indicato:
			// sostituisco il comando con il testo indicato
			// se il comando è da bloccare allora lo blocco

	// noo non mi fa impazzire e se si utilizzasse una nuova lista di enum
	// controllo l'enum che mi da diverse indicazioni:
		// 1. open inv = tasti con i comandi cambiano nello stato x
		// 2. slot selected = con il tasto wsitch
			// ^^ questo da più sbatti perche se cambio e il tasto e uguale a quello che devo visualizzare mi deve dire cose diverse come revert o stronzte simili
		// 3. info = cambiano 2 con usa e drop
		// 4. game = taseto di apertura inventario
			// ^^ anche questo è sbatti in quanto c'è apri inv, spri chest prendi oggetto
		// e chiudi inventario???
	
}


