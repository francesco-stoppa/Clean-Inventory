#include "InventorySystem/Inventory/ManageInventorySlots.h"

#include "CharacterLogic/GenericCharacter.h"
#include "InventorySystem/Inventory/InventoryBase.h"
#include "InventorySystem/Items/ItemInfo.h"
#include "InventorySystem/Items/AmmoItemInfo.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UManageInventorySlots::BeginPlay()
{
	Super::BeginPlay();

	playerInventory = GetOwner()->FindComponentByClass<UInventoryBase>();
	if (playerInventory != nullptr)
		playerInventory->FillSlots();
	else
		UE_LOG(LogTemp, Warning, TEXT("playerInventory: missing"));

	characterOwner = Cast<AGenericCharacter>(GetOwner());
	// to update the UI (I don't do in the <USlotUi> because I need this script to be created)
	PlayTimerSort();
	//OpenCloseInventoryUi(false); // TOTEST
}

/*
WHAT IT NEEDS:
- A INT (which represents the index of the object in its list).
- The inventory of the item selected (its list).
WHAT IT DOES:
1. Check how many slots you have selected:
	a) If is only one fill the first variable SlotSelected.
	b) If there are another one (and they are form the playerInventory) Switch teir position. */
void UManageInventorySlots::SelectSlot(int index, UInventoryBase* inventory)
{// mod
	if (!GetWorld()->GetTimerManager().IsTimerActive(MyTimerHandle))
	{
		// Check if a timer is running (otherwise don't select the item)
		if (slotSelected.inventory != nullptr)
		{
			secondSlotSelected = FSlotSelected(inventory, index);
			if (slotSelected.inventory == otherInventory && otherInventory->GetItem(slotSelected.index) != nullptr
				&& inventory == playerInventory && playerInventory->GetItem(index) == nullptr)
				AddItemInSlotSelectedTimer();
			else
			{
				if (slotSelected.inventory == playerInventory
						&& secondSlotSelected.inventory == playerInventory)
				{
					if (inventory->GetItem(index) == nullptr && slotSelected.inventory->GetItem(slotSelected.index) == nullptr
						|| inventory == slotSelected.inventory && index == slotSelected.index)
						RevertSelection();
					else
					{
						PlayTimerSwitchSlot();
						onSelecSlot.Broadcast(false);
					}
				}
				else
					RevertSelection();
			}
		}
		else
		{
			slotSelected = FSlotSelected(inventory, index);
			if (slotSelected.inventory != nullptr || slotSelected.inventory != otherInventory) // TO CHECK
				onSelecSlot.Broadcast(true);
		}
	}
}
/*
WHAT IT DOES:
1. Revert all the selection. */
void UManageInventorySlots::RevertSelection()
{
	// UI
	if (slotSelected.inventory != nullptr)
		LoadUi(slotSelected);
	if (secondSlotSelected.inventory != nullptr)
		LoadUi(secondSlotSelected);

	slotSelected.index = 0;
	slotSelected.inventory = nullptr;

	secondSlotSelected.index = 0;
	secondSlotSelected.inventory = nullptr;

	onSelecSlot.Broadcast(false);
	// addOneItem = true;
}
/* WHAT IT DOES:
1. Check if the timer is set more than zero.
2. Start the timer. */
void UManageInventorySlots::PlayTimerSwitchSlot()
{
	if (switchItemTimer <= 0)
		EndTimerSwitch();
	else
		GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &UManageInventorySlots::EndTimerSwitch, switchItemTimer * InventoryTimesMultiplier, false);

	onChangeSlotUiDelegate.Broadcast(slotSelected.index, slotSelected.inventory, true, true);
	onChangeSlotUiDelegate.Broadcast(secondSlotSelected.index, secondSlotSelected.inventory, true, true);
	// onMoveSlotUiDelegate.Broadcast(false);
}
/* WHAT IT DOES:
1. Reset the timer.
2. Switch the items (call the function)
3. Revert the all the selection. */
void UManageInventorySlots::EndTimerSwitch()
{
	GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);

	// if they have the same name & the <secondSlotSelected> is not at his max amount vv (order)
	
	if (playerInventory->GetItem(slotSelected.index) != nullptr
			&& playerInventory->GetItem(secondSlotSelected.index) != nullptr
				&& slotSelected.index != secondSlotSelected.index)
	{
		int maxAmount = playerInventory->GetItem(secondSlotSelected.index)->maxAmount;
		if (maxAmount > playerInventory->inventory[secondSlotSelected.index].amount
			&& playerInventory->GetItem(slotSelected.index)->name == playerInventory->GetItem(secondSlotSelected.index)->name)
		{
			int result = playerInventory->inventory[secondSlotSelected.index].amount + playerInventory->inventory[slotSelected.index].amount;
			if (result <= maxAmount)
			{
				playerInventory->SetItemAmount(secondSlotSelected.index, result);
				playerInventory->SetItemAmount(slotSelected.index, 0);
			}
			else
			{
				int difference = result - maxAmount;
				playerInventory->SetItemAmount(secondSlotSelected.index, maxAmount);
				playerInventory->SetItemAmount(slotSelected.index, difference);
			}
		}
		else
			SwitchSlots(slotSelected, secondSlotSelected);
	}
	else
		SwitchSlots(slotSelected, secondSlotSelected);
	RevertSelection();
}
/* WHAT IT DOES:
1. Check the bigger index (base on that change their position). */
void UManageInventorySlots::SwitchSlots(FSlotSelected firstSlot, FSlotSelected secondSlot)
{
	if (firstSlot.index != secondSlot.index)
	{
		bool bigger = false;
		if (firstSlot.inventory == secondSlot.inventory && firstSlot.index > secondSlot.index)
			bigger = true;
		ReplaceSlot(firstSlot,secondSlot);
		secondSlot.index++;
		if (bigger)
			firstSlot.index++;
		ReplaceSlot(secondSlot,firstSlot);
		firstSlot.index++;

		DeleteSlot(firstSlot);
		DeleteSlot(secondSlot);
	}
}
/*
WHAT IT DOES:
- Two slots (one slot to copy and other where it paste).
WHAT DOES IT DO:
1. Replace the slot with the other. */
void UManageInventorySlots::ReplaceSlot(FSlotSelected slot, FSlotSelected slotToReplace) { slotToReplace.inventory->inventory.Insert(ConvertSlotToItem(slot), slotToReplace.index); }
/*
WHAT IT DOES:
- A slot.
WHAT DOES IT DO:
1. Delete that slot form the list. */
void UManageInventorySlots::DeleteSlot(FSlotSelected slot) { slot.inventory->inventory.RemoveAt(slot.index); }

