// Copyright (C) 2019 Gon�alo Marques - All Rights Reserved

#pragma once

#include "UINavComponentBox.h"
#include "UINavSliderBox.generated.h"

/**
 * 
 */
UCLASS()
class UINAVIGATION_API UUINavSliderBox : public UUINavComponentBox
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = UINavSliderBox)
		class UProgressBar* SliderBar;

	virtual void CheckRightLimit() override;

	virtual void Update() override;
	
public:

	virtual void NativeConstruct() override;

	virtual void NavigateRight() override;

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = UINavSliderBox)
		float GetSliderPercent() const;
	
};
