#include "InventorySystem/Widgets/WidgetHint.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

/*
void UWidgetHint::NativeConstruct()
{
	Super::NativeConstruct();

	this->SetVisibility(ESlateVisibility::Hidden);
}*/

void UWidgetHint::SetCommand(FName CommandText, UTexture2D* TextureImage)
{
	Image->SetBrushFromTexture(TextureImage);
	TextBlock->SetText(FText::FromName(CommandText));
}
void UWidgetHint::BlockCommand()
{
	// Image->SetOpacity(true);
	Image->SetRenderOpacity(0.25f);
	// TextBlock->SetOpacity(true);
	TextBlock->SetRenderOpacity(0.25f);
}

void UWidgetHint::ShowCommand(bool bHide)
{
	if (bHide)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Visible);
	}
}