/*
WHAT IT NEEDS:
- A slot
WHAT DOES IT DO:
1. Reduce the amount slot.
2. Check if the amaunt of the object is more than one:
	a) Otherwise empty the slot.
3. Revert the selection.
NOTE:
Not finish. */
void UManageInventorySlots::UseSlot(FSlotSelected slot)
{
	if (slot.inventory != nullptr)
	{
		class UItemInfo* item = slot.inventory->GetItem(slot.index);
		if (item != nullptr)
		{
			int amount = slot.inventory->GetItemAmount(slot.index);

			UAmmoItemInfo* ammo = Cast<UAmmoItemInfo>(item);
			if (ammo == nullptr)
				amount--;
		
			UE_LOG(LogTemp, Warning, TEXT("Use Item")); //  Change with ModifiersDispatcherComponent when available
			
			item->UseItem(characterOwner);
		
			// Play item sound
			if (item->itemSound)
				UGameplayStatics::PlaySound2D(GetWorld(), item->itemSound);

			// Play item VFX
			if (item->itemVFX)
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), item->itemVFX, GetOwner()->GetActorLocation());

			// CHECK
			slot.inventory->SetItemAmount(slot.index, amount);
			// if (amount <= 0) // questo per i proiettili
				RevertSelection();
			LoadUi(slot);

			onItemUsed.Broadcast(item);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Item = null"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Slot/Inventory missing..."));
}
/*
WHAT IT NEED:
- A slot
WHAT IT DOES:
1. Empty the slot selected. */
void UManageInventorySlots::EmptySlot(FSlotSelected slotToFree) { slotToFree.inventory->SetItemAmount(slotToFree.index, 0); }

