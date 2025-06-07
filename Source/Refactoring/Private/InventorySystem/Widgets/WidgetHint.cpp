#include "InventorySystem/Widgets/WidgetHint.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UWidgetHint::NativeConstruct()
{
	Super::NativeConstruct();

	DefaultImage = Cast<UTexture2D>(Image->GetBrush().GetResourceObject()); 

}

void UWidgetHint::SetCommand(FName CommandText, UTexture2D* TextureImage)
{
	BlockCommand(1.f);
	if (TextureImage != nullptr)
	{
		Image->SetBrushFromTexture(TextureImage);
	}
	else
	{
		Image->SetBrushFromTexture(DefaultImage);
	}
	
	TextBlock->SetText(FText::FromName(CommandText));
}
void UWidgetHint::BlockCommand(float SetOpacity)
{
	// Image->SetOpacity(true);
	Image->SetRenderOpacity(SetOpacity);
	// TextBlock->SetOpacity(true);
	TextBlock->SetRenderOpacity(SetOpacity);
}

void UWidgetHint::ShowCommand(bool bHide)
{
	if (bHide)
	{
		this->SetVisibility(ESlateVisibility::Hidden); // occhio che al posto di usare "this" potresti usare UWidget padre
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Visible);
	}
}

