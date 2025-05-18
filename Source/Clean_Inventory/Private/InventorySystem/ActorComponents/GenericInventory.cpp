#include "Clean_Inventory/Public/InventorySystem/ActorComponents/GenericInventory.h"
/*#include "InventorySystem/Items/ItemInfo.h" 
#include "InventorySystem/Items/ListToStortItems.h"*/ 

/*
void UInventoryBase::FillSlots()
{
	int startCount = 0;
	if (!inventory.IsEmpty())
		startCount = inventory.Num();
	
	if (startCount < maxSlots)
		for (int i = startCount; i < maxSlots; i++)
			inventory.Add(FItem());
}

void UInventoryBase::DeleteEmptyItemFromTheList()
{
	if (!inventory.IsEmpty())
		for (int i = inventory.Num()-1; i > -1; i--)
			if(inventory[i].item == nullptr && i >= quickSlots)// >=
				inventory.RemoveAt(i);
}

// Getter
int UInventoryBase::GetEmptySlots()
{			// 1.
	int occupiteSlots = 0;
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
		occupiteSlots = 0;
	return occupiteSlots;
}
int UInventoryBase::GetSlotsOccupite()
{			// 1.
	int occupiteSlots = 0;
	if (!inventory.IsEmpty())
	{
		// 2.
		for (auto itemInTheList : inventory)
			if (itemInTheList.item != nullptr)
				occupiteSlots++;
	}
	
	return occupiteSlots;
}

// Setter
void UInventoryBase::SetItemAndAmount(int index, UItemInfo* item, int amount)
{
	SetItem(index, item);
	SetItemAmount(index, amount);
}
void UInventoryBase::SetItem(int index, UItemInfo* item) { inventory[index].item = item; }
void UInventoryBase::SetItemAmount(int index, int amount)
{
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
	}
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