/*
WHAT IT DOES:
1. Checks every item in the inventory (besides the playerInventory).
2. Set the variable for multiple items to move.
3. Removes empty spots.
4. Adds the first item in the PlayTimerMoveItem.
5. Start the timer.
6. If the timer is ended fill the delete item with empty slot. */
void UManageInventorySlots::AddAllItems()
{
	BombardiroCrocodilo++;
	bool timerEnd = true;
	
	if (playerInventory->GetEmptySlots() > 0)
	{
		if (BombardiroCrocodilo < otherInventory->inventory.Num())
		{
			int i = BombardiroCrocodilo; // I created it because before the end of the timer I change BombardiroCrocodilo (otherwise the pointer is fucked)
			slotSelected = FSlotSelected(otherInventory, i);
			addOneItem = false;
			PlayTimerMoveItem();
			timerEnd = false;
		}
		else
			timerEnd = true;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("PlayerInventory FULL")); // I don't change timer end because is already true

	
	if (timerEnd)
	{
		RevertSelection();
		addOneItem = true;
		BombardiroCrocodilo =-1;
	}
}
/*
WHAT IT DOES:
1. Check if the item exist.
2. Check if the timer is set more than zero.
3. Start the timer. */
void UManageInventorySlots::PlayTimerMoveItem()
{
	float timerTime = 0;
	
	if (ConvertSlotToItem(slotSelected).item != nullptr)
	{
		timerTime = ConvertSlotToItem(slotSelected).item->moveItemTime;
		onChangeSlotUiDelegate.Broadcast(slotSelected.index,slotSelected.inventory, true,false);
	}
	
	if (timerTime <= 0)
		EndTimerAddItem();
	else
		GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &UManageInventorySlots::EndTimerAddItem, timerTime * InventoryTimesMultiplier, false);
}
/*
WHAT IT DOES:
1. Reset the timer.
2. Add the item in the right slot (call the function)
3. Check if the function is ended. */
void UManageInventorySlots::EndTimerAddItem()
{
	GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
	if (slotSelected.inventory != nullptr)
		if (slotSelected.inventory->GetItem(slotSelected.index) != nullptr)
			AddInTheRightSlot(slotSelected);

	// LoadUi(slotSelected);
	// onChangeInventoryUiDelegate.Broadcast(inventoryOpen);
	// onChangeInventoryUiDelegate.Broadcast(inventoryOpen);

	if (!addOneItem)
		AddAllItems();
	else
	{
		int i = 0;
	}
}

/*
WHAT IT NEEDS:
- A slot
WHAT IT DOES:
1. I check all the slots in my inventory.
2. I check if there is a slot with the item I need to add:
	a) If I find it, I calculate the quantity to add.
	b) I add the quantity and see if there is any left.
3. if there are still amounts of the item (or I didn't find a slot with the same item):
	a) I add the item to the first free slot.*/
void UManageInventorySlots::AddInTheRightSlot(FSlotSelected slot)
{
	
	// chek if is nullptr   
	if (ConvertSlotToItem(slot).item->maxAmount > 1)
	{
		int index = -1 ; 
		for (FItem itemInTheList : playerInventory->inventory)
		{
			index++;
			if(itemInTheList.item != nullptr
					&& ConvertSlotToItem(slot).item != nullptr
						&& index > playerInventory->GetQuickSlots()) 
				if (itemInTheList.item->name == ConvertSlotToItem(slot).item->name
						 && itemInTheList.amount > 0
							&& itemInTheList.amount < itemInTheList.item->maxAmount)
				{
					int amoutToAdd = ConvertSlotToItem(slot).amount;
					int amountInTheSpot = itemInTheList.amount;
					int amauntToFill = itemInTheList.item->maxAmount - itemInTheList.amount;
					if (amauntToFill > 0)
					{
						int cycle;
						int amountLeftover = amauntToFill - amoutToAdd;

						if (amountLeftover >= 0)
							cycle = amoutToAdd;
						else
							cycle = amauntToFill;
					
						for (int i = 0; i < cycle; i++)
						{
							amoutToAdd--;	
							amountInTheSpot++;
						}
						playerInventory->SetItemAmount(index, amountInTheSpot);
						onChangeSlotUiDelegate.Broadcast(index, playerInventory, false, false); // << UI CAll
						slot.inventory->SetItemAmount(slot.index, amoutToAdd);
						// RevertSelection();

						if (amoutToAdd <= 0)
						{
							//RevertSelection();
							LoadUi(slot);
							return;
						}
					}
				}
		}
		if (ConvertSlotToItem(slot).amount > 0)
			AddItemInTheFirstFreeSlot(slot);
	}
	else
		AddItemInTheFirstFreeSlot(slot);

	if (!addOneItem)
		onMoveSlotUiDelegate.Broadcast(1);
	else
		onMoveSlotUiDelegate.Broadcast(-1);
}
/*
WHAT IT NEEDS:
- A slot.
WHAT IT DOES:
1. Check if there is an empty spot.
2. Fill the empty spot with the one requested.
3. Clear the spot coordinate.
NOTE:
I made another check just to be sure. */
void UManageInventorySlots::AddItemInTheFirstFreeSlot(FSlotSelected slot)
{
	if (playerInventory->GetEmptySlots() > 0)
	{
		bool done = false;
		if (!playerInventory->inventory.IsEmpty())
		{
			int index = -1;
			for (FItem slotInTheList : playerInventory->inventory)
			{
				index++;
				if (slotInTheList.item == nullptr && !done
					&& index > playerInventory->GetQuickSlots()) // TO debug
				{
					playerInventory->SetItemAndAmount(index, ConvertSlotToItem(slot).item, ConvertSlotToItem(slot).amount);
					onChangeSlotUiDelegate.Broadcast(index, playerInventory,false, false); // TO TEST
					EmptySlot(slot);
					RevertSelection(); // <<<<
					done = true; // A check I need to be sure.
					return;
				}
			}
		}
		if (!done) // check utilizzato nel caso l'inventario fosse vuoto
		{
			playerInventory->inventory.Add(ConvertSlotToItem(slot));
			EmptySlot(slot);
			// LoadUi(slot);
			RevertSelection(); //<<<<
		}
	}
}

