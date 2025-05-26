#include "Clean_Inventory/Public/InventorySystem/ActorComponents/InventoryFiller.h"
#include "Clean_Inventory/Public/InventorySystem/ActorComponents/InventoryBase.h"

void UInventoryFiller::BeginPlay()
{
	Super::BeginPlay();

	// check that the actor it is associated with has an inventory
	inventory = GetOwner()->FindComponentByClass<UInventoryBase>();
	
	if (generateAtStart)// Integrity->OnDeath.addDynamic(this, GeneradeInventory());
		GeneradeInventory();
}

/*
WHAT IT DOES:
1. Check that the actor has an inventory
2. Iterates through all the "itemsToSpawn" 
3. I choose a random number between 1 and 100
4. If the number obtained falls within the "spawnRate", I add that item to my list
NOTE:
To test
END*/
void UInventoryFiller::GeneradeInventory()
{	// 1
	if (inventory != nullptr)
	{
		for (int i = 0; i < itemsToSpawn.Num(); i++) // 2.
		{
			int result = rand() % 100 + 1; // 3.
			int bob = inventory->GetEmptySlots();
			UE_LOG(LogTemp, Warning, TEXT("result: %d"), bob);
			if (result <= itemsToSpawn[i].spawnRate
				&& inventory->GetMaxSlots() > bob)  // 4.  // To Test vv // FItem itemToAdd = FItem(itemsToSpawn[i].item);
			{
				//inventory->inventory.Add(itemsToSpawn[i].item); // Add(itemToAdd)

			}
		}
		inventory->FillSlots();
	}
}

