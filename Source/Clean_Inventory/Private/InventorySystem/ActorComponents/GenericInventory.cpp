#include "Clean_Inventory/Public/InventorySystem/ActorComponents/GenericInventory.h"
#include "InventorySystem/Structs/Item.h" 

void UGenericInventory::FillSlots()
{
	int32 startCount = 0;
	if (!ItemList.IsEmpty())
		startCount = ItemList.Num();
	
	if (startCount < MaxItemNumber)
		for (int32 i = startCount; i < MaxItemNumber; i++)
			ItemList.Add(FItem());
}

// Setter
void UGenericInventory::SetItem(int32 id, FItem Item) // doesn't have an amount
{ ItemList[id] = Item; }

/*
*void UInventoryBase::DeleteEmptyItemFromTheList()
{
	if (!inventory.IsEmpty())
		for (int i = inventory.Num()-1; i > -1; i--)
			if(inventory[i].item == nullptr && i >= quickSlots)// >=
				inventory.RemoveAt(i);
}

void UInventoryBase::Sort() // I need to fix the comments (after the last code update)
{
	if (itemsOrder!=nullptr) 
		if (!itemsOrder->sortList.IsEmpty())
		{
			DeleteEmptyItemFromTheList();
			
			for (UItemInfo* itemInSort : itemsOrder->sortList)
			{
				int sortInventoryCount = quickSlots -1;
			
				for (int i = inventory.Num()-1; i > sortInventoryCount; i--)
					if(itemInSort != nullptr && inventory[i].item != nullptr)
						if (itemInSort->name == inventory[i].item->name)
							if (inventory[i].item->name == inventory[inventory.Num()-1].item->name
									&& i != inventory.Num()-1
										&& inventory[inventory.Num()-1].item->maxAmount > GetItemAmount(inventory.Num()-1))
							{
								int r = GetItemAmount(inventory.Num()-1) + GetItemAmount(i);
								if (r <= inventory[inventory.Num()-1].item->maxAmount)
								{
									SetItemAmount(inventory.Num()-1, inventory[inventory.Num()-1].item->maxAmount);
									inventory.RemoveAt(i);
								}
								else
								{
									int d = r -  inventory[inventory.Num()-1].item->maxAmount;
									SetItemAmount(inventory.Num()-1, inventory[inventory.Num()-1].item->maxAmount);
									SetItemAmount(i, d);
									FItem temporaryItem = FItem(inventory[i]);
									inventory.RemoveAt(i);
									inventory.Add(temporaryItem);
								}
							}
							else
							{
								FItem temporaryItem = FItem(inventory[i]);
								inventory.RemoveAt(i);
								inventory.Add(temporaryItem);
							}
			}
			
			FillSlots();
			// UI vv
			EventStart();
		}
}
*/