/*
WHAT IT DOES:
1. Check if the timer is set more than zero.
2. Start the timer. */
void UManageInventorySlots::PlayTimerSort()
{
	if (sortInventoryTimer <= 0)
		EndTimerSort();
	else
		GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &UManageInventorySlots::EndTimerSort, switchItemTimer * InventoryTimesMultiplier, false);
}
/* WHAT IT DOES:
1. Reset the timer.
2. Sort the items (call the function)
3. Revert the all the selection. */
void UManageInventorySlots::EndTimerSort()
{
	GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
	playerInventory->Sort();
	// chiamare l'evento per la UI qui oppure dentro player<UInventoryBase> (forse meglio dentro <UInventoryBase>)
	RevertSelection();
}
/*
WHAT IT DOES:
1. Check if the timer is set more than zero.
2. Start the timer. */
void UManageInventorySlots::PlayTimerUseItem()
{
	if (ConvertSlotToItem(slotSelected).item != nullptr)
	{
		float timerTime = ConvertSlotToItem(slotSelected).item->useItemTime;

		if (timerTime <= 0)
			EndTimerUse();
		else
			GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &UManageInventorySlots::EndTimerUse, timerTime * InventoryTimesMultiplier, false);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Error"));
}
/* WHAT IT DOES:
1. Reset the timer.
2. Use the items (call the function)
3. Revert the all the selection. */
void UManageInventorySlots::EndTimerUse()
{
	GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
	UseSlot(slotSelected);
}

/* WHAT IT DOES:
1. Reset the timer.
2. Fill the other list with empty slots (call the function)
3. Revert the all the selection. */
void UManageInventorySlots::StopAllTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
	/* ho toccato anche qui
	if (otherInventory != nullptr)
		otherInventory->FillSlots();*/
	addOneItem = true; // >>>>
	BombardiroCrocodilo = -1;
	onMoveSlotUiDelegate.Broadcast(-1);
}

// UI vv
	// per ora
void UManageInventorySlots::UseQuickSlot(int slotToUse)
{
	RevertSelection();
	SelectSlot(slotToUse,playerInventory);
	UseSlot(FSlotSelected(playerInventory, slotToUse)); //if the object has a timer need to change this function
}

void UManageInventorySlots::OpenCloseInventoryUi(bool isOpen)
{
	inventoryOpen = isOpen;
	onChangeInventoryUiDelegate.Broadcast(inventoryOpen);
	if (!isOpen)
	{
		StopAllTimer();
		RevertSelection();
	}
}
// TO TEST
void UManageInventorySlots::AddItemInSlotSelectedTimer()
{
	float timerTime = 0;
	if (ConvertSlotToItem(slotSelected).item != nullptr)
		timerTime = ConvertSlotToItem(slotSelected).item->moveItemTime;

	onChangeSlotUiDelegate.Broadcast(slotSelected.index, slotSelected.inventory,true, false);

	if (timerTime <= 0)
		EndTimerSwitch();
	else
		GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &UManageInventorySlots::EndTimerSwitch, timerTime * InventoryTimesMultiplier, false);
}

void UManageInventorySlots::GiveItem(FItem itemToAdd)
{
	if (playerInventory->GetEmptySlots() > 0)
	{
		bool done = false;
		if (!playerInventory->inventory.IsEmpty())
		{
			int index = -1;
			for (FItem slotInTheList : playerInventory->inventory)
			{
				index++;
				if (slotInTheList.item == nullptr && !done
					&& index > playerInventory->GetQuickSlots()) // TO debug
				{
					playerInventory->SetItemAndAmount(index, itemToAdd.item, itemToAdd.amount);
					onChangeSlotUiDelegate.Broadcast(index, playerInventory,false, false);
					done = true;
				}
			}
		}
		if (!done)
			UE_LOG(LogTemp, Warning, TEXT("Inventory Full"));
	}
}

void UManageInventorySlots::MouseOver(UInventoryBase* inv, int index)
{
	if (inventoryOpen) // TO CHECK
		onTooltipUpdateDelegate.Broadcast(inv, index);
}

void UManageInventorySlots::RemoveItem()
{
	if (!inventoryOpen) // TO CHECK
		return;
	if (slotSelected.inventory == nullptr)
		return;
	if (playerInventory != nullptr)
		if  (slotSelected.inventory != playerInventory)
			return;
	slotSelected.inventory->SetItemAmount(slotSelected.index, 0);
	RevertSelection();
}

