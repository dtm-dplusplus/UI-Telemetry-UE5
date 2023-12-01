// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonButtonBase.h"
#include "CommonActionWidget.h"
void UToonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Update the button style from BP if implemented
	UpdateButtonStyle();

	RefreshButtonText();
}

void UToonButtonBase::SetButtonText(const FText& InText)
{
	// Disables the button text override
	bOverride_ButtonText = InText.IsEmpty();

	// Set and refresh button text
	ButtonText = InText;
	RefreshButtonText();
}

void UToonButtonBase::UpdateInputActionWidget()
{
	Super::UpdateInputActionWidget();

	UpdateButtonStyle();
	RefreshButtonText();
}

void UToonButtonBase::OnInputMethodChanged(ECommonInputType CurrentInputType)
{
	Super::OnInputMethodChanged(CurrentInputType);
}

void UToonButtonBase::RefreshButtonText()
{
	// If the button text is empty or overided, try to get it from the input action widget
	if (bOverride_ButtonText || ButtonText.IsEmpty())
	{
		if (InputActionWidget)
		{
			const FText ActionDisplayText = InputActionWidget->GetDisplayText();
			if (!ActionDisplayText.IsEmpty())
			{
				UpdateButtonText(ActionDisplayText);
				return;
			}
		}
	}

	// Otherwise, just use the text from the button
	UpdateButtonText(ButtonText);
}
