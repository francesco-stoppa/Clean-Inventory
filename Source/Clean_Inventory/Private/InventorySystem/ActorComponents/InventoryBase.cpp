#include "Clean_Inventory/Public/InventorySystem/ActorComponents/InventoryBase.h"
#include "InventorySystem/Items/ItemInfo.h" 
#include "InventorySystem/Items/ListToStortItems.h" 

/*
WHAT IT DOES:
1. Fill the inventory with empty Item
2. if there are occupied slots it fills the next ones
*/
void UInventoryBase::FillSlots()
{
	int startCount = 0;
	if (!inventory.IsEmpty())
		startCount = inventory.Num();
	/*
	if (startCount < maxSlots)
		for (int i = startCount; i < maxSlots; i++)
			inventory.Add(FItem());*/
}
/*
WHAT IT DOES:
1. Delete all empty slot
NOTE:
Function I use to not sort empty slots or fill an inventory (<- ManageInventorySlot).
*/
void UInventoryBase::DeleteEmptyItemFromTheList()
{/*
	if (!inventory.IsEmpty())
		for (int i = inventory.Num()-1; i > -1; i--)
			if(inventory[i].item == nullptr && i >= quickSlots)// >=
				inventory.RemoveAt(i);*/
}

// Getter
/*
WHAT IT DOES:
1. Check if the inventory is empty (otherwise return every Slot exept the QuickSlots).
2. Foreach item in the list it takes track of that number.
3. Check the other empty Slot.
4. If there are object in the QuickSlots delete that.
 */
int UInventoryBase::GetEmptySlots()
{			// 1.
	int occupiteSlots = 0;/*
	if (!inventory.IsEmpty())
	{		// 2.
		for (auto itemInTheList : inventory)
			if (itemInTheList.item != nullptr)
				occupiteSlots++;
			// 3.
		occupiteSlots = maxSlots - occupiteSlots;
		for (int i = 0; i < quickSlots; i++) 	// check the quickslots
		{	// 4.
			if (inventory[i].item == nullptr)
				occupiteSlots--;
		}
	}
	else
		occupiteSlots = maxSlots - quickSlots;
	
	if(quickSlots == 0)
		occupiteSlots = 0;*/
	return occupiteSlots;
}
int UInventoryBase::GetSlotsOccupite()
{			// 1.
	int occupiteSlots = 0;/*
	if (!inventory.IsEmpty())
	{
		// 2.
		for (auto itemInTheList : inventory)
			if (itemInTheList.item != nullptr)
				occupiteSlots++;
	}
	*/
	return occupiteSlots;
}

// Setter
void UInventoryBase::SetItemAndAmount(int index, UItemInfo* item, int amount)
{
	SetItem(index, item);
	SetItemAmount(index, amount);
}
//void UInventoryBase::SetItem(int index, UItemInfo* item) { inventory[index].item = item; }
void UInventoryBase::SetItemAmount(int index, int amount)
{/*
	if (amount > 0)
	{
		if (amount >= GetItem(index)->maxAmount)
			inventory[index].amount = GetItem(index)->maxAmount;
		else
			inventory[index].amount = amount;
	}
	else
	{
		inventory[index].amount = 0;
		inventory[index].item = nullptr;
	}*/
}

/* 
WHAT IT NEEDS:
- A complete "sortList" with all the game elements ordered in the way you prefer.
WHAT IT DOES:
1. Deletes empty items in inventory
2. For each item in "sortList" it searches for a matching item
3. If it finds one, it places it at the bottom of inventory
4. If there are missing items, it adds the empty ones
NOTE:
If after this function the inventory has a staggered order, reselect "WHAT DOES IT NEED".
*/
void UInventoryBase::Sort() // I need to fix the comments (after the last code update)
{/*
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
		}*/
}

