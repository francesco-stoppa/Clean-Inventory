#include "InventorySystem/Items/ModifierItemInfo.h"
#include "CharacterLogic/GenericCharacter.h"
/*
WHAT IT DOES:
1. Iterates through all the "Modifiers"
2. Applies them to the "target".
NOTE:
Need to be tested.
END*/
void UModifierItemInfo::UseItem_Implementation(AGenericCharacter* Target)
{
	Super::UseItem(Target);
	
	//if (!Target)
	//	return;

	//if(Modifiers.Num() < 0)
	//{
	//	return;
	//}

	//// to test
	//for (int i = 0; i < Modifiers.Num(); i++)
	//{
	//	Modifiers[i]->Apply(Target->GetModifierDispatcherComponent());
	//}
}
