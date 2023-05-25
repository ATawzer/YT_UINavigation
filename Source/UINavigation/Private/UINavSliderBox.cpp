// Copyright (C) 2019 Gonçalo Marques - All Rights Reserved

#include "UINavSliderBox.h"
#include "UINavWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"

void UUINavSliderBox::NativeConstruct()
{
	Super::BaseConstruct();

	PRAGMA_DISABLE_DEPRECATION_WARNINGS
	LeftButton->IsFocusable = false;
	RightButton->IsFocusable = false;
	PRAGMA_ENABLE_DEPRECATION_WARNINGS

	if (!LeftButton->OnClicked.IsBound())
		LeftButton->OnClicked.AddDynamic(this, &UUINavSliderBox::NavigateLeft);
	if (!RightButton->OnClicked.IsBound())
		RightButton->OnClicked.AddDynamic(this, &UUINavSliderBox::NavigateRight);
}

void UUINavSliderBox::Update()
{
	Super::Update();
	
	if (NavText != nullptr)
		NavText->SetText(FText::FromString(FString::FromInt(MinRange + OptionIndex * Interval)));

	const float Percent = UKismetMathLibrary::NormalizeToRange(MinRange + OptionIndex * Interval, MinRange, MaxRange);
	SliderBar->SetPercent(Percent);
}

float UUINavSliderBox::GetSliderPercent() const
{
	return SliderBar->GetPercent();
}
